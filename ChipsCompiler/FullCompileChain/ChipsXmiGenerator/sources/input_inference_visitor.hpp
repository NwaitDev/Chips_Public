#pragma once

#include <any>
#include <optional>
#include <string>
#include <vector>

#include "../generated/ChipsBaseVisitor.h"
#include "../generated/ChipsParser.h"
#include "antlr4-runtime.h"

#include "type_utils.hpp"
#include "visitor_env.hpp"

class input_inference_visitor : public ChipsBaseVisitor {
public:
  visitor_env &venv;

  explicit input_inference_visitor(visitor_env &venv) : venv(venv) {}

  void reset(){}

  /**
 * @brief Infers the type constraint of a collective expression.
 *
 * Visits the given parse tree (any node of the c_expr rule family) and
 * returns what is known about its type once visited. Visiting can fix the
 * type of `input` for the current collective definition.
 *
 * @param tree Root of the collective expression to visit.
 * @return The constraint of the expression: `forced_type` is its type
 *         (empty while the expression is still free, i.e. made only of
 *         `input` or `stop`) and `contains_input` tells whether it holds an
 *         `input` whose type is still pending.
 * @throws std::runtime_error If the expression is ill-typed.
 */
  input_constraint infer(antlr4::tree::ParseTree *tree) {
    return std::any_cast<input_constraint>(visit(tree));
  }


  /**
 * @brief Fixes the type of `input` in the current collective definition.
 *
 * The type is stored in `visitor_env::expected_type_for_input`. All the uses
 * of `input` in a same collective definition must agree on this type.
 *
 * @param ctx  Parse tree node that forces the type (used for error reports).
 * @param type Type that `input` must have.
 * @throws std::runtime_error If `input` has already been fixed to a different
 *         type in the current collective definition.
 */
  void force_input(antlr4::ParserRuleContext *ctx, dataflow_type type) {
    if (venv.expected_type_for_input.has_value() &&
        *venv.expected_type_for_input != type) {
      type_fail(venv, ctx,
                "'input' is used as " +
                    type_name(*venv.expected_type_for_input) + " and as " +
                    type_name(type) + " in the same collective definition");
    }
    venv.expected_type_for_input = type;
  }

  /**
 * @brief Requires an expression to have a given type.
 *
 * If the type of the expression is known, it must equal `expected`. If the
 * expression is free and contains a pending `input`, the type of `input`
 * becomes `expected` (see force_input()). A free expression with no pending
 * `input` (e.g. `stop`) accepts any type and is left unchanged.
 *
 * @param ctx      Parse tree node of the expression (used for error reports).
 * @param c        Constraint previously inferred for the expression.
 * @param expected Type required by the context of the expression.
 * @throws std::runtime_error If the type of the expression differs from
 *         `expected`, or if `input` is already fixed to another type.
 */
  void require(antlr4::ParserRuleContext *ctx, const input_constraint &c,
               dataflow_type expected) {
    if (c.forced_type.has_value()) {
      if (*c.forced_type != expected) {
        type_fail(venv, ctx,
                  "expected " + type_name(expected) + ", got " +
                      type_name(*c.forced_type));
      }
      return;
    }
    if (c.contains_input) {
      force_input(ctx, expected);
    }
  }

  void require_numeric(antlr4::ParserRuleContext *ctx,
                       const input_constraint &c) {
    if (c.forced_type.has_value() && !is_numeric(*c.forced_type)) {
      type_fail(venv, ctx,
                "numeric operand expected, got " + type_name(*c.forced_type));
    }
  }

  /**
 * @brief Unifies the operands of an operator that needs both sides to have
 *        the same type.
 *
 * - Both operands typed: the types must be equal.
 * - One operand typed: the other one is required to have the same type, which
 *   fixes the type of `input` if it is pending there.
 * - Both operands free: the result stays free, and contains a pending `input`
 *   if one of the operands does.
 *
 * @param ctx Parse tree node of the operator (used for error reports).
 * @param l   Constraint of the left operand.
 * @param r   Constraint of the right operand.
 * @return The constraint shared by both operands (`forced_type` is empty only
 *         when both operands are free).
 * @throws std::runtime_error If the two operands have different types, or if
 *         fixing the type of `input` contradicts an earlier use.
 */
  input_constraint unify(antlr4::ParserRuleContext *ctx,
                         const input_constraint &l, const input_constraint &r) {
    if (l.forced_type.has_value() && r.forced_type.has_value()) {
      if (*l.forced_type != *r.forced_type) {
        type_fail(venv, ctx,
                  "operands must have the same type, got " +
                      type_name(*l.forced_type) + " and " +
                      type_name(*r.forced_type));
      }
      return {false, l.forced_type};
    }
    if (l.forced_type.has_value()) {
      require(ctx, r, *l.forced_type);
      return {false, l.forced_type};
    }
    if (r.forced_type.has_value()) {
      require(ctx, l, *r.forced_type);
      return {false, r.forced_type};
    }
    return {l.contains_input || r.contains_input, std::nullopt};
  }

