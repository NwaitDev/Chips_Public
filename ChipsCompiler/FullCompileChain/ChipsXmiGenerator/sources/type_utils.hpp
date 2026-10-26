#pragma once

#include <optional>
#include <stdexcept>
#include <string>

#include "antlr4-runtime.h"
#include "metamodel_enums.hpp"
#include "visitor_env.hpp"

using namespace chips;

template <dataflow_type dft, expression_env expenv>
constexpr dataflow_type dataflow_type_of(const rvalue<dft, expenv> *)
{
    return dft;
}

template <typename... Ts>
dataflow_type dataflow_type_of(const std::variant<Ts...> &v)
{
    return std::visit([](const auto &alt) { return dataflow_type_of(alt); }, v);
}

inline dataflow_type collective_result_type(collective_function_definition *collective)
{
    return dataflow_type_of(collective->m_target_output.get_expressions().front());
}

struct input_constraint {
  bool contains_input = false;
  std::optional<dataflow_type> forced_type = std::nullopt;
};

inline std::string type_name(dataflow_type t) {
  switch (t) {
  case dataflow_type::INT:
    return "int";
  case dataflow_type::FLOAT:
    return "float";
  case dataflow_type::BOOL:
    return "bool";
  }
  return "?";
}

inline bool is_numeric(dataflow_type t) {
  return t == dataflow_type::INT || t == dataflow_type::FLOAT;
}

[[noreturn]] inline void semantic_fail(antlr4::ParserRuleContext *ctx,
                                       const std::string &msg) {
  throw std::runtime_error(
      "error at line " + std::to_string(ctx->getStart()->getLine()) +
      ", column " +
      std::to_string(ctx->getStart()->getCharPositionInLine() + 1) + ": " +
      msg);
}

[[noreturn]] inline void type_fail(const visitor_env &venv,
                                   antlr4::ParserRuleContext *ctx,
                                   const std::string &msg) {
  throw std::runtime_error(
      "type error at line " + std::to_string(ctx->getStart()->getLine()) +
      ", column " +
      std::to_string(ctx->getStart()->getCharPositionInLine() + 1) + " in '" +
      venv.current_definition() + "': " + msg +
      " (expression: " + ctx->getText() + ")");
}

inline dataflow_type resolve_variable(const visitor_env &venv,
                                      const std::string &name,
                                      antlr4::ParserRuleContext *ctx) {
  if (name.rfind("ctx.", 0) == 0) {
    if (auto t = venv.lookup_contextual(name)) {
      return *t;
    }
  } else {
    if (auto t = venv.lookup_variable(name)) {
      return *t;
    }
    if (auto p = venv.lookup_parameter(venv.current_definition(), name)) {
      return *p;
    }
  }
  type_fail(venv, ctx, "undeclared variable '" + name + "'");
}