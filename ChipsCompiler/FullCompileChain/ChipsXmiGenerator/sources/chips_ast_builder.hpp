#pragma once

#include <any>
#include <memory>

#include "../generated/ChipsBaseVisitor.h"
#include "../generated/ChipsParser.h"
#include "antlr4-runtime.h"

#include "ast_node_definitions.hpp"

using namespace chips;

class chips_ast_builder : public ChipsBaseVisitor {
    private:
    std::vector<std::unique_ptr<chips::ast_node>> m_all_nodes;

    public:
    program_node m_program;

    template<typename T, typename... Args>
    T* make_node(Args&&... args)
    {
        auto owned = std::make_unique<T>(std::forward<Args>(args)...);
        T* raw = owned.get();
        m_all_nodes.push_back(std::move(owned));
        return raw;
    }

    chips_ast_builder(ChipsParser::ProgramContext* prgm):
    m_program(std::any_cast<program_node>(prgm->accept(this))) {}

    program_node* getAST(){
        return &m_program;
    }

    std::any visitProgram(ChipsParser::ProgramContext *ctx) override;

    std::any visitSystem(ChipsParser::SystemContext *ctx) override;

    std::any
    visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) override;

    std::any
    visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) override;

    std::any visitCollectiveOperationDefinition(
        ChipsParser::CollectiveOperationDefinitionContext *ctx) override;

    std::any visitObject_def(ChipsParser::Object_defContext *ctx) override;

    std::any visitNode_mapping(ChipsParser::Node_mappingContext *ctx) override;

    std::any
    visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) override;

    std::any
    visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) override;

    std::any
    visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) override;

    std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) override;

    std::any
    visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) override;

    std::any
    visitL_function_def(ChipsParser::L_function_defContext *ctx) override;

    std::any
    visitP_function_def(ChipsParser::P_function_defContext *ctx) override;

    std::any visitC_signature(ChipsParser::C_signatureContext *ctx) override;

    std::any visitC_keywords(ChipsParser::C_keywordsContext *ctx) override;

    std::any visitWith_section(ChipsParser::With_sectionContext *ctx) override;

    std::any
    visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) override;

    std::any visitContextualDeclaration(
        ChipsParser::ContextualDeclarationContext *ctx) override;

    std::any visitWithRegularStatement(
        ChipsParser::WithRegularStatementContext *ctx) override;

    std::any visitInit_section(ChipsParser::Init_sectionContext *ctx) override;

    std::any visitThen_section(ChipsParser::Then_sectionContext *ctx) override;

    std::any visitLT(ChipsParser::LTContext *ctx) override;

    std::any visitGT(ChipsParser::GTContext *ctx) override;

    std::any visitLEQ(ChipsParser::LEQContext *ctx) override;

    std::any visitGEQ(ChipsParser::GEQContext *ctx) override;

    std::any visitNEQ(ChipsParser::NEQContext *ctx) override;

    std::any visitEQ(ChipsParser::EQContext *ctx) override;

    std::any visitAND(ChipsParser::ANDContext *ctx) override;

    std::any visitOR(ChipsParser::ORContext *ctx) override;

    std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx) override;

    std::any visitPLUS(ChipsParser::PLUSContext *ctx) override;

    std::any visitSUB(ChipsParser::SUBContext *ctx) override;

    std::any visitPassExpr01(ChipsParser::PassExpr01Context *ctx) override;

    std::any visitNegate(ChipsParser::NegateContext *ctx) override;

    std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx) override;

    std::any visitMULT(ChipsParser::MULTContext *ctx) override;

    std::any visitDIV(ChipsParser::DIVContext *ctx) override;

    std::any visitMOD(ChipsParser::MODContext *ctx) override;

    std::any visitNOT(ChipsParser::NOTContext *ctx) override;

    std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx) override;

    std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx) override;

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) override;

    std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) override;

    std::any visitVar(ChipsParser::VarContext *ctx) override;

    std::any visitParens(ChipsParser::ParensContext *ctx) override;

    std::any visitVarContext(ChipsParser::VarContextContext *ctx) override;

    std::any visitFunction(ChipsParser::FunctionContext *ctx) override;

    std::any visitCastAs(ChipsParser::CastAsContext *ctx) override;

    std::any visitCast(ChipsParser::CastContext *ctx) override;

    std::any visitCStoplessExpression(
        ChipsParser::CStoplessExpressionContext *ctx) override;

    std::any visitStop(ChipsParser::StopContext *ctx) override;

    std::any visitCLT(ChipsParser::CLTContext *ctx) override;

    std::any visitCGT(ChipsParser::CGTContext *ctx) override;

    std::any visitCLEQ(ChipsParser::CLEQContext *ctx) override;

    std::any visitCGEQ(ChipsParser::CGEQContext *ctx) override;

    std::any visitCNEQ(ChipsParser::CNEQContext *ctx) override;

    std::any visitCEQ(ChipsParser::CEQContext *ctx) override;

    std::any visitCAND(ChipsParser::CANDContext *ctx) override;

    std::any visitCOR(ChipsParser::CORContext *ctx) override;

    std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) override;

    std::any visitCPLUS(ChipsParser::CPLUSContext *ctx) override;

    std::any visitCSUB(ChipsParser::CSUBContext *ctx) override;

    std::any visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) override;

    std::any visitCNegate(ChipsParser::CNegateContext *ctx) override;

    std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) override;

    std::any visitCMULT(ChipsParser::CMULTContext *ctx) override;

    std::any visitCDIV(ChipsParser::CDIVContext *ctx) override;

    std::any visitCMOD(ChipsParser::CMODContext *ctx) override;

    std::any visitCNOT(ChipsParser::CNOTContext *ctx) override;

    std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) override;

    std::any visitCVariableExpression(
        ChipsParser::CVariableExpressionContext *ctx) override;

    std::any visitCINT(ChipsParser::CINTContext *ctx) override;

    std::any visitCFLOAT(ChipsParser::CFLOATContext *ctx) override;

    std::any visitCBOOL(ChipsParser::CBOOLContext *ctx) override;

    std::any visitINPUT(ChipsParser::INPUTContext *ctx) override;

    std::any visitCtxVariableExpression(
        ChipsParser::CtxVariableExpressionContext *ctx) override;

    std::any visitChanneledAccuExpression(
        ChipsParser::ChanneledAccuExpressionContext *ctx) override;

    std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx) override;

    std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx) override;

    std::any visitCCastAs(ChipsParser::CCastAsContext *ctx) override;

    std::any visitC_cast(ChipsParser::C_castContext *ctx) override;

    std::any visitSuffixes(ChipsParser::SuffixesContext *ctx) override;

    std::any visitC_suffixes(ChipsParser::C_suffixesContext *ctx) override;

    std::any visitSSuffixableVariableExpression(
        ChipsParser::SSuffixableVariableExpressionContext *ctx) override;

    std::any visitSSuffixableFunctionCallExpression(
        ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) override;

    std::any visitSSuffixableBlockOutputExpression(
        ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) override;

    std::any visitBlock(ChipsParser::BlockContext *ctx) override;

    std::any visitLoop_in(ChipsParser::Loop_inContext *ctx) override;

    std::any
    visitLoop_statement(ChipsParser::Loop_statementContext *ctx) override;

    std::any
    visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) override;

    std::any
    visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) override;

    std::any
    visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) override;

    std::any visitS_if_else_statement(
        ChipsParser::S_if_else_statementContext *ctx) override;

    std::any visitC_if_else_statement(
        ChipsParser::C_if_else_statementContext *ctx) override;

    std::any visitIf_statement(ChipsParser::If_statementContext *ctx) override;

    std::any
    visitS_if_statement(ChipsParser::S_if_statementContext *ctx) override;

    std::any
    visitC_if_statement(ChipsParser::C_if_statementContext *ctx) override;

    std::any visitStatementDeclaration(
        ChipsParser::StatementDeclarationContext *ctx) override;

    std::any visitStatementAssignment(
        ChipsParser::StatementAssignmentContext *ctx) override;

    std::any visitStatementContextualAssignment(
        ChipsParser::StatementContextualAssignmentContext *ctx) override;

    std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx) override;

    std::any
    visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) override;

    std::any visitStatementIf(ChipsParser::StatementIfContext *ctx) override;

    std::any
    visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) override;

    std::any
    visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) override;

    std::any
    visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) override;

    std::any
    visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) override;

    std::any
    visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) override;

    std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx) override;

    std::any
    visitRegularStatement(ChipsParser::RegularStatementContext *ctx) override;

    std::any visitSBlockOutputExpression(
        ChipsParser::SBlockOutputExpressionContext *ctx) override;

    std::any visitSCollectiveCastExpression(
        ChipsParser::SCollectiveCastExpressionContext *ctx) override;

    std::any
    visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) override;

    std::any visitCollective_operation(
        ChipsParser::Collective_operationContext *ctx) override;

    std::any visitCollectiveVariableDeclaration(
        ChipsParser::CollectiveVariableDeclarationContext *ctx) override;

    std::any visitCollectiveAssignment(
        ChipsParser::CollectiveAssignmentContext *ctx) override;

    std::any visitContextualAssignment(
        ChipsParser::ContextualAssignmentContext *ctx) override;

    std::any visitCollectiveLoopStatement(
        ChipsParser::CollectiveLoopStatementContext *ctx) override;

    std::any visitCollectiveIfElseStatement(
        ChipsParser::CollectiveIfElseStatementContext *ctx) override;

    std::any visitCollectiveIfStatement(
        ChipsParser::CollectiveIfStatementContext *ctx) override;

    std::any visitNamed_output(ChipsParser::Named_outputContext *ctx) override;

    std::any
    visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) override;

    std::any
    visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) override;

    std::any
    visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) override;

    std::any visitIntType(ChipsParser::IntTypeContext *ctx) override;

    std::any visitFloatType(ChipsParser::FloatTypeContext *ctx) override;

    std::any visitBoolType(ChipsParser::BoolTypeContext *ctx) override;

    std::any visitFunctionParameterType(
        ChipsParser::FunctionParameterTypeContext *ctx) override;

    std::any visitSensorParameterType(
        ChipsParser::SensorParameterTypeContext *ctx) override;

    std::any
    visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) override;

    std::any
    visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) override;

    std::any visitCdf_full_declaration(
        ChipsParser::Cdf_full_declarationContext *ctx) override;
};