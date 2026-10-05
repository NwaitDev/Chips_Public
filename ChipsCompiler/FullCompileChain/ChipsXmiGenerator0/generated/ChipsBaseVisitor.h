
// Generated from /home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/FullCompileChain/ChipsXmiGenerator/../Chips.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ChipsVisitor.h"


/**
 * This class provides an empty implementation of ChipsVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ChipsBaseVisitor : public ChipsVisitor {
public:

  virtual std::any visitProgram(ChipsParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSystem(ChipsParser::SystemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObject_def(ChipsParser::Object_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplementation_def(ChipsParser::Implementation_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNode_mapping(ChipsParser::Node_mappingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitL_function_def(ChipsParser::L_function_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitP_function_def(ChipsParser::P_function_defContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_signature(ChipsParser::C_signatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_keywords(ChipsParser::C_keywordsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWith_section(ChipsParser::With_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInit_section(ChipsParser::Init_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThen_section(ChipsParser::Then_sectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLT(ChipsParser::LTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGT(ChipsParser::GTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLEQ(ChipsParser::LEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGEQ(ChipsParser::GEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNEQ(ChipsParser::NEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEQ(ChipsParser::EQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAND(ChipsParser::ANDContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOR(ChipsParser::ORContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPLUS(ChipsParser::PLUSContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSUB(ChipsParser::SUBContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassExpr01(ChipsParser::PassExpr01Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegate(ChipsParser::NegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMULT(ChipsParser::MULTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDIV(ChipsParser::DIVContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMOD(ChipsParser::MODContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNOT(ChipsParser::NOTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVar(ChipsParser::VarContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParens(ChipsParser::ParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarContext(ChipsParser::VarContextContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction(ChipsParser::FunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCastAs(ChipsParser::CastAsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCast(ChipsParser::CastContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStop(ChipsParser::StopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCLT(ChipsParser::CLTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCGT(ChipsParser::CGTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCLEQ(ChipsParser::CLEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCGEQ(ChipsParser::CGEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCNEQ(ChipsParser::CNEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCEQ(ChipsParser::CEQContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCAND(ChipsParser::CANDContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCOR(ChipsParser::CORContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCPLUS(ChipsParser::CPLUSContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCSUB(ChipsParser::CSUBContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCNegate(ChipsParser::CNegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCMULT(ChipsParser::CMULTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCDIV(ChipsParser::CDIVContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCMOD(ChipsParser::CMODContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCNOT(ChipsParser::CNOTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCINT(ChipsParser::CINTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCFLOAT(ChipsParser::CFLOATContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCBOOL(ChipsParser::CBOOLContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitINPUT(ChipsParser::INPUTContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCCastAs(ChipsParser::CCastAsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_cast(ChipsParser::C_castContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuffixes(ChipsParser::SuffixesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_suffixes(ChipsParser::C_suffixesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(ChipsParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop_in(ChipsParser::Loop_inContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIf_statement(ChipsParser::If_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementIf(ChipsParser::StatementIfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRegularStatement(ChipsParser::RegularStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollective_operation(ChipsParser::Collective_operationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamed_output(ChipsParser::Named_outputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntType(ChipsParser::IntTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloatType(ChipsParser::FloatTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolType(ChipsParser::BoolTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx) override {
    return visitChildren(ctx);
  }


};

