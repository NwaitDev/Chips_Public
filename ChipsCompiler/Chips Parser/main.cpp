// ============================================================
//  main.cpp
//  Mini-interpréteur arithmétique – ANTLR4 + C++17
// ============================================================
#include <antlr4-runtime.h>
#include "ChipsLexer.h"
#include "ChipsParser.h"
#include "Interpreter.hpp"

#include "sources/forward_declarations.hpp"
#include "sources/ASTBuilder.hpp"
#include "sources/ast_lrxvalues.hpp"


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

    std::string output = "output.xmi";

    // std::cout << "Génération XMI: " << output << std::endl;

    std::ostringstream body_out;
    ChipsToXmiWriter body_writer(body_out);
    ChipsToXmiVisitor visitor(body_writer, body_out);

    // std::cout << "Nb expr: " << tree->expr().size() << std::endl;

    std::any result = builder.visit(tree->expr());

    // extract_as_node dispatche sur tous les types concrets connus
    // et retourne shared_ptr<ast_node> sans que main.cpp connaisse le type template
    std::shared_ptr<ast_node> rootPtr = ast_builder_detail::extract_as_node(result);

    if(rootPtr){
        int status;
        const std::type_info& ti = typeid(*rootPtr);
        char* realname = abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status);
        std::cout << "Type dynamique : " << (realname ? realname : ti.name()) << std::endl;
        free(realname);

        // rootPtr->hello();

        ast_node& root = *rootPtr;
        root.accept(visitor);

        std::ofstream out(output);

        ChipsToXmiWriter writer(out);
        writer.copy_namespaces_from(body_writer);
        writer.xmi_header("error");
        out << body_out.str();
        writer.xmi_footer();

        out.close();
        std::cout << "XMI généré: " << output << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }

    // for(auto* stmt : tree->expr()){
    //     std::any result = builder.visit(stmt);
    //     ast_node* rootPtr = std::any_cast<ast_node>(&result);

    //     if(rootPtr){
    //         int status;
    //         const std::type_info& ti = typeid(*rootPtr);
    //         char* realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
    //         std::cout << "Type dynamique de rootPtr : " << (realname ? realname : ti.name()) << std::endl;
    //         free(realname);
    //     }else{
    //         std::cout << "no" << std::endl;
    //     }

    //     if(auto INT = dynamic_cast<chips::direct<chips::dataflow_type::INT, chips::expression_env::PRIMITIVE>*>(rootPtr)){
    //         std::cout << "ENTIER" << std::endl;
    //         INT->hello();
    //     }
    //     // ast_node& root = *rootPtr;

    //     // root.accept(visitor);

    //     // std::ofstream out(output);

    //     // ChipsToXmiWriter writer(out);
    //     // writer.copy_namespaces_from(body_writer);
    //     // writer.xmi_header("error");
    //     // out << body_out.str();
    //     // writer.xmi_footer();

    //     // out.close();
    //     // std::cout << "XMI généré: " << output << std::endl;
    // }


    // interp.visit(tree);              // évalue
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
