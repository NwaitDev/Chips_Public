// ============================================================
//  main.cpp
//  Mini-interpréteur arithmétique – ANTLR4 + C++17
// ============================================================
#include <antlr4-runtime.h>
#include "ChipsLexer.h"
#include "ChipsParser.h"
#include "Interpreter.hpp"

#include "sources/forward_declarations.hpp"


#include "sources/ChipsToXmiVisitor.hpp"
#include "sources/ChipsToXmiWriter.hpp"


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

// ── Interprète un flux ────────────────────────────────────────
void run(std::istream& input, Interpreter& /*interp*/) {
    antlr4::ANTLRInputStream  stream(input);
    ChipsLexer           lexer(&stream);
    antlr4::CommonTokenStream tokens(&lexer);
    ChipsParser          parser(&tokens);

    // Remplace le listener par défaut (qui imprime sur stderr)
    ThrowingErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    auto* tree = parser.program();   // parse
    ASTBuilder builder;



    std::any result = builder.visit(tree);
    std::any_cast<program_node>(result).hello();


}

// ── REPL (Read-Eval-Print Loop) ───────────────────────────────
void repl() {
    Interpreter interp;
    std::cout << "=== Mini-interpréteur arithmétique (C++17 + ANTLR4) ===\n";
    std::cout << "Tapez une expression ou 'quit' pour quitter.\n\n";

    std::string line;
    while (true) {
        std::cout << ">>> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit" || line == "exit") break;
        if (line.empty()) continue;

        // ANTLR attend une fin de ligne pour terminer la règle `statement`
        std::istringstream ss(line + "\n");
        try {
            run(ss, interp);
        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << "\n";
        }
    }
    std::cout << "Au revoir!\n";
}

// ── Exécution d'un fichier ────────────────────────────────────
void runFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Impossible d'ouvrir le fichier : " << path << "\n";
        std::exit(1);
    }
    Interpreter interp;
    try {
        run(file, interp);
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << "\n";
        std::exit(1);
    }
}

// ── Point d'entrée ────────────────────────────────────────────
int main(int argc, char* argv[]) {
    if (argc == 1) {
        repl();          // mode interactif
    } else {
        runFile(argv[1]); // mode fichier
    }
    return 0;
}
