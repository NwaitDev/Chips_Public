#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <cctype>

#include "antlr4-runtime.h"
#include "ChipsLexer.h"
#include "ChipsParser.h"
#include "CodeGenListener.h"

void print_usage(const char *progName, const std::map<std::string, std::string> &paramDescriptions)
{
    std::cerr << "Usage: " << progName;
    for (const auto &[name, desc] : paramDescriptions)
    {
        if (name.rfind("-", 0) == 0)
            std::cerr << " [" << name << " <value>]";
        else
            std::cerr << " <" << name << ">";
    }
    std::cerr << "\n\n";
    for (const auto &[name, desc] : paramDescriptions)
        std::cerr << "  " << name << "\t\t" << desc << "\n";
}

// paramDescriptions: keys starting with '-' are optional named parameters taking a value;
// keys not starting with '-' are required positional parameters (at most one supported).
std::map<std::string, std::string> parseCommandLine(int argc, char **argv, const std::map<std::string, std::string> &paramDescriptions)
{
    std::map<std::string, std::string> result;

    std::string positionalKey;
    for (const auto &[name, desc] : paramDescriptions)
    {
        if (name.rfind("-", 0) != 0)
        {
            if (!positionalKey.empty())
            {
                std::cerr << "Internal error: more than one positional parameter declared." << std::endl;
                exit(1);
            }
            positionalKey = name;
        }
    }

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg.rfind("-", 0) == 0)
        {
            if (paramDescriptions.find(arg) == paramDescriptions.end())
            {
                std::cerr << "Unknown option: " << arg << std::endl;
                print_usage(argv[0], paramDescriptions);
                exit(1);
            }
            if (i + 1 >= argc)
            {
                std::cerr << "Missing argument for " << arg << std::endl;
                print_usage(argv[0], paramDescriptions);
                exit(1);
            }
            result[arg] = argv[++i];
        }
        else
        {
            if (positionalKey.empty())
            {
                std::cerr << "Unexpected argument: " << arg << std::endl;
                print_usage(argv[0], paramDescriptions);
                exit(1);
            }
            if (result.find(positionalKey) != result.end())
            {
                std::cerr << "Unexpected extra argument: " << arg << std::endl;
                print_usage(argv[0], paramDescriptions);
                exit(1);
            }
            result[positionalKey] = arg;
        }
    }

    if (!positionalKey.empty() && result.find(positionalKey) == result.end())
    {
        std::cerr << "Missing required argument: " << positionalKey << std::endl;
        print_usage(argv[0], paramDescriptions);
        exit(1);
    }

    return result;
}

// Resolves the absolute directory containing the currently running
// executable, so paths relative to the binary (e.g. its ../src folder)
// no longer depend on the caller's current working directory.
std::filesystem::path executable_dir()
{
    return std::filesystem::canonical("/proc/self/exe").parent_path();
}

void ensure_parent_dirs(const std::string &path)
{
    std::filesystem::path p(path);
    std::filesystem::path parent = p.parent_path();
    if (!parent.empty() && !std::filesystem::exists(parent))
    {
        std::filesystem::create_directories(parent);
    }
}

std::string read_file(const std::string &path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        std::cerr << "Failed to open " << path << " for reading." << std::endl;
        exit(1);
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

void write_file(const std::string &path, const std::string &content)
{
    ensure_parent_dirs(path);
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out)
    {
        std::cerr << "Failed to open " << path << " for writing." << std::endl;
        exit(1);
    }
    out << content;
}

std::string include_guard_for(const std::filesystem::path &headerPath)
{
    std::string guard;
    for (char c : headerPath.filename().string())
        guard += std::isalnum(static_cast<unsigned char>(c)) ? static_cast<char>(std::toupper(static_cast<unsigned char>(c))) : '_';
    return guard + "_INCLUDED";
}

std::string section_banner(const std::string &title)
{
    const std::string rule(80, '-');
    return "//" + rule + "\n//" + title + "\n//" + rule + "\n\n";
}

using SourceSegments = std::vector<std::pair<int, std::string>>;

SourceSegments read_source_map(const std::string &path)
{
    std::ifstream in(path);
    if (!in)
        throw std::runtime_error("cannot open source map '" + path + "'");
    SourceSegments segments;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        const std::size_t tab = line.find('\t');
        if (tab == std::string::npos)
            throw std::runtime_error("malformed line in source map '" + path + "': " + line);
        segments.emplace_back(std::stoi(line.substr(0, tab)), line.substr(tab + 1));
    }
    return segments;
}

