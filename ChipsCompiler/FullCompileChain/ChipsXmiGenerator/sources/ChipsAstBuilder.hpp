#pragma once

#include <any>
#include <string>
#include <vector>
#include <unordered_map>
#include <variant>

#include "antlr4-runtime.h"
#include "../generated/ChipsParser.h"
#include "../generated/ChipsBaseVisitor.h"

#include "metamodel_enums.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include "ast_variables.hpp"
#include "ast_system_specific.hpp"
#include "ast_lrxvalues.hpp"
#include "ast_statements.hpp"
#include "ast_inoutputs.hpp"
#include "ast_definitions.hpp"
#include "ast_program.hpp"

using namespace chips;

namespace chips_ast_builder_detail {

template<dataflow_type DFT> struct DftTag { static constexpr dataflow_type value = DFT; };

template<expression_env expenv, typename F>
rvalue_variant<expenv> dispatchDft(dataflow_type dft, F&& f) {
    switch (dft) {
        case dataflow_type::FLOAT: return rvalue_variant<expenv>{ f(DftTag<dataflow_type::FLOAT>{}) };
        case dataflow_type::BOOL:  return rvalue_variant<expenv>{ f(DftTag<dataflow_type::BOOL>{}) };
        default:                   return rvalue_variant<expenv>{ f(DftTag<dataflow_type::INT>{}) };
    }
}


template<expression_env expenv, typename F>
rvalue_variant<expenv> dispatchNumericDft(dataflow_type dft, F&& f) {
    if (dft == dataflow_type::FLOAT) return rvalue_variant<expenv>{ f(DftTag<dataflow_type::FLOAT>{}) };
    return rvalue_variant<expenv>{ f(DftTag<dataflow_type::INT>{}) };
}


template<expression_env expenv, typename F>
rvalue<dataflow_type::BOOL,expenv>* dispatchNumericToBool(dataflow_type dft, F&& f) {
    if (dft == dataflow_type::FLOAT) return f(DftTag<dataflow_type::FLOAT>{});
    return f(DftTag<dataflow_type::INT>{});
}

template<expression_env expenv, typename F>
rvalue<dataflow_type::BOOL,expenv>* dispatchAnyToBool(dataflow_type dft, F&& f) {
    switch (dft) {
        case dataflow_type::FLOAT: return f(DftTag<dataflow_type::FLOAT>{});
        case dataflow_type::BOOL:  return f(DftTag<dataflow_type::BOOL>{});
        default:                   return f(DftTag<dataflow_type::INT>{});
    }
}

struct VarSymbol {
    dataflow_type dft;
    void* ptr;
};

struct BlockSymbol {
    block_type bt;
    void* ptr;
    definition* def;
};

}

using namespace chips_ast_builder_detail;

class ChipsAstBuilder : public ChipsBaseVisitor {
public:
    program_node* build(ChipsParser::ProgramContext* ctx);

private:
    program_node m_program;

    std::unordered_map<std::string, definition*> m_definitions;
    std::unordered_map<std::string, collective_function_definition*> m_collectiveDefs;

    std::unordered_map<std::string, VarSymbol> m_locals;
    std::unordered_map<std::string, VarSymbol> m_contextuals;
    std::unordered_map<std::string, node_element_declaration<node_element::CHANNEL>*> m_channels;
    std::unordered_map<std::string, BlockSymbol> m_blocks;

    statement_env m_stmtEnv = statement_env::DEFINITION;
    expression_env m_exprEnv = expression_env::PRIMITIVE;
    dataflow_type m_expectedType = dataflow_type::INT;

    void resetLocalScope();

    static dataflow_type builtinFunctionType(const std::string& name);

    dataflow_type lookupVarType(const std::string& name);

    dataflow_type lookupContextualType(const std::string& name);

    template<dataflow_type dft, statement_env stenv>
    dataflow_declaration<dft,stenv>* declareVar(const std::string& name) {
        auto* decl = new dataflow_declaration<dft,stenv>(name);
        decl->m_variable.set_declaration(decl);
        return decl;
    }

    template<dataflow_type dft>
    typename DfTypeToContextualDeclType<dft>::type* declareContextual(const std::string& name) {
        using DeclT = typename DfTypeToContextualDeclType<dft>::type;
        auto* decl = new DeclT(contextual_variable<dft>(name), name);
        decl->m_variable_type.m_declaration = decl;
        return decl;
    }

    template<block_type bt>
    block_declaration<bt>* declareBlock(const std::string& name, typename BlockTypeToBlockDef<bt>::type* def) {
        auto* decl = new block_declaration<bt>(name);
        decl->set_definition(def);
        decl->m_variable.m_declaration = decl;
        return decl;
    }

    dataflow_type inferDfTypeCtx(ChipsParser::Df_typeContext* ctx);

    dataflow_type inferExpr2Type(ChipsParser::Expr2Context* ctx);

    dataflow_type inferExpr1Type(ChipsParser::Expr1Context* ctx);

    dataflow_type inferExpr01Type(ChipsParser::Expr01Context* ctx);

    dataflow_type inferExpr0Type(ChipsParser::Expr0Context* ctx);

    dataflow_type inferExprType(ChipsParser::ExprContext* ctx);

    dataflow_type inferCExpr2Type(ChipsParser::C_stopless_expr2Context* ctx);

    dataflow_type inferCExpr1Type(ChipsParser::C_stopless_expr1Context* ctx);

    dataflow_type inferCExpr01Type(ChipsParser::C_stopless_expr01Context* ctx);

    dataflow_type inferCExpr0Type(ChipsParser::C_stopless_expr0Context* ctx);

    dataflow_type inferCExprType(ChipsParser::C_stopless_exprContext* ctx);

