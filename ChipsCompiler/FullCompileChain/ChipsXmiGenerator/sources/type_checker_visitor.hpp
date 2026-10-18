#pragma once

#include <any>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "../generated/ChipsBaseVisitor.h"
#include "../generated/ChipsParser.h"
#include "antlr4-runtime.h"

#include "input_inference_visitor.hpp"
#include "type_utils.hpp"
#include "visitor_env.hpp"

class type_checker_visitor : public ChipsBaseVisitor {
public:
  struct s_expr_info {
    bool is_channel = false;
    bool physical = false;
    std::optional<dataflow_type> type = std::nullopt;
    std::string channel_type;
  };

  visitor_env &venv;
  input_inference_visitor inference;

  explicit type_checker_visitor(visitor_env &venv)
      : venv(venv), inference(venv) {}

  dataflow_type type_of(antlr4::tree::ParseTree *tree) {
    return std::any_cast<dataflow_type>(visit(tree));
  }

  dataflow_type infer_type(ChipsParser::ExprContext *ctx) {
    return type_of(ctx);
  }
  dataflow_type infer_type(ChipsParser::Expr0Context *ctx) {
    return type_of(ctx);
  }
  dataflow_type infer_type(ChipsParser::Expr01Context *ctx) {
    return type_of(ctx);
  }
  dataflow_type infer_type(ChipsParser::Expr1Context *ctx) {
    return type_of(ctx);
  }
  dataflow_type infer_type(ChipsParser::Expr2Context *ctx) {
    return type_of(ctx);
  }
  std::optional<dataflow_type> infer_type(ChipsParser::C_exprContext *ctx) {
    return inference.infer(ctx).forced_type;
  }
  std::optional<dataflow_type>
  infer_type(ChipsParser::C_stopless_exprContext *ctx) {
    return inference.infer(ctx).forced_type;
  }
  std::optional<dataflow_type>
  infer_type(ChipsParser::C_stopless_expr0Context *ctx) {
    return inference.infer(ctx).forced_type;
  }
  std::optional<dataflow_type>
  infer_type(ChipsParser::C_stopless_expr01Context *ctx) {
    return inference.infer(ctx).forced_type;
  }
  std::optional<dataflow_type>
  infer_type(ChipsParser::C_stopless_expr1Context *ctx) {
    return inference.infer(ctx).forced_type;
  }
  std::optional<dataflow_type>
  infer_type(ChipsParser::C_stopless_expr2Context *ctx) {
    return inference.infer(ctx).forced_type;
  }

  void expect(antlr4::ParserRuleContext *ctx, dataflow_type expected,
              const std::string &what) {
    dataflow_type actual = type_of(ctx);
    if (actual != expected) {
      type_fail(venv, ctx,
                what + ": expected " + type_name(expected) + ", got " +
                    type_name(actual));
    }
  }

  void expect_collective(antlr4::ParserRuleContext *ctx, dataflow_type expected,
                         const std::string &what) {
    input_constraint value = inference.infer(ctx);
    if (value.forced_type.has_value() && *value.forced_type != expected) {
      type_fail(venv, ctx,
                what + ": expected " + type_name(expected) + ", got " +
                    type_name(*value.forced_type));
    }
    inference.require(ctx, value, expected);
  }

  void check_suffixes(ChipsParser::SuffixesContext *ctx) {
    for (ChipsParser::ExprContext *e : ctx->expr()) {
      expect(e, dataflow_type::INT, "array index");
    }
  }

  void check_suffixes(ChipsParser::C_suffixesContext *ctx) {
    inference.check_suffixes(ctx);
  }

  dataflow_type same_type(antlr4::ParserRuleContext *ctx,
                          antlr4::tree::ParseTree *l,
                          antlr4::tree::ParseTree *r) {
    dataflow_type left = type_of(l);
    dataflow_type right = type_of(r);
    if (left != right) {
      type_fail(venv, ctx,
                "operands must have the same type, got " + type_name(left) +
                    " and " + type_name(right));
    }
    return left;
  }

