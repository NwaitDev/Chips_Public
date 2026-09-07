#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>

#include "antlr4-runtime.h"
#include "ChipsBaseListener.h"

#include <variant>
#include <utility>

class Dictionary {
public:
   using Value = std::map<std::string,std::string>;

    void addLogical(
        ChipsParser::L_function_defContext* key,
        const std::string& name,
        const std::string& value);

    void addPhysical(
        ChipsParser::P_function_defContext* key,
        const std::string& name,
        const std::string& value);

    void addSpread(
        ChipsParser::Collective_op_defContext* key,
        const std::string& name,
        const std::string& value);

    void addCollect(
        ChipsParser::Collective_op_defContext* key,
        const std::string& name,
        const std::string& value);

    std::string serializeL(
        ChipsParser::L_function_defContext* key) const;

    std::string serializeP(
        ChipsParser::P_function_defContext* key) const;

    std::string serializeCollective(
        ChipsParser::Collective_op_defContext* key) const;

private:
    std::map<ChipsParser::L_function_defContext*, Value> logicals_;
    std::map<ChipsParser::P_function_defContext*, Value> physicals_;
    std::map<ChipsParser::Collective_op_defContext*, Value> spreads_;
    std::map<ChipsParser::Collective_op_defContext*, Value> collects_;
};


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
    
    using DefType = std::variant<
        ChipsParser::L_function_defContext*,
        ChipsParser::P_function_defContext*,
        ChipsParser::CollectiveOperationDefinitionContext*>;
    DefType current_def;
    Dictionary dico;
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