#ifndef __chips_ast_node_definitions_tpp__
#define __chips_ast_node_definitions_tpp__

#include <stdexcept>

#include "ast_node_definitions.hpp"
#include "ChipsToXmiWriter.hpp"

namespace chips {

template <dataflow_kind dfk, dataflow_type dft>
void function_parameter<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft>
void collective_parameter<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_kind dfk, dataflow_type dft>
void function_output<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_kind dfk, dataflow_type dft>
void eater<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_kind dfk, dataflow_type dft>
void feeder_block_expression<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_kind dfk, dataflow_type dft>
void collective_cast<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void direct<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void function<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void plus<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void minus<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void mult<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void div<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <expression_env expenv>
void mod<expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void cast_as<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void gt<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void lt<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void geq<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void leq<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <expression_env expenv>
void or_operator<expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <expression_env expenv>
void and_operator<expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <expression_env expenv>
void not_operator<expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void uminus_operator<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void eq<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void neq<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void variable_expression<dft, expenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, expression_env expenv>
void variable_contextual_expression<dft, expenv>::accept(
    chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, statement_env stenv>
void dataflow_declaration<dft, stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft, statement_env stenv>
void dataflow_assignment<dft, stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <statement_env stenv>
void if_section<stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <statement_env stenv>
void else_section<stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <statement_env stenv>
void if_statement<stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <statement_env stenv>
void if_else_statement<stenv>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <statement_env stenv, dataflow_type dft>
void foreach_statement<stenv, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <block_type bt>
void block_foreach_statement<bt>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <block_type bt>
void block_declaration<bt>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_kind dfk, dataflow_type dft>
void feeding_statement<dfk, dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <node_element ne>
void node_element_declaration<ne>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <expression_env expenv>
void array<expenv>::accept(chips_ast2xmi_visitor &) {
  throw std::runtime_error(
      "array has no XMI representation of its own, visit its variable");
}

template <expression_env expenv>
void variable<expenv>::accept(chips_ast2xmi_visitor &) {
  throw std::runtime_error(
      "abstract variable reached, a concrete variable class is expected");
}

template <dataflow_type dft>
void dataflow_primitive_variable<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft>
void contextual_variable<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft>
void dataflow_collective_variable<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft>
void channeled_accumulator_expression<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <block_type bt>
void block_variable<bt>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

template <dataflow_type dft>
void dataflow_system_variable<dft>::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

} // namespace chips

#endif