  dataflow_type numeric_operands(antlr4::ParserRuleContext *ctx,
                                 antlr4::tree::ParseTree *l,
                                 antlr4::tree::ParseTree *r) {
    dataflow_type type = same_type(ctx, l, r);
    if (!is_numeric(type)) {
      type_fail(venv, ctx, "numeric operands expected, got " + type_name(type));
    }
    return type;
  }

  void bool_operands(antlr4::ParserRuleContext *ctx, antlr4::tree::ParseTree *l,
                     antlr4::tree::ParseTree *r) {
    if (same_type(ctx, l, r) != dataflow_type::BOOL) {
      type_fail(venv, ctx, "bool operands expected");
    }
  }

  dataflow_type cast_target(ChipsParser::Df_typeContext *type,
                            antlr4::ParserRuleContext *ctx) {
    if (dynamic_cast<ChipsParser::IntTypeContext *>(type) != nullptr) {
      return dataflow_type::INT;
    }
    if (dynamic_cast<ChipsParser::FloatTypeContext *>(type) != nullptr) {
      return dataflow_type::FLOAT;
    }
    type_fail(venv, ctx, "cannot cast to bool");
  }

  void check_iterable_function(antlr4::ParserRuleContext *ctx,
                               const std::string &name, std::size_t count) {
    if (name != "range" && name != "zeros" && name != "ones") {
      type_fail(venv, ctx, "cannot iterate over the result of '" + name + "'");
    }
    if (count != 1) {
      type_fail(venv, ctx, "'" + name + "' takes exactly one int parameter");
    }
  }

  s_expr_info block_output(antlr4::ParserRuleContext *ctx,
                           const std::string &definition,
                           const std::string &output) {
    if (auto *channel = venv.lookup_channel(definition, output)) {
      return {true, false, std::nullopt, channel->get_variable()};
    }
    if (auto type = venv.lookup_actuator(definition, output)) {
      return {false, true, type, ""};
    }
    if (auto type = venv.lookup_output(definition, output)) {
      return {false, false, type, ""};
    }
    type_fail(venv, ctx,
              "'" + output +
                  "' is neither an output, an actuator nor a channel of '" +
                  definition + "'");
  }

  dataflow_type
  same_output_type(const std::string &name,
                   const std::vector<ChipsParser::ExprContext *> &exprs) {
    dataflow_type type = type_of(exprs.front());
    for (std::size_t i = 1; i < exprs.size(); ++i) {
      expect(exprs[i], type, "output '" + name + "'");
    }
    return type;
  }

  std::any visitIntType(ChipsParser::IntTypeContext *) {
    return dataflow_type::INT;
  }
  std::any visitFloatType(ChipsParser::FloatTypeContext *) {
    return dataflow_type::FLOAT;
  }
  std::any visitBoolType(ChipsParser::BoolTypeContext *) {
    return dataflow_type::BOOL;
  }

