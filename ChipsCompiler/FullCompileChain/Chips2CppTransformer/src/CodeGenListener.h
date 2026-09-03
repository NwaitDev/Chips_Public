#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "antlr4-runtime.h"
#include "ChipsBaseListener.h"

// Walks the Chips parse tree and, for every logical/physical function
// definition, emits a pair of C++ functions (<name>_init / <name>_then)
// whose bodies are translated from the original init_section / then_section
// statements.
//
// Most statement kinds (declarations, assignments, contextual assignments)
// are already valid C++ syntax and are copied verbatim from the source.
// `foreach` loops have no direct C++ equivalent and are rewritten:
//
//   foreach x in y { ... }        ->  for (auto& x : y) { ... }
//   foreach x in y(a, b) { ... }  ->  y(a, b) is called once to build a
//                                     generator, then invoked once per
//                                     iteration to produce the next value.
//
// `if` / `if-else` bodies are recursed into as well, since they may contain
// nested loops.
class CodeGenListener : public ChipsBaseListener
{
public:
    CodeGenListener(antlr4::CommonTokenStream &tokens, std::ostream &out)
        : tokens_(tokens), out_(out)
    {
    }

    void exitL_function_def(ChipsParser::L_function_defContext *ctx) override;
    void exitP_function_def(ChipsParser::P_function_defContext *ctx) override;

private:
    void emitSection(const std::string &funcName,
                      const std::string &suffix,
                      const std::vector<ChipsParser::StatementContext *> &statements);

    std::string translateStatements(const std::vector<ChipsParser::StatementContext *> &statements,
                                     int indent);
    std::string translateStatement(ChipsParser::StatementContext *stmt, int indent);
    std::string translateLoop(ChipsParser::Loop_statementContext *ctx, int indent);
    std::string translateIf(ChipsParser::If_statementContext *ctx, int indent);
    std::string translateIfElse(ChipsParser::If_else_statementContext *ctx, int indent);
    std::string translateDecl(ChipsParser::StatementDeclarationContext *ctx, int indent);
    std::string header(std::string address);

    antlr4::CommonTokenStream &tokens_;
    std::ostream &out_;
};