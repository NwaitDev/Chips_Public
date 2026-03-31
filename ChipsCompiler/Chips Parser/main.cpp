// ============================================================
//  main.cpp : Chips Compiler
//  ANTLR4 + C++17
// ============================================================
#include <antlr4-runtime.h>
#include "ChipsLexer.h"
#include "ChipsParser.h"

#include "chips_headers.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <typeinfo>
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
            "Erreur syntaxique ligne " + std::to_string(line) +
            ":" + std::to_string(charPositionInLine) + " – " + msg);
    }
};


void parse(std::istream& input) {

    antlr4::ANTLRInputStream    stream(input);
    ChipsLexer                  lexer(&stream);
    antlr4::CommonTokenStream   tokens(&lexer);
    ChipsParser                 parser(&tokens);

    // Remplace le listener par défaut (qui imprime sur stderr)
    ThrowingErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    auto* tree = parser.program();   // parse
    ASTBuilder builder;

    std::string output = "output.xmi";

    std::ostringstream body_out;
    ChipsToXmiWriter body_writer(body_out);
    ChipsToXmiVisitor visitor(body_writer, body_out);

    std::any result = builder.visit(tree);

    // for(auto* stmt : tree->statement()){
        // std::any result = builder.visit(stmt);
        std::shared_ptr<ast_node> rootPtr = ast_builder_detail::extract_as_node(result);

        if(rootPtr){
            int status;
            const std::type_info& ti = typeid(*rootPtr);
            char* realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
            std::cout << "Type dynamique de rootPtr : " << (realname ? realname : ti.name()) << std::endl;
            free(realname);

            rootPtr->hello();

            SymbolTable::getInstance().dump();
        }else{
            std::cout << "no" << std::endl;
        }
    // }
}

// ── Point d'entrée ────────────────────────────────────────────
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout<<"[ERROR] chips compiler requires exactly one parameter\n"
                 <<"usage: ./chipsc path/to/file.chips"<<std::endl;
        std::cout;
        std::exit(1);
    } else {
        std::string filename(argv[1]);
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << "\n";
            std::exit(1);
        }
        try {
            parse(file);
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << "\n";
            std::exit(1);
        }
        std::exit(0);
    }
    return 0;
}
