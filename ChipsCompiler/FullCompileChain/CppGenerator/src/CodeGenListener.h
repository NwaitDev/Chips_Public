#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <utility>
#include <stdexcept>
#include <cstddef>

#include "antlr4-runtime.h"
#include "ChipsBaseListener.h"
#include "Dictionary.hpp"

class ChipsGenerationError : public std::runtime_error
{
public:
    ChipsGenerationError(std::size_t line, std::size_t column, const std::string &message);
    std::size_t line() const noexcept { return line_; }
    std::size_t column() const noexcept { return column_; }
    const std::string &message() const noexcept { return message_; }

private:
    std::size_t line_;
    std::size_t column_;
    std::string message_;
};

class CodeGenListener : public ChipsBaseListener
{
public:
    CodeGenListener(antlr4::CommonTokenStream &tokens, std::ostream &headerOut, std::ostream &sourceOut)
        : tokens_(tokens), header_out_(headerOut), source_out_(sourceOut)
    {
    }

    void enterProgram(ChipsParser::ProgramContext *ctx) override;
    void exitL_function_def(ChipsParser::L_function_defContext *ctx) override;
    void exitObject_def(ChipsParser::Object_defContext *ctx) override;
    void exitP_function_def(ChipsParser::P_function_defContext *ctx) override;
    void exitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) override;

