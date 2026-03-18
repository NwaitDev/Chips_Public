#pragma once
// ============================================================
//  Interpreter.hpp
//  Visiteur d'AST ANTLR4 – évalue les expressions arithmétiques
//
//  NOTE : ANTLR4 ne génère visitXxx() QUE pour les alternatives
//  étiquetées (# Label). Les règles non-étiquetées (term, power,
//  unary, atom) n'ont PAS de visitXxx() dédié → on utilise visit().
// ============================================================
#include "ChipsBaseVisitor.h"
#include <unordered_map>
#include <string>
#include <variant>
#include <stdexcept>
#include <cmath>
#include <iostream>

// Valeur de runtime : entier 64-bit ou double
using Value = std::variant<long long, double>;

// ── utilitaires ────────────────────────────────────────────
inline double toDouble(const Value& v) {
    return std::visit([](auto x){ return static_cast<double>(x); }, v);
}

inline bool isDouble(const Value& v) {
    return std::holds_alternative<double>(v);
}

// ── helper : extraire une Value depuis std::any ────────────
inline Value asValue(std::any a) {
    return std::any_cast<Value>(a);
}

// ── Interpréteur ──────────────────────────────────────────
class Interpreter : public ChipsBaseVisitor {
public:
    std::unordered_map<std::string, Value> env;

    // std::any visitProgram(ChipsParser::ProgramContext* ctx) override {
    //     for(auto* stmt : ctx->expr()){
    //         visit(stmt);
    //         std::cout << std::endl;
    //     }
    //     return {};
    // }

    // std::any visitPLUS(ChipsParser::PLUSContext* ctx) override {
    //     Value left = asValue(visit(ctx->expr1()));
    //     std::cout << " + ";
    //     Value right = asValue(visit(ctx->expr0()));
    //     double a = toDouble(left), b = toDouble(right);
    //     return Value{a+b};
    // }

    // std::any visitSUB(ChipsParser::SUBContext* ctx) override {
    //     Value left = asValue(visit(ctx->expr1()));
    //     std::cout << " - ";
    //     Value right = asValue(visit(ctx->expr0()));
    //     double a = toDouble(left), b = toDouble(right);
    //     return Value{a-b};
    // }

    // std::any visitMULT(ChipsParser::MULTContext* ctx) override {
    //     Value left = asValue(visit(ctx->expr2()));
    //     std::cout << " * ";
    //     Value right = asValue(visit(ctx->expr1()));

    //     double a = toDouble(left), b = toDouble(right);
    //     return Value{a * b};
    // }

    // std::any visitDIV(ChipsParser::DIVContext* ctx) override {
    //     Value left = asValue(visit(ctx->expr2()));
    //     std::cout << " / ";
    //     Value right = asValue(visit(ctx->expr1()));

    //     double a = toDouble(left), b = toDouble(right);
    //     return Value{a / b};
    // }
    
    // std::any visitNegate(ChipsParser::NegateContext* ctx) override {
    //     std::cout << " - ";
    //     Value v = asValue(visit(ctx->expr0()));
    //     if (isDouble(v)) return Value{-toDouble(v)};
    //     return Value{-std::get<long long>(v)};
    // }

    // std::any visitIntLiteral(ChipsParser::IntLiteralContext* ctx) override {
    //     std::cout << std::stoll(ctx->INT()->getText());
    //     return Value{std::stoll(ctx->INT()->getText())};
    // }

    // std::any visitFloatLiteral(ChipsParser::FloatLiteralContext* ctx) override {
    //     std::cout << std::stod(ctx->FLOAT()->getText());
    //     return Value{std::stod(ctx->FLOAT()->getText())};
    // }

    // std::any visitParens(ChipsParser::ParensContext* ctx) override {
    //     return visit(ctx->expr());
    // }

    // std::any visitPassExpr(ChipsParser::PassExprContext* ctx) override {
    //     return visit(ctx->expr0());
    // }

    // std::any visitPassExpr0(ChipsParser::PassExpr0Context* ctx) override {
    //     return visit(ctx->expr1());
    // }

    // std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx) override {
    //     return visit(ctx->expr2());
    // }

private:
    void printValue(const Value& v) {
        std::visit([](auto x) { std::cout << x << "\n"; }, v);
    }
};