  std::any visitLT(ChipsParser::LTContext *ctx) {
    numeric_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitGT(ChipsParser::GTContext *ctx) {
    numeric_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitLEQ(ChipsParser::LEQContext *ctx) {
    numeric_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitGEQ(ChipsParser::GEQContext *ctx) {
    numeric_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitNEQ(ChipsParser::NEQContext *ctx) {
    same_type(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitEQ(ChipsParser::EQContext *ctx) {
    same_type(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitAND(ChipsParser::ANDContext *ctx) {
    bool_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitOR(ChipsParser::ORContext *ctx) {
    bool_operands(ctx, ctx->expr0(), ctx->expr());
    return dataflow_type::BOOL;
  }

  std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx) {
    return visit(ctx->expr0());
  }

  std::any visitPLUS(ChipsParser::PLUSContext *ctx) {
    return numeric_operands(ctx, ctx->expr01(), ctx->expr0());
  }

  std::any visitSUB(ChipsParser::SUBContext *ctx) {
    return numeric_operands(ctx, ctx->expr01(), ctx->expr0());
  }

  std::any visitPassExpr01(ChipsParser::PassExpr01Context *ctx) {
    return visit(ctx->expr01());
  }

  std::any visitNegate(ChipsParser::NegateContext *ctx) {
    dataflow_type type = type_of(ctx->expr1());
    return type;
  }

  std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx) {
    return visit(ctx->expr1());
  }

  std::any visitMULT(ChipsParser::MULTContext *ctx) {
    return numeric_operands(ctx, ctx->expr2(), ctx->expr1());
  }

  std::any visitDIV(ChipsParser::DIVContext *ctx) {
    return numeric_operands(ctx, ctx->expr2(), ctx->expr1());
  }

  std::any visitMOD(ChipsParser::MODContext *ctx) {
    if (same_type(ctx, ctx->expr2(), ctx->expr1()) != dataflow_type::INT) {
      type_fail(venv, ctx, "modulo needs int operands");
    }
    return dataflow_type::INT;
  }

  std::any visitNOT(ChipsParser::NOTContext *ctx) {
    expect(ctx->expr2(), dataflow_type::BOOL, "'!' operand");
    return dataflow_type::BOOL;
  }

  std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx) {
    return visit(ctx->expr2());
  }

  std::any visitIntLiteral(ChipsParser::IntLiteralContext *) {
    return dataflow_type::INT;
  }
  std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *) {
    return dataflow_type::FLOAT;
  }
  std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *) {
    return dataflow_type::BOOL;
  }

  std::any visitVar(ChipsParser::VarContext *ctx) {
    check_suffixes(ctx->suffixes());
    return resolve_variable(venv, ctx->IDENTIFIER()->getText(), ctx);
  }

  std::any visitParens(ChipsParser::ParensContext *ctx) {
    return visit(ctx->expr());
  }

  std::any visitVarContext(ChipsParser::VarContextContext *ctx) {
    check_suffixes(ctx->suffixes());
    return resolve_variable(venv, "ctx." + ctx->IDENTIFIER()->getText(), ctx);
  }

  std::any visitFunction(ChipsParser::FunctionContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    std::vector<ChipsParser::ExprContext *> args = ctx->expr();
    if (name == "range" || name == "zeros" || name == "ones") {
      if (args.size() != 1) {
        type_fail(venv, ctx, "'" + name + "' takes exactly one int parameter");
      }
      expect(args[0], dataflow_type::INT, "'" + name + "' parameter");
      return dataflow_type::INT;
    }
    if (name == "randin01") {
      if (!args.empty()) {
        type_fail(venv, ctx, "'randin01' takes no parameter");
      }
      return dataflow_type::FLOAT;
    }
    if (name == "is_fresh") {
      if (args.size() != 1) {
        type_fail(venv, ctx, "'is_fresh' takes exactly one parameter");
      }
      type_of(args[0]);
      return dataflow_type::BOOL;
    }
    type_fail(venv, ctx, "unknown function '" + name + "'");
  }

  std::any visitCastAs(ChipsParser::CastAsContext *ctx) {
    return visit(ctx->cast());
  }

  std::any visitCast(ChipsParser::CastContext *ctx) {
    dataflow_type target = cast_target(ctx->df_type(), ctx);
    dataflow_type operand = type_of(ctx->expr());
    if (!is_numeric(operand)) {
      type_fail(venv, ctx,
                "cast needs a numeric operand, got " + type_name(operand));
    }
    return target;
  }

  std::any visitLoop_in(ChipsParser::Loop_inContext *ctx) {
    check_suffixes(ctx->suffixes());
    std::string name = ctx->IDENTIFIER()->getText();
    if (ctx->L_PARENTH() == nullptr) {
      return resolve_variable(venv, name, ctx);
    }
    check_iterable_function(ctx, name, ctx->expr().size());
    expect(ctx->expr(0), dataflow_type::INT, "'" + name + "' parameter");
    return dataflow_type::INT;
  }

  std::any visitC_loop_in(ChipsParser::C_loop_inContext *ctx) {
    check_suffixes(ctx->c_suffixes());
    std::string name = ctx->IDENTIFIER()->getText();
    if (ctx->L_PARENTH() == nullptr) {
      return resolve_variable(venv, name, ctx);
    }
    check_iterable_function(ctx, name, ctx->c_expr().size());
    expect_collective(ctx->c_expr(0), dataflow_type::INT,
                      "'" + name + "' parameter");
    return dataflow_type::INT;
  }

  std::any
  visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx) {
    check_suffixes(ctx->suffixes());
    return type_of(ctx->df_type());
  }

  std::any
  visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx) {
    check_suffixes(ctx->suffixes());
    return type_of(ctx->df_type());
  }

  std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) {
    dataflow_type declared = type_of(ctx->df_type());
    check_suffixes(ctx->suffixes());
    if (ctx->expr() != nullptr) {
      expect(ctx->expr(), declared,
             "default value of parameter '" + ctx->IDENTIFIER()->getText() +
                 "'");
    }
    return declared;
  }

  std::any
  visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) {
    dataflow_type declared = type_of(ctx->pdf_parameter_type());
    if (ctx->expr() != nullptr) {
      expect(ctx->expr(), declared,
             "default value of parameter '" + ctx->IDENTIFIER()->getText() +
                 "'");
    }
    return declared;
  }