std::pair<std::string, std::size_t> original_position(const SourceSegments &segments, const std::string &mergedPath, std::size_t line)
{
    const std::pair<int, std::string> *found = nullptr;
    for (const auto &segment : segments)
        if (static_cast<std::size_t>(segment.first) <= line)
            found = &segment;
    if (!found)
        return {mergedPath, line};
    return {found->second, line - static_cast<std::size_t>(found->first) + 1};
}

void generate_cpp(const std::string &chipsPath, const std::string &runtimeHeaderPath,
                  const std::filesystem::path &hppPath, const std::filesystem::path &cppPath, long long maxTicks,
                  const SourceSegments &segments, const std::string &probeFile)
{
    antlr4::ANTLRInputStream inputStream(read_file(chipsPath));
    ChipsLexer lexer(&inputStream);
    antlr4::CommonTokenStream tokens(&lexer);
    ChipsParser parser(&tokens);
    antlr4::tree::ParseTree *tree = parser.program();

    std::ostringstream headerBody;
    std::ostringstream sourceBody;
    CodeGenListener listener(tokens, headerBody, sourceBody);
    listener.setSourcePath(chipsPath);
    listener.setSourceSegments(segments);
    listener.setProbeFile(probeFile);
    listener.setMaxTicks(maxTicks);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

    const std::string guard = include_guard_for(hppPath);
    std::ostringstream hpp;
    hpp << "#ifndef " << guard << "\n#define " << guard << "\n\n";
    hpp << read_file(runtimeHeaderPath) << "\n";
    hpp << section_banner("Declarations generated from chips sources");
    hpp << headerBody.str();
    hpp << "#endif // " << guard << "\n";

    const std::filesystem::path includePath =
        std::filesystem::absolute(hppPath).lexically_relative(std::filesystem::absolute(cppPath).parent_path());
    std::ostringstream cpp;
    cpp << "#include \"" << includePath.generic_string() << "\"\n\n";
    cpp << section_banner("Definitions generated from chips sources");
    cpp << sourceBody.str();

    write_file(hppPath.string(), hpp.str());
    write_file(cppPath.string(), cpp.str());
}

int main(int argc, char **argv)
{
    const std::map<std::string, std::string> paramDescriptions{
        {"input", "path to the chips file to compile"},
        {"-o", "path of the generated source file (default: bip_importable.cpp)"},
        {"-oh", "path of the generated header file (default: the source path with a .hpp extension)"},
        {"-max-ticks", "number of THEN cycles after which each core component stops (default: 1000)"},
        {"-probe-file", "path of the csv file written by the probe statements (default: <input without extension>.probe.csv)"},
        {"-source-map", "file mapping the lines of <input> to the files it was merged from (one '<first line>\\t<path>' per line)"}};

    std::map<std::string, std::string> args = parseCommandLine(argc, argv, paramDescriptions);

    const std::filesystem::path exeDir = executable_dir();

    const std::string chipsPath = std::filesystem::absolute(args.at("input")).string();
    const std::string outputPath = std::filesystem::absolute(
        args.count("-o") ? args.at("-o") : "bip_importable.cpp").string();
    const std::filesystem::path cppPath = std::filesystem::absolute(outputPath);
    const std::filesystem::path hppPath = args.count("-oh")
        ? std::filesystem::absolute(args.at("-oh"))
        : std::filesystem::path(cppPath).replace_extension(".hpp");
    const std::string runtimeHeaderPath = std::filesystem::canonical(
        exeDir / ".." / "src" / "cppHeaderAutoInclude.hpp").string();

    long long maxTicks = 1000;
    if (args.count("-max-ticks"))
    {
        try
        {
            std::size_t used = 0;
            maxTicks = std::stoll(args.at("-max-ticks"), &used);
            if (used != args.at("-max-ticks").size() || maxTicks < 0 || maxTicks > 2147483647LL)
                throw std::invalid_argument("out of range");
        }
        catch (const std::exception &)
        {
            std::cerr << "Invalid value for -max-ticks: " << args.at("-max-ticks") << " (expected an integer between 0 and 2147483647)" << std::endl;
            return 1;
        }
    }

    SourceSegments segments;
    try
    {
        if (args.count("-source-map"))
            segments = read_source_map(args.at("-source-map"));
        const std::string probeFile = args.count("-probe-file")
            ? std::filesystem::absolute(args.at("-probe-file")).string()
            : std::filesystem::path(chipsPath).replace_extension(".probe.csv").string();
        generate_cpp(chipsPath, runtimeHeaderPath, hppPath, cppPath, maxTicks, segments, probeFile);
    }
    catch (const ChipsGenerationError &e)
    {
        const auto [path, line] = original_position(segments, chipsPath, e.line());
        std::cerr << path << ":" << line << ":" << e.column() << ": error: " << e.message() << std::endl;
        return 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << chipsPath << ": error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}