    template<dataflow_type dft, expression_env expenv>
    rvalue<dft,expenv>* asType(const rvalue_variant<expenv>& v) {
        return std::get<rvalue<dft,expenv>*>(v);
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildDirect(dataflow_type dft, const std::string& text) {
        return dispatchDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            using CppT = typename DfTypeToCppType<DFT>::type;
            CppT v{};
            if constexpr (DFT == dataflow_type::BOOL) v = (text == "true");
            else if constexpr (DFT == dataflow_type::FLOAT) v = std::stod(text);
            else v = std::stoi(text);
            return static_cast<rvalue<DFT,expenv>*>(new direct<DFT,expenv>(v));
        });
    }

    template<expression_env expenv, template<dataflow_type,expression_env> class Op>
    rvalue_variant<expenv> buildBinaryNumeric(dataflow_type dft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchNumericDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<DFT,expenv>*>(new Op<DFT,expenv>(lp, rp));
        });
    }
    
    template<expression_env expenv>
    rvalue_variant<expenv> buildUminus(dataflow_type dft, rvalue_variant<expenv> operand) {
        return dispatchNumericDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto p = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(operand), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<DFT,expenv>*>(new uminus_operator<DFT,expenv>(p));
        });
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildPlus(dataflow_type dft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return buildBinaryNumeric<expenv, plus>(dft, lhs, rhs);
    }
    template<expression_env expenv>
    rvalue_variant<expenv> buildMinus(dataflow_type dft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return buildBinaryNumeric<expenv, minus>(dft, lhs, rhs);
    }
    template<expression_env expenv>
    rvalue_variant<expenv> buildMult(dataflow_type dft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return buildBinaryNumeric<expenv, mult>(dft, lhs, rhs);
    }
    template<expression_env expenv>
    rvalue_variant<expenv> buildDiv(dataflow_type dft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return buildBinaryNumeric<expenv, chips::div>(dft, lhs, rhs);
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildMod(rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        auto lp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(asType<dataflow_type::INT>(lhs), [](rvalue<dataflow_type::INT,expenv>*){});
        auto rp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(asType<dataflow_type::INT>(rhs), [](rvalue<dataflow_type::INT,expenv>*){});
        rvalue<dataflow_type::INT,expenv>* r = new mod<expenv>(lp, rp);
        return rvalue_variant<expenv>{ r };
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCastAs(dataflow_type target, dataflow_type operandDft, rvalue_variant<expenv> operand) {
        return dispatchDft<expenv>(target, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            return dispatchNumericToRvalueSameEnv<expenv,DFT>(operandDft, operand);
        });
    }

    template<expression_env expenv, dataflow_type target>
    rvalue<target,expenv>* dispatchNumericToRvalueSameEnv(dataflow_type operandDft, rvalue_variant<expenv> operand) {
        if (operandDft == dataflow_type::FLOAT) {
            auto p = std::shared_ptr<rvalue<dataflow_type::FLOAT,expenv>>(asType<dataflow_type::FLOAT>(operand), [](rvalue<dataflow_type::FLOAT,expenv>*){});
            return new cast_as<target,expenv>(p);
        }
        auto p = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(asType<dataflow_type::INT>(operand), [](rvalue<dataflow_type::INT,expenv>*){});
        return new cast_as<target,expenv>(p);
    }

    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildGt(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchNumericToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new gt<expenv,DFT>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildLt(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchNumericToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new lt<expenv,DFT>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildGeq(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchNumericToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new geq<expenv,DFT>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildLeq(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchNumericToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new leq<expenv,DFT>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildEq(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchAnyToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new eq<DFT,expenv>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildNeq(dataflow_type operandDft, rvalue_variant<expenv> lhs, rvalue_variant<expenv> rhs) {
        return dispatchAnyToBool<expenv>(operandDft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto lp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(lhs), [](rvalue<DFT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<DFT,expenv>>(asType<DFT>(rhs), [](rvalue<DFT,expenv>*){});
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(new neq<DFT,expenv>(lp, rp));
        });
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildOr(rvalue<dataflow_type::BOOL,expenv>* lhs, rvalue<dataflow_type::BOOL,expenv>* rhs) {
        auto lp = std::shared_ptr<rvalue<dataflow_type::BOOL,expenv>>(lhs, [](rvalue<dataflow_type::BOOL,expenv>*){});
        auto rp = std::shared_ptr<rvalue<dataflow_type::BOOL,expenv>>(rhs, [](rvalue<dataflow_type::BOOL,expenv>*){});
        return new or_operator<expenv>(lp, rp);
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildAnd(rvalue<dataflow_type::BOOL,expenv>* lhs, rvalue<dataflow_type::BOOL,expenv>* rhs) {
        auto lp = std::shared_ptr<rvalue<dataflow_type::BOOL,expenv>>(lhs, [](rvalue<dataflow_type::BOOL,expenv>*){});
        auto rp = std::shared_ptr<rvalue<dataflow_type::BOOL,expenv>>(rhs, [](rvalue<dataflow_type::BOOL,expenv>*){});
        return new and_operator<expenv>(lp, rp);
    }
    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildNot(rvalue<dataflow_type::BOOL,expenv>* operand) {
        auto p = std::shared_ptr<rvalue<dataflow_type::BOOL,expenv>>(operand, [](rvalue<dataflow_type::BOOL,expenv>*){});
        return new not_operator<expenv>(p);
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildVarExpr(dataflow_type dft, void* varPtr, std::vector<int_rvalue_expression_variant<expenv>> idx) {
        return dispatchDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto* v = static_cast<variable<expenv>*>(static_cast<dataflow_primitive_variable<DFT>*>(nullptr));
            (void)v;
            auto* typedVar = reinterpret_cast<typename DataflowVariableAliasType<expenv,DFT>::type*>(varPtr);
            return static_cast<rvalue<DFT,expenv>*>(new variable_expression<DFT,expenv>(typedVar, idx));
        });
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildContextualVarExpr(dataflow_type dft, void* varPtr, std::vector<int_rvalue_expression_variant<expenv>> idx) {
        return dispatchDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto* typedVar = reinterpret_cast<contextual_variable<DFT>*>(varPtr);
            return static_cast<rvalue<DFT,expenv>*>(new variable_contextual_expression<DFT,expenv>(typedVar, idx));
        });
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildFunctionCall(dataflow_type dft, const std::string& name, std::vector<rvalue_variant<expenv>> params) {
        return dispatchDft<expenv>(dft, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            std::vector<rvalue_variant<expenv>> p = params;
            return static_cast<rvalue<DFT,expenv>*>(new function<DFT,expenv>(name, p));
        });
    }

    template<expression_env expenv>
    int_rvalue_expression_variant<expenv> buildIndexExpr(ChipsParser::ExprContext* ctx) {
        auto* c0 = dynamic_cast<ChipsParser::PassExpr0Context*>(ctx);
        if (!c0) return int_rvalue_expression_variant<expenv>{ (direct<dataflow_type::INT,expenv>*) new direct<dataflow_type::INT,expenv>(0) };
        return buildIndexExpr0<expenv>(c0->expr0());
    }
    template<expression_env expenv>
    int_rvalue_expression_variant<expenv> buildIndexExpr0(ChipsParser::Expr0Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr01Context*>(ctx)) return buildIndexExpr01<expenv>(c->expr01());
        if (auto* c = dynamic_cast<ChipsParser::PLUSContext*>(ctx)) {
            auto l = buildIndexExpr01<expenv>(c->expr01());
            auto r = buildIndexExpr0<expenv>(c->expr0());
            auto lp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(l), [](rvalue<dataflow_type::INT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(r), [](rvalue<dataflow_type::INT,expenv>*){});
            return int_rvalue_expression_variant<expenv>{ new plus<dataflow_type::INT,expenv>(lp, rp) };
        }
        if (auto* c = dynamic_cast<ChipsParser::SUBContext*>(ctx)) {
            auto l = buildIndexExpr01<expenv>(c->expr01());
            auto r = buildIndexExpr0<expenv>(c->expr0());
            auto lp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(l), [](rvalue<dataflow_type::INT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(r), [](rvalue<dataflow_type::INT,expenv>*){});
            return int_rvalue_expression_variant<expenv>{ new minus<dataflow_type::INT,expenv>(lp, rp) };
        }
        return int_rvalue_expression_variant<expenv>{ (direct<dataflow_type::INT,expenv>*) new direct<dataflow_type::INT,expenv>(0) };
    }
    template<expression_env expenv>
    int_rvalue_expression_variant<expenv> buildIndexExpr01(ChipsParser::Expr01Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr1Context*>(ctx)) return buildIndexExpr1<expenv>(c->expr1());
        if (auto* c = dynamic_cast<ChipsParser::NegateContext*>(ctx)) {
            auto v = buildIndexExpr1<expenv>(c->expr1());
            auto p = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(v), [](rvalue<dataflow_type::INT,expenv>*){});
            return int_rvalue_expression_variant<expenv>{ new uminus_operator<dataflow_type::INT,expenv>(p) };
        }
        return int_rvalue_expression_variant<expenv>{ (direct<dataflow_type::INT,expenv>*) new direct<dataflow_type::INT,expenv>(0) };
    }
    template<expression_env expenv>
    int_rvalue_expression_variant<expenv> buildIndexExpr1(ChipsParser::Expr1Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr2Context*>(ctx)) return buildIndexExpr2<expenv>(c->expr2());
        if (auto* c = dynamic_cast<ChipsParser::MULTContext*>(ctx)) {
            auto l = buildIndexExpr2<expenv>(c->expr2());
            auto r = buildIndexExpr1<expenv>(c->expr1());
            auto lp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(l), [](rvalue<dataflow_type::INT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(r), [](rvalue<dataflow_type::INT,expenv>*){});
            return int_rvalue_expression_variant<expenv>{ new mult<dataflow_type::INT,expenv>(lp, rp) };
        }
        if (auto* c = dynamic_cast<ChipsParser::DIVContext*>(ctx)) {
            auto l = buildIndexExpr2<expenv>(c->expr2());
            auto r = buildIndexExpr1<expenv>(c->expr1());
            auto lp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(l), [](rvalue<dataflow_type::INT,expenv>*){});
            auto rp = std::shared_ptr<rvalue<dataflow_type::INT,expenv>>(idxToRvalue<expenv>(r), [](rvalue<dataflow_type::INT,expenv>*){});
            return int_rvalue_expression_variant<expenv>{ new chips::div<dataflow_type::INT,expenv>(lp, rp) };
        }
        return int_rvalue_expression_variant<expenv>{ (direct<dataflow_type::INT,expenv>*) new direct<dataflow_type::INT,expenv>(0) };
    }
    template<expression_env expenv>
    int_rvalue_expression_variant<expenv> buildIndexExpr2(ChipsParser::Expr2Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::IntLiteralContext*>(ctx))
            return int_rvalue_expression_variant<expenv>{ new direct<dataflow_type::INT,expenv>(std::stoi(c->INT()->getText())) };
        if (auto* c = dynamic_cast<ChipsParser::VarContext*>(ctx)) {
            auto sym = m_locals.find(c->IDENTIFIER()->getText());
            if (sym != m_locals.end()) {
                auto* typedVar = reinterpret_cast<typename DataflowVariableAliasType<expenv,dataflow_type::INT>::type*>(sym->second.ptr);
                return int_rvalue_expression_variant<expenv>{ new variable_expression<dataflow_type::INT,expenv>(typedVar) };
            }
        }
        if (auto* c = dynamic_cast<ChipsParser::ParensContext*>(ctx)) return buildIndexExpr<expenv>(c->expr());
        return int_rvalue_expression_variant<expenv>{ (direct<dataflow_type::INT,expenv>*) new direct<dataflow_type::INT,expenv>(0) };
    }
    template<expression_env expenv>
    rvalue<dataflow_type::INT,expenv>* idxToRvalue(int_rvalue_expression_variant<expenv> v) {
        return std::visit([](auto* p) -> rvalue<dataflow_type::INT,expenv>* { return p; }, v);
    }
    template<expression_env expenv>
    std::vector<int_rvalue_expression_variant<expenv>> buildSuffixIndices(ChipsParser::SuffixesContext* ctx) {
        std::vector<int_rvalue_expression_variant<expenv>> idx;
        if (!ctx) return idx;
        for (auto* e : ctx->expr()) idx.push_back(buildIndexExpr<expenv>(e));
        return idx;
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildExpr(ChipsParser::ExprContext* ctx) {
        dataflow_type dft = inferExprType(ctx);
        m_expectedType = dft;
        if (auto* c = dynamic_cast<ChipsParser::PassExpr0Context*>(ctx)) return buildExpr0<expenv>(c->expr0());
        dataflow_type opDft = inferExpr0Type(dynamic_cast<ChipsParser::LTContext*>(ctx) ? dynamic_cast<ChipsParser::LTContext*>(ctx)->expr0() : nullptr);
        rvalue<dataflow_type::BOOL,expenv>* res = nullptr;
        if (auto* c = dynamic_cast<ChipsParser::LTContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildLt<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::GTContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildGt<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::LEQContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildLeq<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::GEQContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildGeq<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::NEQContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildNeq<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::EQContext*>(ctx)) {
            opDft = inferExpr0Type(c->expr0());
            auto l = buildExpr0<expenv>(c->expr0());
            auto r = buildExpr<expenv>(c->expr());
            res = buildEq<expenv>(opDft, l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::ANDContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto l = asType<dataflow_type::BOOL>(buildExpr0<expenv>(c->expr0()));
            auto r = asType<dataflow_type::BOOL>(buildExpr<expenv>(c->expr()));
            res = buildAnd<expenv>(l, r);
        } else if (auto* c = dynamic_cast<ChipsParser::ORContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto l = asType<dataflow_type::BOOL>(buildExpr0<expenv>(c->expr0()));
            auto r = asType<dataflow_type::BOOL>(buildExpr<expenv>(c->expr()));
            res = buildOr<expenv>(l, r);
        }
        return rvalue_variant<expenv>{ res };
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildExpr0(ChipsParser::Expr0Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr01Context*>(ctx)) return buildExpr01<expenv>(c->expr01());
        dataflow_type dft = inferExpr0Type(ctx);
        if (auto* c = dynamic_cast<ChipsParser::PLUSContext*>(ctx)) {
            auto l = buildExpr01<expenv>(c->expr01());
            auto r = buildExpr0<expenv>(c->expr0());
            return buildPlus<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::SUBContext*>(ctx)) {
            auto l = buildExpr01<expenv>(c->expr01());
            auto r = buildExpr0<expenv>(c->expr0());
            return buildMinus<expenv>(dft, l, r);
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildExpr01(ChipsParser::Expr01Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr1Context*>(ctx)) return buildExpr1<expenv>(c->expr1());
        if (auto* c = dynamic_cast<ChipsParser::NegateContext*>(ctx)) {
            dataflow_type dft = inferExpr1Type(c->expr1());
            auto v = buildExpr1<expenv>(c->expr1());
            return buildUminus<expenv>(dft, v);
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildExpr1(ChipsParser::Expr1Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassExpr2Context*>(ctx)) return buildExpr2<expenv>(c->expr2());
        if (auto* c = dynamic_cast<ChipsParser::MULTContext*>(ctx)) {
            dataflow_type dft = inferExpr2Type(c->expr2());
            auto l = buildExpr2<expenv>(c->expr2());
            auto r = buildExpr1<expenv>(c->expr1());
            return buildMult<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::DIVContext*>(ctx)) {
            dataflow_type dft = inferExpr2Type(c->expr2());
            auto l = buildExpr2<expenv>(c->expr2());
            auto r = buildExpr1<expenv>(c->expr1());
            return buildDiv<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::MODContext*>(ctx)) {
            auto l = buildExpr2<expenv>(c->expr2());
            auto r = buildExpr1<expenv>(c->expr1());
            return buildMod<expenv>(l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::NOTContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto v = asType<dataflow_type::BOOL>(buildExpr2<expenv>(c->expr2()));
            return rvalue_variant<expenv>{ static_cast<rvalue<dataflow_type::BOOL,expenv>*>(buildNot<expenv>(v)) };
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildExpr2(ChipsParser::Expr2Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::IntLiteralContext*>(ctx)) return buildDirect<expenv>(dataflow_type::INT, c->INT()->getText());
        if (auto* c = dynamic_cast<ChipsParser::FloatLiteralContext*>(ctx)) return buildDirect<expenv>(dataflow_type::FLOAT, c->FLOAT()->getText());
        if (auto* c = dynamic_cast<ChipsParser::BoolLiteralContext*>(ctx)) return buildDirect<expenv>(dataflow_type::BOOL, c->BOOL()->getText());
        if (auto* c = dynamic_cast<ChipsParser::VarContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_locals.find(name);
            dataflow_type dft = it != m_locals.end() ? it->second.dft : m_expectedType;
            auto idx = buildSuffixIndices<expenv>(c->suffixes());
            return buildVarExpr<expenv>(dft, it != m_locals.end() ? it->second.ptr : nullptr, idx);
        }
        if (auto* c = dynamic_cast<ChipsParser::ParensContext*>(ctx)) return buildExpr<expenv>(c->expr());
        if (auto* c = dynamic_cast<ChipsParser::VarContextContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_contextuals.find(name);
            dataflow_type dft = it != m_contextuals.end() ? it->second.dft : m_expectedType;
            auto idx = buildSuffixIndices<expenv>(c->suffixes());
            return buildContextualVarExpr<expenv>(dft, it != m_contextuals.end() ? it->second.ptr : nullptr, idx);
        }
        if (auto* c = dynamic_cast<ChipsParser::FunctionContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            dataflow_type dft = builtinFunctionType(name);
            std::vector<rvalue_variant<expenv>> params;
            for (auto* e : c->expr()) params.push_back(buildExpr<expenv>(e));
            return buildFunctionCall<expenv>(dft, name, params);
        }
        if (auto* c = dynamic_cast<ChipsParser::CastAsContext*>(ctx)) {
            auto* castCtx = c->cast();
            dataflow_type target = inferDfTypeCtx(castCtx->df_type());
            dataflow_type opDft = inferExprType(castCtx->expr());
            auto operand = buildExpr<expenv>(castCtx->expr());
            return buildCastAs<expenv>(target, opDft, operand);
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue<dataflow_type::BOOL,expenv>* buildCStop() {
        return dispatchAnyToBool<expenv>(m_expectedType, [&](auto tag) {
            constexpr dataflow_type DFT = decltype(tag)::value;
            return static_cast<rvalue<dataflow_type::BOOL,expenv>*>(static_cast<rvalue<DFT,expenv>*>(new stop()));
        });
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCExpr(ChipsParser::C_exprContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::StopContext*>(ctx)) {
            return dispatchDft<expenv>(m_expectedType, [&](auto tag) {
                constexpr dataflow_type DFT = decltype(tag)::value;
                return static_cast<rvalue<DFT,expenv>*>(new stop());
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::CStoplessExpressionContext*>(ctx)) return buildCStopless<expenv>(c->c_stopless_expr());
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCStopless(ChipsParser::C_stopless_exprContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr0Context*>(ctx)) return buildCExpr0<expenv>(c->c_stopless_expr0());
        if (auto* c = dynamic_cast<ChipsParser::CLTContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildLt<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CGTContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildGt<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CLEQContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildLeq<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CGEQContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildGeq<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CNEQContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildNeq<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CEQContext*>(ctx)) {
            dataflow_type dft = inferCExpr0Type(c->c_stopless_expr0());
            auto l = buildCExpr0<expenv>(c->c_stopless_expr0());
            auto r = buildCStopless<expenv>(c->c_stopless_expr());
            return rvalue_variant<expenv>{ buildEq<expenv>(dft, l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CANDContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto l = asType<dataflow_type::BOOL>(buildCExpr0<expenv>(c->c_stopless_expr0()));
            auto r = asType<dataflow_type::BOOL>(buildCStopless<expenv>(c->c_stopless_expr()));
            return rvalue_variant<expenv>{ buildAnd<expenv>(l, r) };
        }
        if (auto* c = dynamic_cast<ChipsParser::CORContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto l = asType<dataflow_type::BOOL>(buildCExpr0<expenv>(c->c_stopless_expr0()));
            auto r = asType<dataflow_type::BOOL>(buildCStopless<expenv>(c->c_stopless_expr()));
            return rvalue_variant<expenv>{ buildOr<expenv>(l, r) };
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCExpr0(ChipsParser::C_stopless_expr0Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr01Context*>(ctx)) return buildCExpr01<expenv>(c->c_stopless_expr01());
        dataflow_type dft = inferCExpr0Type(ctx);
        if (auto* c = dynamic_cast<ChipsParser::CPLUSContext*>(ctx)) {
            auto l = buildCExpr01<expenv>(c->c_stopless_expr01());
            auto r = buildCExpr0<expenv>(c->c_stopless_expr0());
            return buildPlus<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::CSUBContext*>(ctx)) {
            auto l = buildCExpr01<expenv>(c->c_stopless_expr01());
            auto r = buildCExpr0<expenv>(c->c_stopless_expr0());
            return buildMinus<expenv>(dft, l, r);
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCExpr01(ChipsParser::C_stopless_expr01Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr1Context*>(ctx)) return buildCExpr1<expenv>(c->c_stopless_expr1());
        if (auto* c = dynamic_cast<ChipsParser::CNegateContext*>(ctx)) {
            dataflow_type dft = inferCExpr1Type(c->c_stopless_expr1());
            auto v = buildCExpr1<expenv>(c->c_stopless_expr1());
            return buildUminus<expenv>(dft, v);
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCExpr1(ChipsParser::C_stopless_expr1Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::PassCExpr2Context*>(ctx)) return buildCExpr2<expenv>(c->c_stopless_expr2());
        if (auto* c = dynamic_cast<ChipsParser::CMULTContext*>(ctx)) {
            dataflow_type dft = inferCExpr2Type(c->c_stopless_expr2());
            auto l = buildCExpr2<expenv>(c->c_stopless_expr2());
            auto r = buildCExpr1<expenv>(c->c_stopless_expr1());
            return buildMult<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::CDIVContext*>(ctx)) {
            dataflow_type dft = inferCExpr2Type(c->c_stopless_expr2());
            auto l = buildCExpr2<expenv>(c->c_stopless_expr2());
            auto r = buildCExpr1<expenv>(c->c_stopless_expr1());
            return buildDiv<expenv>(dft, l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::CMODContext*>(ctx)) {
            auto l = buildCExpr2<expenv>(c->c_stopless_expr2());
            auto r = buildCExpr1<expenv>(c->c_stopless_expr1());
            return buildMod<expenv>(l, r);
        }
        if (auto* c = dynamic_cast<ChipsParser::CNOTContext*>(ctx)) {
            m_expectedType = dataflow_type::BOOL;
            auto v = asType<dataflow_type::BOOL>(buildCExpr2<expenv>(c->c_stopless_expr2()));
            return rvalue_variant<expenv>{ static_cast<rvalue<dataflow_type::BOOL,expenv>*>(buildNot<expenv>(v)) };
        }
        return rvalue_variant<expenv>{};
    }

    template<expression_env expenv>
    rvalue_variant<expenv> buildCExpr2(ChipsParser::C_stopless_expr2Context* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::CINTContext*>(ctx)) return buildDirect<expenv>(dataflow_type::INT, c->INT()->getText());
        if (auto* c = dynamic_cast<ChipsParser::CFLOATContext*>(ctx)) return buildDirect<expenv>(dataflow_type::FLOAT, c->FLOAT()->getText());
        if (auto* c = dynamic_cast<ChipsParser::CBOOLContext*>(ctx)) return buildDirect<expenv>(dataflow_type::BOOL, c->BOOL()->getText());
        if (dynamic_cast<ChipsParser::INPUTContext*>(ctx)) {
            return dispatchDft<expenv>(m_expectedType, [&](auto tag) {
                constexpr dataflow_type DFT = decltype(tag)::value;
                return static_cast<rvalue<DFT,expenv>*>(new input());
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::CVariableExpressionContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_locals.find(name);
            dataflow_type dft = it != m_locals.end() ? it->second.dft : m_expectedType;
            std::vector<int_rvalue_expression_variant<expenv>> idx;
            return buildVarExpr<expenv>(dft, it != m_locals.end() ? it->second.ptr : nullptr, idx);
        }
        if (auto* c = dynamic_cast<ChipsParser::CtxVariableExpressionContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            auto it = m_contextuals.find(name);
            dataflow_type dft = it != m_contextuals.end() ? it->second.dft : m_expectedType;
            std::vector<int_rvalue_expression_variant<expenv>> idx;
            return buildContextualVarExpr<expenv>(dft, it != m_contextuals.end() ? it->second.ptr : nullptr, idx);
        }
        if (auto* c = dynamic_cast<ChipsParser::ChanneledAccuExpressionContext*>(ctx)) {
            std::string accuName = c->IDENTIFIER(1)->getText();
            auto it = m_locals.find(accuName);
            dataflow_type dft = it != m_locals.end() ? it->second.dft : m_expectedType;
            return dispatchDft<expenv>(dft, [&](auto tag) {
                constexpr dataflow_type DFT = decltype(tag)::value;
                auto* accu = reinterpret_cast<dataflow_collective_variable<DFT>*>(it != m_locals.end() ? it->second.ptr : nullptr);
                return static_cast<rvalue<DFT,expenv>*>(makeChanneledExpr<DFT>(accu));
            });
        }
        if (auto* c = dynamic_cast<ChipsParser::FunctionCallContext*>(ctx)) {
            std::string name = c->IDENTIFIER()->getText();
            dataflow_type dft = builtinFunctionType(name);
            std::vector<rvalue_variant<expenv>> params;
            for (auto* e : c->c_expr()) params.push_back(buildCExpr<expenv>(e));
            return buildFunctionCall<expenv>(dft, name, params);
        }
        if (auto* c = dynamic_cast<ChipsParser::CParenthesisContext*>(ctx)) return buildCStopless<expenv>(c->c_stopless_expr());
        if (auto* c = dynamic_cast<ChipsParser::CCastAsContext*>(ctx)) {
            auto* castCtx = c->c_cast();
            dataflow_type target = inferDfTypeCtx(castCtx->df_type());
            dataflow_type opDft = inferCExprType(castCtx->c_stopless_expr());
            auto operand = buildCStopless<expenv>(castCtx->c_stopless_expr());
            return buildCastAs<expenv>(target, opDft, operand);
        }
        return rvalue_variant<expenv>{};
    }

    template<dataflow_type dft>
    void* makeChanneledExpr(dataflow_collective_variable<dft>*) { return nullptr; }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildDeclarationStatement(ChipsParser::StatementDeclarationContext* ctx) {
        dataflow_type dft = inferDfTypeCtx(ctx->df_type());
        std::string name = ctx->IDENTIFIER()->getText();
        auto* decl = declareVar<dataflow_type::INT,stenv>(name);
        (void)decl;
        return typename SttEnvToSttVariant<stenv>::type{};
    }

    template<statement_env stenv, dataflow_type dft>
    dataflow_declaration<dft,stenv>* declareTypedVar(const std::string& name, ChipsParser::SuffixesContext* suf) {
        auto* decl = declareVar<dft,stenv>(name);
        auto idx = buildSuffixIndices<SttEnvToExpEnv<stenv>::value>(suf);
        for (auto& d : idx) decl->m_variable.m_dimensions.push_back(d);
        m_locals[name] = VarSymbol{ dft, &decl->m_variable };
        return decl;
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildStatementDeclarationTyped(ChipsParser::StatementDeclarationContext* ctx) {
        dataflow_type dft = inferDfTypeCtx(ctx->df_type());
        std::string name = ctx->IDENTIFIER()->getText();
        return dispatchStmtByDft<stenv>(dft, [&](auto tag) -> typename SttEnvToSttVariant<stenv>::type {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto* decl = declareTypedVar<stenv,DFT>(name, ctx->suffixes());
            if (ctx->expr()) {
                m_expectedType = DFT;
                auto init = buildExpr<SttEnvToExpEnv<stenv>::value>(ctx->expr());
                auto* lv = new variable_expression<DFT,SttEnvToExpEnv<stenv>::value>(&decl->m_variable);
                auto* asg = new dataflow_assignment<DFT,stenv>(lv, asType<DFT>(init));
                (void)asg;
            }
            return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::DECLARATION>*>(decl) };
        });
    }

    template<statement_env stenv, typename F>
    auto dispatchStmtByDft(dataflow_type dft, F&& f) -> decltype(f(DftTag<dataflow_type::INT>{})) {
        switch (dft) {
            case dataflow_type::FLOAT: return f(DftTag<dataflow_type::FLOAT>{});
            case dataflow_type::BOOL:  return f(DftTag<dataflow_type::BOOL>{});
            default:                   return f(DftTag<dataflow_type::INT>{});
        }
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildStatementAssignment(ChipsParser::StatementAssignmentContext* ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        auto it = m_locals.find(name);
        dataflow_type dft = it != m_locals.end() ? it->second.dft : dataflow_type::INT;
        return dispatchStmtByDft<stenv>(dft, [&](auto tag) -> typename SttEnvToSttVariant<stenv>::type {
            constexpr dataflow_type DFT = decltype(tag)::value;
            m_expectedType = DFT;
            auto idx = buildSuffixIndices<SttEnvToExpEnv<stenv>::value>(ctx->suffixes());
            auto* typedVar = reinterpret_cast<typename DataflowVariableAliasType<SttEnvToExpEnv<stenv>::value,DFT>::type*>(it != m_locals.end() ? it->second.ptr : nullptr);
            auto* lv = new variable_expression<DFT,SttEnvToExpEnv<stenv>::value>(typedVar, idx);
            auto rhs = buildExpr<SttEnvToExpEnv<stenv>::value>(ctx->expr());
            auto* asg = new dataflow_assignment<DFT,stenv>(lv, asType<DFT>(rhs));
            return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::ASSIGNMENT>*>(asg) };
        });
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext* ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        auto it = m_contextuals.find(name);
        dataflow_type dft = it != m_contextuals.end() ? it->second.dft : dataflow_type::INT;
        return dispatchStmtByDft<stenv>(dft, [&](auto tag) -> typename SttEnvToSttVariant<stenv>::type {
            constexpr dataflow_type DFT = decltype(tag)::value;
            m_expectedType = DFT;
            auto idx = buildSuffixIndices<SttEnvToExpEnv<stenv>::value>(ctx->suffixes());
            auto* typedVar = reinterpret_cast<contextual_variable<DFT>*>(it != m_contextuals.end() ? it->second.ptr : nullptr);
            auto* lv = new variable_contextual_expression<DFT,SttEnvToExpEnv<stenv>::value>(typedVar, idx);
            auto rhs = buildExpr<SttEnvToExpEnv<stenv>::value>(ctx->expr());
            auto* asg = new dataflow_assignment<DFT,stenv>(lv, asType<DFT>(rhs));
            return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::ASSIGNMENT>*>(asg) };
        });
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildStatement(ChipsParser::StatementContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::StatementDeclarationContext*>(ctx)) return buildStatementDeclarationTyped<stenv>(c);
        if (auto* c = dynamic_cast<ChipsParser::StatementAssignmentContext*>(ctx)) return buildStatementAssignment<stenv>(c);
        if (auto* c = dynamic_cast<ChipsParser::StatementContextualAssignmentContext*>(ctx)) return buildStatementContextualAssignment<stenv>(c);
        if (auto* c = dynamic_cast<ChipsParser::StatementIfContext*>(ctx)) return buildIfStatement<stenv>(c->if_statement());
        if (auto* c = dynamic_cast<ChipsParser::StatementIfElseContext*>(ctx)) return buildIfElseStatement<stenv>(c->if_else_statement());
        if (auto* c = dynamic_cast<ChipsParser::StatementLoopContext*>(ctx)) return buildLoopStatement<stenv>(c->loop_statement());
        return typename SttEnvToSttVariant<stenv>::type{};
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildIfStatement(ChipsParser::If_statementContext* ctx) {
        auto* node = new if_statement<stenv>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildExpr<SttEnvToExpEnv<stenv>::value>(ctx->expr()));
        for (auto* s : ctx->statement()) node->get_if_section().add_statement(buildStatement<stenv>(s));
        return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::IF>*>(node) };
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildIfElseStatement(ChipsParser::If_else_statementContext* ctx) {
        auto* node = new if_else_statement<stenv>();
        m_expectedType = dataflow_type::BOOL;
        node->get_condition() = asType<dataflow_type::BOOL>(buildExpr<SttEnvToExpEnv<stenv>::value>(ctx->if_statement()->expr()));
        for (auto* s : ctx->if_statement()->statement()) node->get_if_section().add_statement(buildStatement<stenv>(s));
        for (auto* s : ctx->statement()) node->get_else_section().add_statement(buildStatement<stenv>(s));
        return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::IF>*>(node) };
    }

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildLoopStatement(ChipsParser::Loop_statementContext* ctx) {
        std::string iterName = ctx->IDENTIFIER()->getText();
        dataflow_type dft = dataflow_type::INT;
        return dispatchStmtByDft<stenv>(dft, [&](auto tag) -> typename SttEnvToSttVariant<stenv>::type {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto* iterDecl = declareVar<DFT,stenv>(iterName);
            m_locals[iterName] = VarSymbol{ DFT, &iterDecl->m_variable };
            auto* node = new foreach_statement<stenv,DFT>();
            node->get_iterator() = *iterDecl;
            std::string fname = ctx->loop_in()->IDENTIFIER()->getText();
            std::vector<rvalue_variant<SttEnvToExpEnv<stenv>::value>> params;
            for (auto* e : ctx->loop_in()->expr()) params.push_back(buildExpr<SttEnvToExpEnv<stenv>::value>(e));
            auto* fn = new function<DFT,SttEnvToExpEnv<stenv>::value>(fname, params);
            node->get_iterable() = fn;
            for (auto* s : ctx->statement()) node->add_statement(buildStatement<stenv>(s));
            return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::FOREACH>*>(node) };
        });
    }

public:
    std::any visitProgram(ChipsParser::ProgramContext *ctx) override;

    std::any visitSystem(ChipsParser::SystemContext *ctx) override;

    std::any visitObject_def(ChipsParser::Object_defContext *ctx) override;

    std::any visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) override;
    std::any visitFunctionDefinition(ChipsParser::FunctionDefinitionContext *ctx) override;
    std::any visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx) override;
    std::any visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx) override;
    std::any visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) override;
    std::any visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) override;

    std::any visitImplementation_def(ChipsParser::Implementation_defContext *ctx) override;

    std::any visitNode_mapping(ChipsParser::Node_mappingContext *ctx) override;

    node_element_declaration<node_element::CHANNEL>* buildChannelDeclaration(ChipsParser::ChannelDeclarationContext* ctx);

    template<dataflow_type dft>
    typename DfTypeToContextualDeclType<dft>::type* buildContextualDeclTyped(ChipsParser::ContextualDeclarationContext* ctx, with_section& with) {
        std::string name = ctx->IDENTIFIER()->getText();
        auto* decl = declareContextual<dft>(name);
        auto idx = buildSuffixIndices<expression_env::PRIMITIVE>(ctx->suffixes());
        for (auto& d : idx) decl->m_variable_type.m_dimensions.push_back(d);
        m_contextuals[name] = VarSymbol{ dft, &decl->m_variable_type };
        if (ctx->expr()) {
            m_expectedType = dft;
            auto rhs = buildExpr<expression_env::PRIMITIVE>(ctx->expr());
            auto* lv = new variable_contextual_expression<dft,expression_env::PRIMITIVE>(&decl->m_variable_type);
            auto* asg = new dataflow_assignment<dft,statement_env::NODE>(lv, asType<dft>(rhs));
            with.add_statement(node_statement_variant{ static_cast<statement<statement_env::NODE,recurring_statement::ASSIGNMENT>*>(asg) });
        }
        return decl;
    }

    node_statement_variant buildWithStatement(ChipsParser::With_statementContext* ctx);

    std::any visitWith_section(ChipsParser::With_sectionContext *ctx) override;
    std::any visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) override;
    std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx) override;
    std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx) override;

    init_section buildInitSection(ChipsParser::Init_sectionContext* ctx);
    then_section buildThenSection(ChipsParser::Then_sectionContext* ctx);
    std::any visitInit_section(ChipsParser::Init_sectionContext *ctx) override;
    std::any visitThen_section(ChipsParser::Then_sectionContext *ctx) override;

    template<dataflow_type dft>
    function_parameter<dataflow_kind::LOGICAL,dft>* buildLogicalParam(ChipsParser::Df_parameter_declContext* ctx) {
        std::string name = ctx->IDENTIFIER()->getText();
        auto* decl = declareVar<dft,statement_env::DEFINITION>(name);
        auto idx = buildSuffixIndices<expression_env::PRIMITIVE>(ctx->suffixes());
        for (auto& d : idx) decl->m_variable.m_dimensions.push_back(d);
        m_locals[name] = VarSymbol{ dft, &decl->m_variable };
        std::optional<rvalue_variant<expression_env::PRIMITIVE>> defVal = std::nullopt;
        if (ctx->expr()) { m_expectedType = dft; defVal = buildExpr<expression_env::PRIMITIVE>(ctx->expr()); }
        return new function_parameter<dataflow_kind::LOGICAL,dft>(name, *decl, defVal);
    }

    function_parameter_variant buildDfParameterDecl(ChipsParser::Df_parameter_declContext* ctx);

    template<dataflow_type dft>
    function_parameter<dataflow_kind::PHYSICAL,dft>* buildPhysicalRegularParam(const std::string& name, ChipsParser::SuffixesContext* suf, ChipsParser::ExprContext* defExpr) {
        auto* decl = declareVar<dft,statement_env::DEFINITION>(name);
        auto idx = buildSuffixIndices<expression_env::PRIMITIVE>(suf);
        for (auto& d : idx) decl->m_variable.m_dimensions.push_back(d);
        m_locals[name] = VarSymbol{ dft, &decl->m_variable };
        std::optional<rvalue_variant<expression_env::PRIMITIVE>> defVal = std::nullopt;
        if (defExpr) { m_expectedType = dft; defVal = buildExpr<expression_env::PRIMITIVE>(defExpr); }
        return new function_parameter<dataflow_kind::PHYSICAL,dft>(name, *decl, defVal);
    }

    void buildPdfParameterDecl(ChipsParser::Pdf_parameter_declContext* ctx, std::vector<physical_parameter_variant>& params, std::vector<physical_parameter_variant>& sensors);

    std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) override;
    std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) override;
    std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx) override;
    std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx) override;
    std::any visitIntType(ChipsParser::IntTypeContext *ctx) override;
    std::any visitFloatType(ChipsParser::FloatTypeContext *ctx) override;
    std::any visitBoolType(ChipsParser::BoolTypeContext *ctx) override;

    template<dataflow_type dft>
    function_output<dataflow_kind::LOGICAL,dft>* buildLogicalOutputTyped(const std::string& name, const std::vector<ChipsParser::ExprContext*>& exprs) {
        m_expectedType = dft;
        auto* out = new function_output<dataflow_kind::LOGICAL,dft>(name, asType<dft>(buildExpr<expression_env::PRIMITIVE>(exprs[0])));
        for (size_t i = 1; i < exprs.size(); ++i) out->add_expression(buildExpr<expression_env::PRIMITIVE>(exprs[i]));
        return out;
    }
    template<dataflow_type dft>
    function_output<dataflow_kind::PHYSICAL,dft>* buildActuatorOutputTyped(const std::string& name, const std::vector<ChipsParser::ExprContext*>& exprs) {
        m_expectedType = dft;
        auto* out = new function_output<dataflow_kind::PHYSICAL,dft>(name, asType<dft>(buildExpr<expression_env::PRIMITIVE>(exprs[0])));
        for (size_t i = 1; i < exprs.size(); ++i) out->add_expression(buildExpr<expression_env::PRIMITIVE>(exprs[i]));
        return out;
    }

    function_output_variant buildNamedOutput(ChipsParser::Named_outputContext* ctx);

    std::any visitNamed_output(ChipsParser::Named_outputContext *ctx) override;
    std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) override;
    std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) override;

    std::any visitL_function_def(ChipsParser::L_function_defContext *ctx) override;

    std::any visitP_function_def(ChipsParser::P_function_defContext *ctx) override;

    std::any visitC_signature(ChipsParser::C_signatureContext *ctx) override;
    std::any visitC_keywords(ChipsParser::C_keywordsContext *ctx) override;

    template<dataflow_type dft>
    collective_parameter<dft>* buildCollectiveParamTyped(const std::string& name, ChipsParser::SuffixesContext* suf, ChipsParser::C_exprContext* defExpr) {
        auto* decl = declareVar<dft,statement_env::COLLECTIVE>(name);
        auto idx = buildSuffixIndices<expression_env::COLLECTIVE>(suf);
        for (auto& d : idx) decl->m_variable.m_dimensions.push_back(d);
        m_locals[name] = VarSymbol{ dft, &decl->m_variable };
        m_expectedType = dft;
        auto defVal = defExpr ? asType<dft>(buildCExpr<expression_env::COLLECTIVE>(defExpr)) : nullptr;
        return new collective_parameter<dft>(name, *decl, defVal);
    }

    collective_parameter_variant buildCdfDefaultedDecl(ChipsParser::Cdf_defaulted_declContext* ctx);

    std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) override;
    std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx) override;

    template<statement_env stenv>
    typename SttEnvToSttVariant<stenv>::type buildCollectiveDeclStatement(ChipsParser::Cdf_full_declarationContext* ctx) {
        dataflow_type dft = inferDfTypeCtx(ctx->df_type());
        std::string name = ctx->IDENTIFIER()->getText();
        return dispatchStmtByDft<stenv>(dft, [&](auto tag) -> typename SttEnvToSttVariant<stenv>::type {
            constexpr dataflow_type DFT = decltype(tag)::value;
            auto* decl = declareVar<DFT,stenv>(name);
            auto idx = buildSuffixIndices<SttEnvToExpEnv<stenv>::value>(ctx->suffixes());
            for (auto& d : idx) decl->m_variable.m_dimensions.push_back(d);
            m_locals[name] = VarSymbol{ DFT, &decl->m_variable };
            if (ctx->c_expr()) {
                m_expectedType = DFT;
                auto initv = buildCExpr<SttEnvToExpEnv<stenv>::value>(ctx->c_expr());
                auto* lv = new variable_expression<DFT,SttEnvToExpEnv<stenv>::value>(&decl->m_variable);
                auto* asg = new dataflow_assignment<DFT,stenv>(lv, asType<DFT>(initv));
                (void)asg;
            }
            return typename SttEnvToSttVariant<stenv>::type{ static_cast<statement<stenv,recurring_statement::DECLARATION>*>(decl) };
        });
    }

    typename SttEnvToSttVariant<statement_env::COLLECTIVE>::type buildCStatement(ChipsParser::C_statementContext* ctx);

    collective_statement_variant buildCIfStatement(ChipsParser::C_if_statementContext* ctx);
    collective_statement_variant buildCIfElseStatement(ChipsParser::C_if_else_statementContext* ctx);
    collective_statement_variant buildCLoopStatement(ChipsParser::C_loop_statementContext* ctx);

    std::any visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx) override;
    std::any visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx) override;
    std::any visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) override;
    std::any visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx) override;
    std::any visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx) override;
    std::any visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx) override;
    std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) override;
    std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx) override;
    std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) override;

    std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) override;
    std::any visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) override;

    std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) override;

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
    std::any visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx) override;
    std::any visitStop(ChipsParser::StopContext *ctx) override;
    std::any visitCLT(ChipsParser::CLTContext *ctx) override;
    std::any visitCGT(ChipsParser::CGTContext *ctx) override;
    std::any visitCLEQ(ChipsParser::CLEQContext *ctx) override;
    std::any visitCGEQ(ChipsParser::CGEQContext *ctx) override;
    std::any visitCNEQ(ChipsParser::CNEQContext *ctx) override;
    std::any visitCEQ(ChipsParser::CEQContext *ctx) override;
    std::any visitCAND(ChipsParser::CANDContext *ctx) override;
    std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx) override;
    std::any visitCINT(ChipsParser::CINTContext *ctx) override;
    std::any visitCFLOAT(ChipsParser::CFLOATContext *ctx) override;
    std::any visitCBOOL(ChipsParser::CBOOLContext *ctx) override;
    std::any visitINPUT(ChipsParser::INPUTContext *ctx) override;
    std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx) override;
    std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx) override;
    std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx) override;
    std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx) override;
    std::any visitCCastAs(ChipsParser::CCastAsContext *ctx) override;
    std::any visitC_cast(ChipsParser::C_castContext *ctx) override;
    std::any visitSuffixes(ChipsParser::SuffixesContext *ctx) override;
    std::any visitC_suffixes(ChipsParser::C_suffixesContext *ctx) override;
    std::any visitLoop_in(ChipsParser::Loop_inContext *ctx) override;
    std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx) override;
    std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) override;
    std::any visitIf_statement(ChipsParser::If_statementContext *ctx) override;
    std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx) override;
    std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) override;
    std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx) override;
    std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx) override;
    std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) override;
    std::any visitStatementIf(ChipsParser::StatementIfContext *ctx) override;

    template<block_type bt>
    block_declaration<bt>* buildBlockDeclTyped(const std::string& typeName, const std::string& varName) {
        auto dit = m_definitions.find(typeName);
        typename BlockTypeToBlockDef<bt>::type* def = dit != m_definitions.end() ? static_cast<typename BlockTypeToBlockDef<bt>::type*>(dit->second) : nullptr;
        auto* decl = declareBlock<bt>(varName, def);
        m_blocks[varName] = BlockSymbol{ bt, &decl->m_variable, def };
        return decl;
    }

    block_type blockTypeOfDefinition(const std::string& typeName);

    system_statement_variant buildObjectDeclaration(ChipsParser::ObjectDeclarationContext* ctx);

    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> buildBlockIndices(ChipsParser::SuffixesContext* suf);

    system_statement_variant buildFeedingStatement(ChipsParser::FeedingStatementContext* ctx);

    template<dataflow_kind dfk, dataflow_type dft>
    feeder<dfk,dft>* buildSExpr(ChipsParser::S_exprContext* ctx) {
        if (auto* c = dynamic_cast<ChipsParser::SBlockOutputExpressionContext*>(ctx)) {
            std::string blockName = c->block()->IDENTIFIER()->getText();
            std::string outName = c->IDENTIFIER()->getText();
            auto bit = m_blocks.find(blockName);
            functional_block_variant fbv;
            if (bit != m_blocks.end()) {
                if (bit->second.bt == block_type::LOGICAL) fbv = reinterpret_cast<block_variable<block_type::LOGICAL>*>(bit->second.ptr);
                else fbv = reinterpret_cast<block_variable<block_type::PHYSICAL>*>(bit->second.ptr);
            }
            function_output<dfk,dft>* out = nullptr;
            return new feeder_block_expression<dfk,dft>(fbv, out);
        }
        if (auto* c = dynamic_cast<ChipsParser::SCollectiveCastExpressionContext*>(ctx)) {
            std::string castName = c->collective_operation()->IDENTIFIER()->getText();
            auto cit = m_collectiveDefs.find(castName);
            std::string blockName = c->block()->IDENTIFIER()->getText();
            auto bit = m_blocks.find(blockName);
            feeder<dfk,dft> dummyFeed;
            (void)dummyFeed;
            return nullptr;
        }
        if (auto* c = dynamic_cast<ChipsParser::SRegularExpressionContext*>(ctx)) {
            m_expectedType = dft;
            auto v = buildExpr<expression_env::SYSTEM>(c->expr());
            return static_cast<feeder<dfk,dft>*>(static_cast<void*>(asType<dft>(v)));
        }
        return nullptr;
    }

    system_statement_variant buildLinkingStatement(ChipsParser::LinkingStatementContext* ctx);

    system_statement_variant buildSStatement(ChipsParser::S_statementContext* ctx);

    system_statement_variant buildSIfStatement(ChipsParser::S_if_statementContext* ctx);
    system_statement_variant buildSIfElseStatement(ChipsParser::S_if_else_statementContext* ctx);
    system_statement_variant buildSLoopStatement(ChipsParser::S_loop_statementContext* ctx);

    std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) override;
    std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) override;
    std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) override;
    std::any visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx) override;
    std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) override;
    std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) override;
    std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx) override;
    std::any visitRegularStatement(ChipsParser::RegularStatementContext *ctx) override;
    std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) override;
    std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx) override;
    std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) override;
    std::any visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx) override;
    std::any visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx) override;
    std::any visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) override;
    std::any visitCollective_operation(ChipsParser::Collective_operationContext *ctx) override;
    std::any visitBlock(ChipsParser::BlockContext *ctx) override;
    std::any visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx) override;
    std::any visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) override;
    std::any visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) override;
    std::any visitImplementationStatementFallback(ChipsParser::ImplementationStatementContext *ctx);
};
