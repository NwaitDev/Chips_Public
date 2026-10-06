// ============================================================
//  main.cpp : Chips Compiler
//  ANTLR4 + C++17
// ============================================================
#include <antlr4-runtime.h>
#include "./generated/ChipsLexer.h"
#include "./generated/ChipsParser.h"
#include "./sources/ChipsToXmiWriter.hpp"
#include "./sources/chips_ast2xmi_visitor.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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


void parse(std::istream& input, std::string output, std::string filename) {

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

    auto* tree = parser.program();

    chips_ast_builder builder;
    std::any result = builder.visit(tree);

    program_node* rootPtr = std::any_cast<program_node>(&result);

    if(rootPtr){

        std::ostringstream body_out;
        ChipsToXmiWriter body_writer(body_out);
        chips_ast2xmi_visitor visitor(body_writer, body_out);
        rootPtr->accept(visitor);

        std::ofstream out(output);

        ChipsToXmiWriter writer(out);
        writer.copy_namespaces_from(body_writer);
        writer.xmi_header(filename);
        out << body_out.str();
        writer.xmi_footer();

        out.close();
    }
}

// ── Point d'entrée ────────────────────────────────────────────
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout<<"[ERROR] chips parser requires exactly two parameters\n"
                 <<"usage: ./chipsparser path/to/file.chips path/to/output/file"<<std::endl;
        std::cout;
        std::exit(1);
    } else {
        std::string filename(argv[1]);
        std::string output(argv[2]);
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << "\n";
            std::exit(1);
        }
        try {
            parse(file, output, filename);
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << "\n";
            std::exit(1);
        }
        std::exit(0);
    }
    return 0;
}
