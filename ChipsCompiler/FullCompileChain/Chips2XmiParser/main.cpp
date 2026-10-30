// ============================================================
//  main.cpp : Chips Compiler
//  ANTLR4 + C++17
// ============================================================
#include <antlr4-runtime.h>
#include "./generated/ChipsLexer.h"
#include "./generated/ChipsParser.h"

#include "sources/chips_ast_builder.hpp"
#include "sources/ChipsToXmiWriter.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include <cxxabi.h>

// ── Gestionnaire d'erreur personnalisé ───────────────────────
class ThrowingErrorListener : public antlr4::BaseErrorListener {
public:
    void syntaxError(antlr4::Recognizer* /*recognizer*/,
                     antlr4::Token*      /*offendingSymbol*/,
                     size_t              line,
                     size_t              charPositionInLine,
                     const std::string&  msg,
                     std::exception_ptr  /*e*/) override
    {
        throw std::runtime_error(
            "Syntax error line " + std::to_string(line) +
            ":" + std::to_string(charPositionInLine) + " – " + msg);
    }
};


int parse(std::istream& input, std::string output, std::string filename) {

    antlr4::ANTLRInputStream    stream(input);
    ChipsLexer                  lexer(&stream);
    antlr4::CommonTokenStream   tokens(&lexer);
    ChipsParser                 parser(&tokens);

    // replace the default listener (that prints on stderr)
    ThrowingErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    ChipsParser::ProgramContext* tree = parser.program();

    chips_ast_builder builder(tree);
    program_node& result = builder.getAST();

    try {
        std::ofstream out(output,std::ios::out);
        const std::filesystem::path metamodel = std::filesystem::weakly_canonical(std::filesystem::absolute("../metamodels/chips1.1.ecore"));

        chips_ast2xmi_visitor writer(out, "file://" + metamodel.generic_string());
        writer.write(result);
    } catch (const std::exception &e) {
        std::cerr << "XMI generation failed: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// ── Point d'entrée ────────────────────────────────────────────
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout<<"[ERROR] chips parser requires exactly two parameters\n"
                 <<"usage: ./chipsparser path/to/file.chips path/to/output/file"<<std::endl;
        std::cout;
        return EXIT_FAILURE;
    }
    std::string filename(argv[1]);
    std::string output(argv[2]);
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Impossible d'ouvrir le fichier : " << filename << "\n";
        return EXIT_FAILURE;
    }
    return parse(file, output, filename);
}