  input_constraint relational(antlr4::ParserRuleContext *ctx,
                              antlr4::tree::ParseTree *l,
                              antlr4::tree::ParseTree *r) {
    require_numeric(ctx, unify(ctx, infer(l), infer(r)));
    return {false, dataflow_type::BOOL};
  }

  input_constraint equality(antlr4::ParserRuleContext *ctx,
                            antlr4::tree::ParseTree *l,
                            antlr4::tree::ParseTree *r) {
    unify(ctx, infer(l), infer(r));
    return {false, dataflow_type::BOOL};
  }

  input_constraint logical(antlr4::ParserRuleContext *ctx,
                           antlr4::tree::ParseTree *l,
                           antlr4::tree::ParseTree *r) {
    require(ctx, infer(l), dataflow_type::BOOL);
    require(ctx, infer(r), dataflow_type::BOOL);
    return {false, dataflow_type::BOOL};
  }

  input_constraint arithmetic(antlr4::ParserRuleContext *ctx,
                              antlr4::tree::ParseTree *l,
                              antlr4::tree::ParseTree *r) {
    input_constraint operands = unify(ctx, infer(l), infer(r));
    require_numeric(ctx, operands);
    return operands;
  }

  /**
 * @brief Checks the index expressions of an array access in a collective
 *        expression.
 *
 * Every index of the suffix list (`[i][j]...`) must be an integer. An index
 * made of a pending `input` fixes the type of `input` to `int`.
 *
 * @param ctx Suffix list to check.
 * @throws std::runtime_error If an index is not an integer.
 */
  void check_suffixes(ChipsParser::C_suffixesContext *ctx) {
    for (ChipsParser::C_stopless_exprContext *e : ctx->c_stopless_expr()) {
      require(e, infer(e), dataflow_type::INT);
    }
  }

