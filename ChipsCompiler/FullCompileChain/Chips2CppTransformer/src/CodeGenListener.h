#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "antlr4-runtime.h"
#include "ChipsBaseListener.h"


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
    void emitSection(const std::string &funcName, const std::string &suffix, const std::vector<ChipsParser::StatementContext *> &statements, const std::string &params);

    std::string chipsTypeFor(ChipsParser::Df_typeContext *typeCtx);
    std::string translateParams(const std::vector<ChipsParser::Df_parameter_declContext *> &params);
    std::string translateParams(const std::vector<ChipsParser::Pdf_parameter_declContext *> &params);
    
    // inScope parameter allows to specify if the declaration must be in the scope of the section only
    // or in the declaration of the parameters of the function call that models the init/then section
    std::string translateDecl(ChipsParser::StatementDeclarationContext *ctx, int indent, bool inScope);
    std::string translateStatements(const std::vector<ChipsParser::StatementContext *> &statements, int indent, bool inScope);
    std::string translateStatement(ChipsParser::StatementContext *stmt, int indent, bool inScope);
    std::string translateLoop(ChipsParser::Loop_statementContext *ctx, int indent);
    std::string translateIf(ChipsParser::If_statementContext *ctx, int indent);
    std::string translateIfElse(ChipsParser::If_else_statementContext *ctx, int indent);

    std::string translateSuffixes(ChipsParser::SuffixesContext *ctx);
    std::string translateFunction(ChipsParser::FunctionContext *ctx);
    std::string translateExpr(ChipsParser::ExprContext* ctx);
    std::string translateExpr0(ChipsParser::Expr0Context* ctx);
    std::string translateExpr01(ChipsParser::Expr01Context* ctx);
    std::string translateExpr1(ChipsParser::Expr1Context* ctx);
    std::string translateExpr2(ChipsParser::Expr2Context* ctx);

    antlr4::CommonTokenStream &tokens_;
    std::ostream &out_;
};