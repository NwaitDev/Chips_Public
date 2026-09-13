#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <filesystem>

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

void cppGenerated_file(const char *srcPath, const std::string &dstPath)
{
    std::ifstream in(srcPath);
    if (!in)
    {
        std::cerr << "Failed to open input file for reading." << std::endl;
        exit(1);
    }
    std::ostringstream buffer;
    buffer << in.rdbuf();
    std::string input = buffer.str();

    antlr4::ANTLRInputStream inputStream(input);

    ChipsLexer lexer(&inputStream);

    antlr4::CommonTokenStream tokens(&lexer);

    ChipsParser parser(&tokens);

    antlr4::tree::ParseTree *tree = parser.program();

    ensure_parent_dirs(dstPath);
    std::ofstream out(dstPath, std::ios::app);
    if (!out)
    {
        std::cerr << "Failed to open output file for writing." << std::endl;
        exit(1);
    }
    CodeGenListener listener(tokens, out);
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
    out.close();
}

void copy_file(const char *srcPath, const std::string &dstPath)
{
    ensure_parent_dirs(dstPath);
    std::ifstream src(srcPath, std::ios::binary);
    std::ofstream dst(dstPath, std::ios::binary);
    const std::size_t bufSize = 65536;
    std::vector<char> buf(bufSize);

    while (src)
    {
        src.read(buf.data(), static_cast<std::streamsize>(bufSize));
        std::streamsize n = src.gcount();
        if (n > 0)
            dst.write(buf.data(), n);
    }
}

int main(int argc, char **argv)
{
    const std::map<std::string, std::string> paramDescriptions{
        {"input", "path to the chips file to compile"},
        {"-o", "path of the file in which to output the generated cpp code (default: bip_importable.cpp)"}};

    std::map<std::string, std::string> args = parseCommandLine(argc, argv, paramDescriptions);

    const std::filesystem::path exeDir = executable_dir();

    const std::string chipsPath = std::filesystem::absolute(args.at("input")).string();
    const std::string outputPath = std::filesystem::absolute(
        args.count("-o") ? args.at("-o") : "bip_importable.cpp").string();
    const std::string headerPath = std::filesystem::canonical(
        exeDir / ".." / "src" / "cppHeaderAutoInclude.hpp").string();

    copy_file(headerPath.c_str(), outputPath);
    cppGenerated_file(chipsPath.c_str(), outputPath);
    // std::cout << "Generated code written to " << outputPath << std::endl;

    return 0;
}