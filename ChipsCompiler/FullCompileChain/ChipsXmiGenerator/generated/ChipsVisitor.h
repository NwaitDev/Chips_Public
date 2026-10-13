
// Generated from /home/agallone/Documents/Thesis_code/Chips_Public/ChipsCompiler/FullCompileChain/ChipsXmiGenerator/../Chips.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "ChipsParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ChipsParser.
 */
class  ChipsVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ChipsParser.
   */
    virtual std::any visitProgram(ChipsParser::ProgramContext *context) = 0;

    virtual std::any visitSystem(ChipsParser::SystemContext *context) = 0;

    virtual std::any visitObjectDefinition(ChipsParser::ObjectDefinitionContext *context) = 0;

    virtual std::any visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *context) = 0;

    virtual std::any visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *context) = 0;

    virtual std::any visitObject_def(ChipsParser::Object_defContext *context) = 0;

    virtual std::any visitImplementation_def(ChipsParser::Implementation_defContext *context) = 0;

    virtual std::any visitNode_mapping(ChipsParser::Node_mappingContext *context) = 0;

    virtual std::any visitLogicalDefintion(ChipsParser::LogicalDefintionContext *context) = 0;

    virtual std::any visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *context) = 0;

    virtual std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *context) = 0;

    virtual std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *context) = 0;

    virtual std::any visitChanneledOutput(ChipsParser::ChanneledOutputContext *context) = 0;

    virtual std::any visitL_function_def(ChipsParser::L_function_defContext *context) = 0;

    virtual std::any visitP_function_def(ChipsParser::P_function_defContext *context) = 0;

    virtual std::any visitC_signature(ChipsParser::C_signatureContext *context) = 0;

    virtual std::any visitC_keywords(ChipsParser::C_keywordsContext *context) = 0;

    virtual std::any visitWith_section(ChipsParser::With_sectionContext *context) = 0;

    virtual std::any visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *context) = 0;

    virtual std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *context) = 0;

    virtual std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *context) = 0;

    virtual std::any visitInit_section(ChipsParser::Init_sectionContext *context) = 0;

    virtual std::any visitThen_section(ChipsParser::Then_sectionContext *context) = 0;

    virtual std::any visitLT(ChipsParser::LTContext *context) = 0;

    virtual std::any visitGT(ChipsParser::GTContext *context) = 0;

    virtual std::any visitLEQ(ChipsParser::LEQContext *context) = 0;

    virtual std::any visitGEQ(ChipsParser::GEQContext *context) = 0;

    virtual std::any visitNEQ(ChipsParser::NEQContext *context) = 0;

    virtual std::any visitEQ(ChipsParser::EQContext *context) = 0;

    virtual std::any visitAND(ChipsParser::ANDContext *context) = 0;

    virtual std::any visitOR(ChipsParser::ORContext *context) = 0;

    virtual std::any visitPassExpr0(ChipsParser::PassExpr0Context *context) = 0;

    virtual std::any visitPLUS(ChipsParser::PLUSContext *context) = 0;

    virtual std::any visitSUB(ChipsParser::SUBContext *context) = 0;

    virtual std::any visitPassExpr01(ChipsParser::PassExpr01Context *context) = 0;

    virtual std::any visitNegate(ChipsParser::NegateContext *context) = 0;

    virtual std::any visitPassExpr1(ChipsParser::PassExpr1Context *context) = 0;

    virtual std::any visitMULT(ChipsParser::MULTContext *context) = 0;

    virtual std::any visitDIV(ChipsParser::DIVContext *context) = 0;

    virtual std::any visitMOD(ChipsParser::MODContext *context) = 0;

    virtual std::any visitNOT(ChipsParser::NOTContext *context) = 0;

    virtual std::any visitPassExpr2(ChipsParser::PassExpr2Context *context) = 0;

    virtual std::any visitIntLiteral(ChipsParser::IntLiteralContext *context) = 0;

    virtual std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *context) = 0;

    virtual std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *context) = 0;

    virtual std::any visitVar(ChipsParser::VarContext *context) = 0;

    virtual std::any visitParens(ChipsParser::ParensContext *context) = 0;

    virtual std::any visitVarContext(ChipsParser::VarContextContext *context) = 0;

    virtual std::any visitFunction(ChipsParser::FunctionContext *context) = 0;

    virtual std::any visitCastAs(ChipsParser::CastAsContext *context) = 0;

    virtual std::any visitCast(ChipsParser::CastContext *context) = 0;

    virtual std::any visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *context) = 0;

    virtual std::any visitStop(ChipsParser::StopContext *context) = 0;

    virtual std::any visitCLT(ChipsParser::CLTContext *context) = 0;

    virtual std::any visitCGT(ChipsParser::CGTContext *context) = 0;

    virtual std::any visitCLEQ(ChipsParser::CLEQContext *context) = 0;

    virtual std::any visitCGEQ(ChipsParser::CGEQContext *context) = 0;

    virtual std::any visitCNEQ(ChipsParser::CNEQContext *context) = 0;

    virtual std::any visitCEQ(ChipsParser::CEQContext *context) = 0;

    virtual std::any visitCAND(ChipsParser::CANDContext *context) = 0;

    virtual std::any visitCOR(ChipsParser::CORContext *context) = 0;

    virtual std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *context) = 0;

    virtual std::any visitCPLUS(ChipsParser::CPLUSContext *context) = 0;

    virtual std::any visitCSUB(ChipsParser::CSUBContext *context) = 0;

    virtual std::any visitPassCExpr01(ChipsParser::PassCExpr01Context *context) = 0;

    virtual std::any visitCNegate(ChipsParser::CNegateContext *context) = 0;

    virtual std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *context) = 0;

    virtual std::any visitCMULT(ChipsParser::CMULTContext *context) = 0;

    virtual std::any visitCDIV(ChipsParser::CDIVContext *context) = 0;

    virtual std::any visitCMOD(ChipsParser::CMODContext *context) = 0;

    virtual std::any visitCNOT(ChipsParser::CNOTContext *context) = 0;

    virtual std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *context) = 0;

    virtual std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *context) = 0;

    virtual std::any visitCINT(ChipsParser::CINTContext *context) = 0;

    virtual std::any visitCFLOAT(ChipsParser::CFLOATContext *context) = 0;

    virtual std::any visitCBOOL(ChipsParser::CBOOLContext *context) = 0;

    virtual std::any visitINPUT(ChipsParser::INPUTContext *context) = 0;

    virtual std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *context) = 0;

    virtual std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *context) = 0;

    virtual std::any visitFunctionCall(ChipsParser::FunctionCallContext *context) = 0;

    virtual std::any visitCParenthesis(ChipsParser::CParenthesisContext *context) = 0;

    virtual std::any visitCCastAs(ChipsParser::CCastAsContext *context) = 0;

    virtual std::any visitC_cast(ChipsParser::C_castContext *context) = 0;

    virtual std::any visitSuffixes(ChipsParser::SuffixesContext *context) = 0;

    virtual std::any visitC_suffixes(ChipsParser::C_suffixesContext *context) = 0;

    virtual std::any visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *context) = 0;

    virtual std::any visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *context) = 0;

    virtual std::any visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *context) = 0;

    virtual std::any visitBlock(ChipsParser::BlockContext *context) = 0;

    virtual std::any visitLoop_in(ChipsParser::Loop_inContext *context) = 0;

    virtual std::any visitLoop_statement(ChipsParser::Loop_statementContext *context) = 0;

    virtual std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *context) = 0;

    virtual std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *context) = 0;

    virtual std::any visitIf_else_statement(ChipsParser::If_else_statementContext *context) = 0;

    virtual std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *context) = 0;

    virtual std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *context) = 0;

    virtual std::any visitIf_statement(ChipsParser::If_statementContext *context) = 0;

    virtual std::any visitS_if_statement(ChipsParser::S_if_statementContext *context) = 0;

    virtual std::any visitC_if_statement(ChipsParser::C_if_statementContext *context) = 0;

    virtual std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext *context) = 0;

    virtual std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *context) = 0;

    virtual std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *context) = 0;

    virtual std::any visitStatementLoop(ChipsParser::StatementLoopContext *context) = 0;

    virtual std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *context) = 0;

    virtual std::any visitStatementIf(ChipsParser::StatementIfContext *context) = 0;

    virtual std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *context) = 0;

    virtual std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *context) = 0;

    virtual std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *context) = 0;

    virtual std::any visitImplementationStatement(ChipsParser::ImplementationStatementContext *context) = 0;

    virtual std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *context) = 0;

    virtual std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *context) = 0;

    virtual std::any visitSIfStatement(ChipsParser::SIfStatementContext *context) = 0;

    virtual std::any visitRegularStatement(ChipsParser::RegularStatementContext *context) = 0;

    virtual std::any visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *context) = 0;

    virtual std::any visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *context) = 0;

    virtual std::any visitSRegularExpression(ChipsParser::SRegularExpressionContext *context) = 0;

    virtual std::any visitCollective_operation(ChipsParser::Collective_operationContext *context) = 0;

    virtual std::any visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *context) = 0;

    virtual std::any visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *context) = 0;

    virtual std::any visitContextualAssignment(ChipsParser::ContextualAssignmentContext *context) = 0;

    virtual std::any visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *context) = 0;

    virtual std::any visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *context) = 0;

    virtual std::any visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *context) = 0;

    virtual std::any visitNamed_output(ChipsParser::Named_outputContext *context) = 0;

    virtual std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *context) = 0;

    virtual std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *context) = 0;

    virtual std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *context) = 0;

    virtual std::any visitIntType(ChipsParser::IntTypeContext *context) = 0;

    virtual std::any visitFloatType(ChipsParser::FloatTypeContext *context) = 0;

    virtual std::any visitBoolType(ChipsParser::BoolTypeContext *context) = 0;

    virtual std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *context) = 0;

    virtual std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *context) = 0;

    virtual std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *context) = 0;

    virtual std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *context) = 0;

    virtual std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *context) = 0;


};