private:

    using DefType = std::variant<
        ChipsParser::L_function_defContext*,
        ChipsParser::P_function_defContext*,
        ChipsParser::Collective_op_defContext*>;

    using ObjectType = std::variant<
        ChipsParser::P_function_defContext*,
        ChipsParser::Object_defContext*>;
    
    DefType current_def;
    Dictionary dico;
    std::map<std::string, std::string> varTypes_;
    std::map<ObjectType, std::set<std::pair<std::string, std::string>>> channels_;
    std::map<DefType, std::map<std::string, std::string>> vars_for_def_;
    std::map<ObjectType, std::set<std::pair<std::string, std::string>>> ctx_vars_;
    bool substituteInputDefaults_ = false;
    std::set<std::string> emittedAggrStructs_;

    static std::string capitalize(const std::string &s);
    static std::string contextualParamName(const std::string &name);
    std::string aggregateStructName(const std::vector<ChipsParser::Cdf_defaulted_declContext *> &params);
    std::string aggregateStructDef(const std::vector<ChipsParser::Cdf_defaulted_declContext *> &params);
    void emitAggregateStructIfNeeded(ChipsParser::Collective_op_defContext *ctx);

    void registerChannels(const ObjectType &key);
    void registerContextualVars(const ObjectType &key);
    void storeVar(DefType ctx,const std::string& var_name, const std::string& type);
    const std::set<std::pair<std::string, std::string>> *findContextualVarsForSupportName(const std::string &name) const;

    void emitFunction(const std::string &funcName, const std::vector<std::string> &signatureParts, const std::string &body);
    static std::string joinSortedByName(std::vector<std::pair<std::string, std::string>> namedDecls);
    static std::string dfTypeName(ChipsParser::Df_typeContext *typeCtx);
    static ChipsParser::Df_typeContext *pdfParameterType(ChipsParser::Pdf_parameter_declContext *param);
    std::string translateContextualParams(ChipsParser::P_function_defContext *ctx);

    bool lookupVarType(const std::string &name, std::string &type) const;
    bool isParameterOfCurrentDef(const std::string &name) const;
    bool isContextualOfCurrentDef(const std::string &name) const;
    bool isInnerOfCurrentDef(const std::string &name) const;
    std::string resolveVariableReference(const std::string &name, antlr4::ParserRuleContext *where) const;
    [[noreturn]] static void fail(antlr4::ParserRuleContext *where, const std::string &message);
    bool isSpreadOp(ChipsParser::Collective_op_defContext *ctx) const;

    std::string collectiveFunctionName(ChipsParser::Collective_op_defContext *ctx);
    std::string translateCTarget(ChipsParser::Collective_op_defContext *ctx, int indent);

    std::string chipsTypeFor(ChipsParser::Df_typeContext *typeCtx);
    std::string chipsTypeFor(ChipsParser::ExprContext *ctx);
    std::string chipsTypeFor(ChipsParser::Expr0Context *ctx);
    std::string chipsTypeFor(ChipsParser::Expr01Context *ctx);
    std::string chipsTypeFor(ChipsParser::Expr1Context *ctx);
    std::string chipsTypeFor(ChipsParser::Expr2Context *ctx);

    std::string chipsTypeFor(ChipsParser::C_exprContext *ctx);
    std::string chipsTypeFor(ChipsParser::C_stopless_exprContext *ctx);
    std::string chipsTypeFor(ChipsParser::C_stopless_expr0Context *ctx);
    std::string chipsTypeFor(ChipsParser::C_stopless_expr01Context *ctx);
    std::string chipsTypeFor(ChipsParser::C_stopless_expr1Context *ctx);
    std::string chipsTypeFor(ChipsParser::C_stopless_expr2Context *ctx);

    std::map<ChipsParser::Collective_op_defContext*, std::string> inputTypeCache_;

    static void collectInputContexts(antlr4::tree::ParseTree *node, std::vector<ChipsParser::INPUTContext*> &out);
    std::string inferInputTypeLocal(ChipsParser::INPUTContext *inputCtx);
    std::string inferInputType(ChipsParser::INPUTContext *inputCtx);

    std::string translateParams(const std::vector<ChipsParser::Df_parameter_declContext *> &params);
    std::string translateParams(const std::vector<ChipsParser::Pdf_parameter_declContext *> &params);
    std::string translateOutputs(const std::vector<ChipsParser::Named_outputContext *> &outputs);
    std::string translateOutputs(const std::vector<ChipsParser::P_named_outputContext *> &outputs);

    // inScope parameter allows to specify if the declaration must be in the scope of the section only
    // or in the declaration of the parameters of the function call that models the init/then section
    std::string translateDecl(ChipsParser::StatementDeclarationContext *ctx, int indent, bool inScope);
    std::string translateStatements(const std::vector<ChipsParser::StatementContext *> &statements, int indent, bool inScope);
    std::string translateStatement(ChipsParser::StatementContext *stmt, int indent, bool inScope);
    std::string translateLoop(ChipsParser::Loop_statementContext *ctx, int indent);
    std::string translateIf(ChipsParser::If_statementContext *ctx, int indent);
    std::string translateIfElse(ChipsParser::If_else_statementContext *ctx, int indent);
    std::string translateAssignment(ChipsParser::StatementAssignmentContext *ctx, int indent);
    std::string translateContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx, int indent);

    std::string translateSuffixes(ChipsParser::SuffixesContext *ctx);
    std::string translateLhsSuffixes(ChipsParser::SuffixesContext *s);
    std::string translateCLhsSuffixes(ChipsParser::C_suffixesContext *s);
    std::string translateFunction(ChipsParser::FunctionContext *ctx);
    std::string translateExpr(ChipsParser::ExprContext* ctx);
    std::string translateExpr0(ChipsParser::Expr0Context* ctx);
    std::string translateExpr01(ChipsParser::Expr01Context* ctx);
    std::string translateExpr1(ChipsParser::Expr1Context* ctx);
    std::string translateExpr2(ChipsParser::Expr2Context* ctx);

    // c_statement / c_expr family (collective_op_def bodies)
    std::string translateCStatements(const std::vector<ChipsParser::C_statementContext *> &statements, int indent);
    std::string translateCStatement(ChipsParser::C_statementContext *stmt, int indent);
    std::string translateCLoop(ChipsParser::C_loop_statementContext *ctx, int indent);
    std::string translateCIf(ChipsParser::C_if_statementContext *ctx, int indent);
    std::string translateCIfElse(ChipsParser::C_if_else_statementContext *ctx, int indent);
    std::string translateCDecl(ChipsParser::Cdf_full_declarationContext *ctx, int indent);
    std::string translateCAssignment(ChipsParser::CollectiveAssignmentContext *ctx, int indent);
    std::string translateCContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx, int indent);

    std::string translateCSuffixes(ChipsParser::C_suffixesContext *s);
    std::string translateCFunctionCall(ChipsParser::FunctionCallContext *ctx);
    std::string translateCCast(ChipsParser::C_castContext *ctx);
    std::string translateCExpr(ChipsParser::C_exprContext *ctx);
    std::string translateCStoplessExpr(ChipsParser::C_stopless_exprContext *ctx);
    std::string translateCStoplessExpr0(ChipsParser::C_stopless_expr0Context *ctx);
    std::string translateCStoplessExpr01(ChipsParser::C_stopless_expr01Context *ctx);
    std::string translateCStoplessExpr1(ChipsParser::C_stopless_expr1Context *ctx);
    std::string translateCStoplessExpr2(ChipsParser::C_stopless_expr2Context *ctx);


    std::string extractParameters(ChipsParser::Collective_op_defContext *ctx);
    std::string translateCOutputs(ChipsParser::Collective_op_defContext *ctx, int indent);
    const std::set<std::pair<std::string, std::string>> *findChannelsForObjectName(const std::string &name) const;

    std::string outputText();

    antlr4::CommonTokenStream &tokens_;
    std::ostream &header_out_;
    std::ostream &source_out_;
};