  std::any visitNamed_output(ChipsParser::Named_outputContext *ctx) {
    return same_output_type(ctx->IDENTIFIER()->getText(), ctx->expr());
  }

  std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) {
    return same_output_type(ctx->IDENTIFIER()->getText(), ctx->expr());
  }

  std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) {
    return visit(ctx->named_output());
  }

  std::any
  visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx) {
    dataflow_type declared = type_of(ctx->df_type());
    check_suffixes(ctx->suffixes());
    if (ctx->expr() != nullptr) {
      expect(ctx->expr(), declared,
             "initial value of '" + ctx->IDENTIFIER()->getText() + "'");
    }
    return {};
  }

  std::any
  visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx) {
    return visit(ctx->statement());
  }

  std::any
  visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx) {
    dataflow_type declared = type_of(ctx->df_type());
    check_suffixes(ctx->suffixes());
    if (ctx->expr() != nullptr) {
      expect(ctx->expr(), declared,
             "initial value of '" + ctx->IDENTIFIER()->getText() + "'");
    }
    return {};
  }

  std::any
  visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    dataflow_type expected = resolve_variable(venv, name, ctx);
    check_suffixes(ctx->suffixes());
    expect(ctx->expr(), expected, "assignment to '" + name + "'");
    return {};
  }

  std::any visitStatementContextualAssignment(
      ChipsParser::StatementContextualAssignmentContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    dataflow_type expected = resolve_variable(venv, "ctx." + name, ctx);
    check_suffixes(ctx->suffixes());
    expect(ctx->expr(), expected, "assignment to 'ctx." + name + "'");
    return {};
  }

  std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx) {
    return visit(ctx->loop_statement());
  }

  std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx) {
    visit(ctx->loop_in());
    return {};
  }

  std::any visitStatementIf(ChipsParser::StatementIfContext *ctx) {
    return visit(ctx->if_statement());
  }

  std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) {
    return visit(ctx->if_else_statement());
  }

  std::any visitIf_statement(ChipsParser::If_statementContext *ctx) {
    expect(ctx->expr(), dataflow_type::BOOL, "if condition");
    return {};
  }

  std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) {
    return visit(ctx->if_statement());
  }

  std::any
  visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) {
    dataflow_type declared = type_of(ctx->df_type());
    check_suffixes(ctx->c_suffixes());
    expect_collective(ctx->c_expr(), declared,
                      "default value of accumulator '" +
                          ctx->IDENTIFIER()->getText() + "'");
    return declared;
  }

  std::any
  visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx) {
    dataflow_type declared = type_of(ctx->df_type());
    check_suffixes(ctx->c_suffixes());
    if (ctx->c_expr() != nullptr) {
      expect_collective(ctx->c_expr(), declared,
                        "initial value of '" + ctx->IDENTIFIER()->getText() +
                            "'");
    }
    return declared;
  }

  std::any visitCollectiveVariableDeclaration(
      ChipsParser::CollectiveVariableDeclarationContext *ctx) {
    return visit(ctx->cdf_full_declaration());
  }

  std::any
  visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    dataflow_type expected = resolve_variable(venv, name, ctx);
    check_suffixes(ctx->c_suffixes());
    expect_collective(ctx->c_expr(), expected, "assignment to '" + name + "'");
    return {};
  }

  std::any
  visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    dataflow_type expected = resolve_variable(venv, "ctx." + name, ctx);
    check_suffixes(ctx->c_suffixes());
    expect_collective(ctx->c_expr(), expected,
                      "assignment to 'ctx." + name + "'");
    return {};
  }

  std::any visitCollectiveLoopStatement(
      ChipsParser::CollectiveLoopStatementContext *ctx) {
    return visit(ctx->c_loop_statement());
  }

  std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) {
    visit(ctx->c_loop_in());
    return {};
  }

  std::any
  visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx) {
    return visit(ctx->c_if_statement());
  }

  std::any visitCollectiveIfElseStatement(
      ChipsParser::CollectiveIfElseStatementContext *ctx) {
    return visit(ctx->c_if_else_statement());
  }

  std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx) {
    expect_collective(ctx->c_expr(), dataflow_type::BOOL, "if condition");
    return {};
  }

  std::any
  visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) {
    return visit(ctx->c_if_statement());
  }

  std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) {
    for (ChipsParser::C_exprContext *e : ctx->c_expr()) {
      inference.infer(e);
    }
    return {};
  }

  std::any visitC_default_output(ChipsParser::C_default_outputContext *ctx) {
    for (ChipsParser::C_exprContext *e : ctx->c_expr()) {
      inference.infer(e);
    }
    return {};
  }

  std::any
  visitC_channeled_output(ChipsParser::C_channeled_outputContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    if (venv.lookup_channel(venv.m_support_name, name) == nullptr) {
      type_fail(venv, ctx,
                "channel '" + name + "' is not declared in node '" +
                    venv.m_support_name + "'");
    }
    for (ChipsParser::C_exprContext *e : ctx->c_expr()) {
      inference.infer(e);
    }
    return {};
  }

  std::any visitRegularStatement(ChipsParser::RegularStatementContext *ctx) {
    return visit(ctx->statement());
  }

  std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) {
    return visit(ctx->s_loop_statement());
  }

  std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) {
    visit(ctx->s_suffixable_expr());
    return {};
  }

  std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx) {
    return visit(ctx->s_if_statement());
  }

  std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) {
    return visit(ctx->s_if_else_statement());
  }

  std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx) {
    expect(ctx->expr(), dataflow_type::BOOL, "if condition");
    return {};
  }

  std::any
  visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) {
    return visit(ctx->s_if_statement());
  }

  std::any visitSSuffixableVariableExpression(
      ChipsParser::SSuffixableVariableExpressionContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    if (!venv.is_block(name)) {
      resolve_variable(venv, name, ctx);
    }
    return {};
  }

  std::any visitSSuffixableFunctionCallExpression(
      ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    if (ctx->L_PARENTH() == nullptr) {
      if (!venv.is_block(name)) {
        resolve_variable(venv, name, ctx);
      }
      return {};
    }
    check_iterable_function(ctx, name, ctx->expr().size());
    expect(ctx->expr(0), dataflow_type::INT, "'" + name + "' parameter");
    return {};
  }

  std::any visitSSuffixableBlockOutputExpression(
      ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) {
    type_fail(venv, ctx,
              "the output of a functional block cannot be iterated on in the "
              "system section");
  }

  std::any visitBlock(ChipsParser::BlockContext *ctx) {
    check_suffixes(ctx->suffixes());
    return venv.lookup_block(ctx->IDENTIFIER()->getText(), ctx);
  }

  std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) {
    check_suffixes(ctx->suffixes());
    std::string definition = ctx->IDENTIFIER(0)->getText();
    if (!venv.definition_exists(definition)) {
      type_fail(venv, ctx,
                "definition '" + definition +
                    "' is not defined before this point");
    }
    return {};
  }

  std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) {
    for (std::size_t i = 0; i < 2; ++i) {
      check_suffixes(ctx->suffixes(i));
      venv.lookup_block(ctx->IDENTIFIER(i)->getText(), ctx);
    }
    return {};
  }

  std::any visitImplementationStatement(
      ChipsParser::ImplementationStatementContext *ctx) {
    for (std::size_t i = 0; i < 2; ++i) {
      check_suffixes(ctx->suffixes(i));
    }
    return {};
  }

  std::any
  visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx) {
    auto block =
        std::any_cast<std::pair<block_type, std::string>>(visit(ctx->block()));
    return block_output(ctx, block.second, ctx->IDENTIFIER()->getText());
  }

  std::any visitSCollectiveCastExpression(
      ChipsParser::SCollectiveCastExpressionContext *ctx) {
    venv.lookup_collective(ctx->collective_operation()->IDENTIFIER()->getText(),
                           ctx);
    auto block =
        std::any_cast<std::pair<block_type, std::string>>(visit(ctx->block()));
    s_expr_info inner =
        block_output(ctx, block.second, ctx->IDENTIFIER()->getText());
    if (inner.is_channel) {
      type_fail(venv, ctx,
                "a collective operation cannot be applied to a channel");
    }
    return inner;
  }

  std::any
  visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) {
    s_expr_info info;
    info.type = type_of(ctx->expr());
    return info;
  }

  std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) {
    auto block =
        std::any_cast<std::pair<block_type, std::string>>(visit(ctx->block()));
    const std::string &definition = block.second;
    std::string target = ctx->IDENTIFIER()->getText();
    s_expr_info source = std::any_cast<s_expr_info>(visit(ctx->s_expr()));

    if (auto *channel = venv.lookup_channel(definition, target)) {
      if (!source.is_channel) {
        type_fail(venv, ctx->s_expr(),
                  "channel '" + target + "' must be plugged to a channel");
      }
      if (channel->get_variable() != source.channel_type) {
        type_fail(venv, ctx->s_expr(),
                  "incompatible channel types: '" + channel->get_variable() +
                      "' and '" + source.channel_type + "'");
      }
      return {};
    }

    std::optional<dataflow_type> expected =
        venv.lookup_parameter(definition, target);
    if (!expected.has_value()) {
      type_fail(venv, ctx,
                "'" + target + "' is neither a parameter nor a channel of '" +
                    definition + "'");
    }
    if (source.is_channel) {
      type_fail(venv, ctx->s_expr(),
                "parameter '" + target + "' cannot be fed by a channel");
    }
    if (source.physical != venv.lookup_sensor(definition, target).has_value()) {
      type_fail(venv, ctx->s_expr(),
                "sensors must be fed by actuators, and other parameters by "
                "outputs or values");
    }
    if (*source.type != *expected) {
      type_fail(venv, ctx->s_expr(),
                "parameter '" + target + "' expects " + type_name(*expected) +
                    ", got " + type_name(*source.type));
    }
    return {};
  }
};