  std::any
  visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx) {
    return infer(ctx->c_stopless_expr());
  }

  std::any visitStop(ChipsParser::StopContext *) {
    return input_constraint{false, std::nullopt};
  }

  std::any visitCLT(ChipsParser::CLTContext *ctx) {
    return relational(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCGT(ChipsParser::CGTContext *ctx) {
    return relational(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCLEQ(ChipsParser::CLEQContext *ctx) {
    return relational(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCGEQ(ChipsParser::CGEQContext *ctx) {
    return relational(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCNEQ(ChipsParser::CNEQContext *ctx) {
    return equality(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCEQ(ChipsParser::CEQContext *ctx) {
    return equality(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCAND(ChipsParser::CANDContext *ctx) {
    return logical(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitCOR(ChipsParser::CORContext *ctx) {
    return logical(ctx, ctx->c_stopless_expr0(), ctx->c_stopless_expr());
  }

  std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) {
    return infer(ctx->c_stopless_expr0());
  }

  std::any visitCPLUS(ChipsParser::CPLUSContext *ctx) {
    return arithmetic(ctx, ctx->c_stopless_expr01(), ctx->c_stopless_expr0());
  }

  std::any visitCSUB(ChipsParser::CSUBContext *ctx) {
    return arithmetic(ctx, ctx->c_stopless_expr01(), ctx->c_stopless_expr0());
  }

  std::any visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx) {
    return infer(ctx->c_stopless_expr01());
  }

  std::any visitCNegate(ChipsParser::CNegateContext *ctx) {
    input_constraint operand = infer(ctx->c_stopless_expr1());
    require_numeric(ctx, operand);
    return operand;
  }

  std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) {
    return infer(ctx->c_stopless_expr1());
  }

  std::any visitCMULT(ChipsParser::CMULTContext *ctx) {
    return arithmetic(ctx, ctx->c_stopless_expr2(), ctx->c_stopless_expr1());
  }

  std::any visitCDIV(ChipsParser::CDIVContext *ctx) {
    return arithmetic(ctx, ctx->c_stopless_expr2(), ctx->c_stopless_expr1());
  }

  std::any visitCMOD(ChipsParser::CMODContext *ctx) {
    require(ctx,
            unify(ctx, infer(ctx->c_stopless_expr2()),
                  infer(ctx->c_stopless_expr1())),
            dataflow_type::INT);
    return input_constraint{false, dataflow_type::INT};
  }

  std::any visitCNOT(ChipsParser::CNOTContext *ctx) {
    require(ctx, infer(ctx->c_stopless_expr2()), dataflow_type::BOOL);
    return input_constraint{false, dataflow_type::BOOL};
  }

  std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) {
    return infer(ctx->c_stopless_expr2());
  }

  std::any visitINPUT(ChipsParser::INPUTContext *) {
    return input_constraint{!venv.expected_type_for_input.has_value(), venv.expected_type_for_input};
  }

  std::any visitCINT(ChipsParser::CINTContext *) {
    return input_constraint{false, dataflow_type::INT};
  }

  std::any visitCFLOAT(ChipsParser::CFLOATContext *) {
    return input_constraint{false, dataflow_type::FLOAT};
  }

  std::any visitCBOOL(ChipsParser::CBOOLContext *) {
    return input_constraint{false, dataflow_type::BOOL};
  }

  std::any
  visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx) {
    check_suffixes(ctx->c_suffixes());
    return input_constraint{
        false, resolve_variable(venv, ctx->IDENTIFIER()->getText(), ctx)};
  }

  std::any
  visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx) {
    check_suffixes(ctx->c_suffixes());
    return input_constraint{
        false,
        resolve_variable(venv, "ctx." + ctx->IDENTIFIER()->getText(), ctx)};
  }

  std::any visitChanneledAccuExpression(
      ChipsParser::ChanneledAccuExpressionContext *ctx) {
    check_suffixes(ctx->c_suffixes());
    std::string channel = ctx->IDENTIFIER(0)->getText();
    if (venv.lookup_channel(venv.m_support_name, channel) == nullptr) {
      type_fail(venv, ctx,
                "channel '" + channel + "' is not declared in node '" +
                    venv.m_support_name + "'");
    }
    return input_constraint{
        false, resolve_variable(venv, ctx->IDENTIFIER(1)->getText(), ctx)};
  }

  std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx) {
    std::string name = ctx->IDENTIFIER()->getText();
    std::vector<ChipsParser::C_exprContext *> args = ctx->c_expr();
    if (name == "range" || name == "zeros" || name == "ones") {
      if (args.size() != 1) {
        type_fail(venv, ctx, "'" + name + "' takes exactly one int parameter");
      }
      require(args[0], infer(args[0]), dataflow_type::INT);
      return input_constraint{false, dataflow_type::INT};
    }
    if (name == "randin01") {
      if (!args.empty()) {
        type_fail(venv, ctx, "'randin01' takes no parameter");
      }
      return input_constraint{false, dataflow_type::FLOAT};
    }
    if (name == "imin" || name == "imax") {
      if (args.size()!= 2) {
        type_fail(venv, ctx, "'imin/imax' function takes exactly 2 parameters");
      }
      return input_constraint{false, dataflow_type::INT};
    }
    if (name == "fmin" || name == "fmax") {
      if (args.size()!= 2) {
        type_fail(venv, ctx, "'fmin/fmax' function takes exactly 2 parameters");
      }
      return input_constraint{false, dataflow_type::FLOAT};
    }
    if (name == "is_fresh") {
      if (args.size() != 1) {
        type_fail(venv, ctx, "'is_fresh' takes exactly one parameter");
      }
      infer(args[0]);
      return input_constraint{false, dataflow_type::BOOL};
    }
    type_fail(venv, ctx, "unknown function '" + name + "'");
  }

  std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx) {
    return infer(ctx->c_stopless_expr());
  }

  std::any visitCCastAs(ChipsParser::CCastAsContext *ctx) {
    return infer(ctx->c_cast());
  }

  std::any visitC_cast(ChipsParser::C_castContext *ctx) {
    dataflow_type target = dataflow_type::INT;
    if (dynamic_cast<ChipsParser::FloatTypeContext *>(ctx->df_type()) !=
        nullptr) {
      target = dataflow_type::FLOAT;
    } else if (dynamic_cast<ChipsParser::IntTypeContext *>(ctx->df_type()) ==
               nullptr) {
      type_fail(venv, ctx, "cannot cast to bool");
    }
    require_numeric(ctx, infer(ctx->c_stopless_expr()));
    return input_constraint{false, target};
  }
};