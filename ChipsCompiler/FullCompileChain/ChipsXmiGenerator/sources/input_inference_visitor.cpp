#include <optional>
#include "../generated/ChipsBaseVisitor.h"
#include "../generated/ChipsParser.h"
#include "antlr4-runtime.h"

#include "metamodel_enums.hpp"

using namespace chips;

class input_inference_visitor : public ChipsBaseVisitor
{
    public:
    // data members
    

    // Methods
    std::optional<dataflow_type> constrain_type(
        const input_inference_visitor &b,
        antlr4::ParserRuleContext *ctx,
        const std::optional<dataflow_type> &actual,
        dataflow_type expected)
    {
        if (actual.has_value() && *actual != expected)
        {
            b.type_fail(ctx,
                        "expected " + type_name(expected) +
                            ", got " + type_name(*actual));
        }

        return expected;
    }

    input_constraint merge_input_constraints(
        antlr4::ParserRuleContext *ctx,
        const input_constraint &l,
        const input_constraint &r)
    {
        return {
            l.contains_input || r.contains_input,
            unify_types(*this, ctx, l.forced_type, r.forced_type)};
    }

    std::any visitCLT(ChipsParser::CLTContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr0()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr()).as<input_constraint>();
        auto result = merge_input_constraints(ctx, l, r);

        if (result.contains_input)
            result.forced_type = dataflow_type::INT;

        return result;
    }

    std::any visitCGT(ChipsParser::CGTContext *ctx)
    {
        return visitCLT(ctx);
    }

    std::any visitCLEQ(ChipsParser::CLEQContext *ctx)
    {
        return visitCLT(ctx);
    }

    std::any visitCGEQ(ChipsParser::CGEQContext *ctx)
    {
        return visitCLT(ctx);
    }

    std::any visitCNEQ(ChipsParser::CNEQContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr0()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr()).as<input_constraint>();
        return merge_input_constraints(ctx, l, r);
    }

    std::any visitCEQ(ChipsParser::CEQContext *ctx)
    {
        return visitCNEQ(ctx);
    }

    std::any visitCAND(ChipsParser::CANDContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr0()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr()).as<input_constraint>();
        auto result = merge_input_constraints(ctx, l, r);

        if (result.contains_input)
            result.forced_type = dataflow_type::BOOL;

        return result;
    }

    std::any visitCOR(ChipsParser::CORContext *ctx)
    {
        return visitCAND(ctx);
    }

    std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx)
    {
        return visit(ctx->c_stopless_expr0());
    }

    std::any visitCPLUS(ChipsParser::CPLUSContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr01()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr0()).as<input_constraint>();
        return merge_input_constraints(ctx, l, r);
    }

    std::any visitCSUB(ChipsParser::CSUBContext *ctx)
    {
        return visitCPLUS(ctx);
    }

    std::any visitPassCExpr01(ChipsParser::PassCExpr01Context *ctx)
    {
        return visit(ctx->c_stopless_expr01());
    }

    std::any visitCNegate(ChipsParser::CNegateContext *ctx)
    {
        return visit(ctx->c_stopless_expr1());
    }

    std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx)
    {
        return visit(ctx->c_stopless_expr1());
    }

    std::any visitCMULT(ChipsParser::CMULTContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr2()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr1()).as<input_constraint>();
        return merge_input_constraints(ctx, l, r);
    }

    std::any visitCDIV(ChipsParser::CDIVContext *ctx)
    {
        return visitCMULT(ctx);
    }

    std::any visitCMOD(ChipsParser::CMODContext *ctx)
    {
        auto l = visit(ctx->c_stopless_expr2()).as<input_constraint>();
        auto r = visit(ctx->c_stopless_expr1()).as<input_constraint>();
        auto result = merge_input_constraints(ctx, l, r);

        if (result.contains_input)
            result.forced_type = dataflow_type::INT;

        return result;
    }

    std::any visitCNOT(ChipsParser::CNOTContext *ctx)
    {
        auto result = visit(ctx->c_stopless_expr2()).as<input_constraint>();

        if (result.contains_input)
            result.forced_type = dataflow_type::BOOL;

        return result;
    }

    std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx)
    {
        return visit(ctx->c_stopless_expr2());
    }

    std::any visitINPUT(ChipsParser::INPUTContext *)
    {
        return input_constraint{true, std::nullopt};
    }

    std::any visitCINT(ChipsParser::CINTContext *)
    {
        return input_constraint{false, dataflow_type::INT};
    }

    std::any visitCFLOAT(ChipsParser::CFLOATContext *)
    {
        return input_constraint{false, dataflow_type::FLOAT};
    }

    std::any visitCBOOL(ChipsParser::CBOOLContext *)
    {
        return input_constraint{false, dataflow_type::BOOL};
    }

    std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx)
    {
        return input_constraint{
            false,
            lookup_variable(ctx->IDENTIFIER()->getText(), ctx)};
    }

    std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx)
    {
        return input_constraint{
            false,
            lookup_variable("ctx." + ctx->IDENTIFIER()->getText(), ctx)};
    }

    std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx)
    {
        return input_constraint{
            false,
            lookup_variable(ctx->IDENTIFIER(1)->getText(), ctx)};
    }

    std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx)
    {
        input_constraint result{false, std::nullopt};

        for (auto *arg : ctx->c_expr())
        {
            auto current = visit(arg).as<input_constraint>();
            result = merge_input_constraints(ctx, result, current);
        }

        return result;
    }

    std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx)
    {
        return visit(ctx->c_stopless_expr());
    }

    std::any visitCCastAs(ChipsParser::CCastAsContext *ctx)
    {
        return visit(ctx->c_cast());
    }

    void check_suffixes(ChipsParser::C_suffixesContext *ctx) const
    {
        for (ChipsParser::C_stopless_exprContext *e : ctx->c_stopless_expr())
        {
            std::optional<dataflow_type> t = infer_type(e);
            if (t.has_value() && *t != dataflow_type::INT)
            {
                type_fail(e, "array index must be int, got " + type_name(*t));
            }
        }
    }
};