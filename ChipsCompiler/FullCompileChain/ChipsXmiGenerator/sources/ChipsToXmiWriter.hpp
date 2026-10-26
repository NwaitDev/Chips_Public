#ifndef CHIPS_TO_XMI_WRITER_HPP
#define CHIPS_TO_XMI_WRITER_HPP

#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include "ast_node_definitions.hpp"

namespace chips {

struct chips_ast2xmi_visitor {
public:
  explicit chips_ast2xmi_visitor(std::ostream &out, std::string schema_location,
                                 std::string xmi_version = "2.0",
                                 std::string xmi_url = "http://www.omg.org/XMI");

  void write(program_node &root);

  void visit(program_node &node);
  void visit(preamble_section_node &node);
  void visit(system_section_node &node);

  void visit(object_definition &node);
  void visit(logical_definition &node);
  void visit(physical_definition &node);
  void visit(collective_function_definition &node);

  void visit(with_section &node);
  void visit(init_section &node);
  void visit(then_section &node);
  void visit(collectiveops_section &node);
  void visit(accumulator_definition &node);

  void visit(channeled_output &node);
  void visit(default_output &node);
  void visit(target_output &node);

  template <dataflow_kind dfk, dataflow_type dft>
  void visit(function_parameter<dfk, dft> &node);
  template <dataflow_type dft> void visit(collective_parameter<dft> &node);
  template <dataflow_kind dfk, dataflow_type dft>
  void visit(function_output<dfk, dft> &node);
  void visit(probe_statement &node);

  template <dataflow_type dft, statement_env stenv>
  void visit(dataflow_declaration<dft, stenv> &node);
  template <dataflow_type dft, statement_env stenv>
  void visit(dataflow_assignment<dft, stenv> &node);
  template <statement_env stenv> void visit(if_statement<stenv> &node);
  template <statement_env stenv> void visit(if_else_statement<stenv> &node);
  template <statement_env stenv> void visit(if_section<stenv> &node);
  template <statement_env stenv> void visit(else_section<stenv> &node);
  template <statement_env stenv, dataflow_type dft>
  void visit(foreach_statement<stenv, dft> &node);
  template <block_type bt> void visit(block_foreach_statement<bt> &node);
  template <block_type bt> void visit(block_declaration<bt> &node);
  template <node_element ne> void visit(node_element_declaration<ne> &node);
  template <dataflow_kind dfk, dataflow_type dft>
  void visit(feeding_statement<dfk, dft> &node);
  void visit(channel_plugging &node);
  void visit(linking_statement &node);

  template <dataflow_type dft> void visit(dataflow_primitive_variable<dft> &node);
  template <dataflow_type dft> void visit(contextual_variable<dft> &node);
  template <dataflow_type dft> void visit(dataflow_collective_variable<dft> &node);
  template <dataflow_type dft> void visit(dataflow_system_variable<dft> &node);
  template <block_type bt> void visit(block_variable<bt> &node);

  template <block_type bt> void visit(system_variable_block_expression<bt> &node);
  template <dataflow_kind dfk, dataflow_type dft> void visit(eater<dfk, dft> &node);
  template <dataflow_kind dfk, dataflow_type dft>
  void visit(feeder_block_expression<dfk, dft> &node);
  template <dataflow_kind dfk, dataflow_type dft>
  void visit(collective_cast<dfk, dft> &node);
  void visit(channel_eater &node);
  void visit(channel_feeder &node);

  template <dataflow_type dft, expression_env expenv>
  void visit(direct<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(function<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(plus<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(minus<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(mult<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(chips::div<dft, expenv> &node);
  template <expression_env expenv> void visit(mod<expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(cast_as<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(uminus_operator<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(gt<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(lt<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(geq<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(leq<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(eq<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(neq<dft, expenv> &node);
  template <expression_env expenv> void visit(or_operator<expenv> &node);
  template <expression_env expenv> void visit(and_operator<expenv> &node);
  template <expression_env expenv> void visit(not_operator<expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(variable_expression<dft, expenv> &node);
  template <dataflow_type dft, expression_env expenv>
  void visit(variable_contextual_expression<dft, expenv> &node);
  template <dataflow_type dft>
  void visit(channeled_accumulator_expression<dft> &node);
  void visit(input &node);
  void visit(stop &node);

private:
  template <typename T> static ast_node *as_node(T *ptr);

  template <typename T> void child(const std::string &role, T *node);
  template <typename... Ts>
  void child(const std::string &role, const std::variant<Ts...> &node);
  template <typename T> void member(const std::string &role, T &node);
  template <typename Seq> void children(const std::string &role, Seq &nodes);
  template <typename N>
  void binary(const std::string &ns_prefix, const std::string &eclass, N &node);
  template <typename V>
  void variable_node(const std::string &ns_prefix, const std::string &eclass,
                     V &node);

  void begin_element(const std::string &ns_prefix, const std::string &eclass,
                     ast_node *self);
  void begin_untyped_element(ast_node *self);
  void attribute(const std::string &name, const std::string &value);
  void attribute(const std::string &name, int value);
  void attribute(const std::string &name, double value);
  void attribute(const std::string &name, bool value);
  void reference(const std::string &name, ast_node *target);
  void end_element();

  std::string qualified_type(const std::string &ns_prefix,
                             const std::string &eclass);
  void register_namespace(const std::string &ns_prefix);
  static const std::map<std::string, std::string> &known_namespaces();
  static std::string schema_fragment(const std::string &ns_url);

  static std::string type_name(dataflow_type dft);
  static std::string env_name(expression_env expenv);
  static std::string env_name(statement_env stenv);
  static std::string rvalues_ns(expression_env expenv);
  static std::string operators_ns(expression_env expenv, dataflow_type dft);
  static std::string escape(const std::string &raw);
  static std::string protect_identifier(const std::string &raw);

  std::string node_id(ast_node *node);
  void indent();

  void write_header(const std::string &filename);
  void write_footer();

  std::ostream &m_out;
  std::ostringstream m_body;
  std::string m_schema_location;
  std::string m_xmi_version;
  std::string m_xmi_url;

  std::string m_role;
  std::vector<std::string> m_open_elements;
  bool m_tag_pending = false;
  int m_depth = 0;

  int m_id_counter = 0;
  std::map<const ast_node *, std::string> m_node_ids;
  std::map<std::string, std::string> m_namespaces;
};

} // namespace chips

using ChipsToXmiWriter = chips::chips_ast2xmi_visitor;

#include "ChipsToXmiWriter.tpp"

#endif