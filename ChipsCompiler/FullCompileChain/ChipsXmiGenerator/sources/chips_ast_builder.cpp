#include "chips_ast_builder.hpp"
#include "../generated/ChipsParser.h"


#define UNIMPLEMENTED_METHOD \
  throw std::runtime_error(std::string("unimplemented ") + __func__ + " error.")


std::any chips_ast_builder::visitProgram(ChipsParser::ProgramContext *ctx)
{
  std::vector<definition_variant> defs{};
  for (ChipsParser::PreambleContext* def : ctx->preamble())
  {
    definition_variant dv = std::any_cast<definition_variant>(def->accept(this));
    defs.push_back(dv);
  }

  system_section_node system =  std::any_cast<system_section_node>(ctx->system()->accept(this));
  return program_node(
      ctx->getStart()->getLine(),
      ctx->getStart()->getCharPositionInLine(),
      std::string("ChipsModel"),
      preamble_section_node(0,0,defs),
      system
    );
}

std::any chips_ast_builder::visitSystem(ChipsParser::SystemContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) 
{
    return ctx->function_def()->accept(this);
}


std::any chips_ast_builder::visitCollectiveOperationDefinition(
    ChipsParser::CollectiveOperationDefinitionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitObject_def(ChipsParser::Object_defContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNode_mapping(ChipsParser::Node_mappingContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) 
{
  return ctx->p_function_def()->accept(this);
}


std::any
chips_ast_builder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitL_function_def(ChipsParser::L_function_defContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitP_function_def(ChipsParser::P_function_defContext *ctx) 
{
  std::vector<function_parameter_variant> parameters{};


  std::vector<physical_parameter_variant> sensors{};

  with_section with = std::any_cast<with_section>(ctx->with_section()->accept(this));

  init_section init = std::any_cast<init_section>(ctx->with_section()->accept(this));

  then_section then = std::any_cast<then_section>(ctx->with_section()->accept(this));

  std::vector<function_output_variant> outputs{};

  std::vector<physical_output_variant> actuators{};

  return physical_definition(
    ctx->getStart()->getLine(),
    ctx->getStart()->getCharPositionInLine(),
    ctx->IDENTIFIER()->getText(), parameters, sensors,
    with,
    init,
    then, 
    outputs, actuators
  );
}


std::any chips_ast_builder::visitC_signature(ChipsParser::C_signatureContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_keywords(ChipsParser::C_keywordsContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitWith_section(ChipsParser::With_sectionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitContextualDeclaration(
    ChipsParser::ContextualDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitWithRegularStatement(
    ChipsParser::WithRegularStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitInit_section(ChipsParser::Init_sectionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitThen_section(ChipsParser::Then_sectionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitLT(ChipsParser::LTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitGT(ChipsParser::GTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitLEQ(ChipsParser::LEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitGEQ(ChipsParser::GEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNEQ(ChipsParser::NEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitEQ(ChipsParser::EQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitAND(ChipsParser::ANDContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitOR(ChipsParser::ORContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPLUS(ChipsParser::PLUSContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSUB(ChipsParser::SUBContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassExpr01(ChipsParser::PassExpr01Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNegate(ChipsParser::NegateContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitMULT(ChipsParser::MULTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitDIV(ChipsParser::DIVContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitMOD(ChipsParser::MODContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNOT(ChipsParser::NOTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitVar(ChipsParser::VarContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitParens(ChipsParser::ParensContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitVarContext(ChipsParser::VarContextContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFunction(ChipsParser::FunctionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCastAs(ChipsParser::CastAsContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCast(ChipsParser::CastContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCStoplessExpression(
    ChipsParser::CStoplessExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStop(ChipsParser::StopContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCLT(ChipsParser::CLTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCGT(ChipsParser::CGTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCLEQ(ChipsParser::CLEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCGEQ(ChipsParser::CGEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNEQ(ChipsParser::CNEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCEQ(ChipsParser::CEQContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCAND(ChipsParser::CANDContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCOR(ChipsParser::CORContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCPLUS(ChipsParser::CPLUSContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCSUB(ChipsParser::CSUBContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNegate(ChipsParser::CNegateContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCMULT(ChipsParser::CMULTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCDIV(ChipsParser::CDIVContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCMOD(ChipsParser::CMODContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCNOT(ChipsParser::CNOTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCVariableExpression(
    ChipsParser::CVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCINT(ChipsParser::CINTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCFLOAT(ChipsParser::CFLOATContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCBOOL(ChipsParser::CBOOLContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitINPUT(ChipsParser::INPUTContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCtxVariableExpression(
    ChipsParser::CtxVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitChanneledAccuExpression(
    ChipsParser::ChanneledAccuExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCCastAs(ChipsParser::CCastAsContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_cast(ChipsParser::C_castContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSuffixes(ChipsParser::SuffixesContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableVariableExpression(
    ChipsParser::SSuffixableVariableExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableFunctionCallExpression(
    ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSSuffixableBlockOutputExpression(
    ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitBlock(ChipsParser::BlockContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitLoop_in(ChipsParser::Loop_inContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLoop_statement(ChipsParser::Loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitS_if_else_statement(
    ChipsParser::S_if_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitC_if_else_statement(
    ChipsParser::C_if_else_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitIf_statement(ChipsParser::If_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementDeclaration(
    ChipsParser::StatementDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementAssignment(
    ChipsParser::StatementAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementContextualAssignment(
    ChipsParser::StatementContextualAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementLoop(ChipsParser::StatementLoopContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitStatementIf(ChipsParser::StatementIfContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitRegularStatement(ChipsParser::RegularStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSBlockOutputExpression(
    ChipsParser::SBlockOutputExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSCollectiveCastExpression(
    ChipsParser::SCollectiveCastExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollective_operation(
    ChipsParser::Collective_operationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveVariableDeclaration(
    ChipsParser::CollectiveVariableDeclarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveAssignment(
    ChipsParser::CollectiveAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitContextualAssignment(
    ChipsParser::ContextualAssignmentContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveLoopStatement(
    ChipsParser::CollectiveLoopStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveIfElseStatement(
    ChipsParser::CollectiveIfElseStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCollectiveIfStatement(
    ChipsParser::CollectiveIfStatementContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitNamed_output(ChipsParser::Named_outputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitIntType(ChipsParser::IntTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFloatType(ChipsParser::FloatTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitBoolType(ChipsParser::BoolTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitFunctionParameterType(
    ChipsParser::FunctionParameterTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitSensorParameterType(
    ChipsParser::SensorParameterTypeContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any
chips_ast_builder::visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}


std::any chips_ast_builder::visitCdf_full_declaration(
    ChipsParser::Cdf_full_declarationContext *ctx) 
{
  UNIMPLEMENTED_METHOD;
}

#undef UNIMPLEMENTED_METHOD
