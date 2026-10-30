#ifndef CHIPS_TO_XMI_WRITER_TPP
#define CHIPS_TO_XMI_WRITER_TPP

#include <stdexcept>
#include <type_traits>

namespace chips {

namespace xmi_detail {

template <typename> inline constexpr bool dependent_false = false;

template <typename T> struct is_variant : std::false_type {};
template <typename... Ts>
struct is_variant<std::variant<Ts...>> : std::true_type {};

inline std::string kind_name(dataflow_kind dfk) {
  return dfk == dataflow_kind::LOGICAL ? "logical" : "physical";
}

inline std::string block_name(block_type bt) {
  switch (bt) {
  case block_type::LOGICAL:
    return "logical";
  case block_type::PHYSICAL:
    return "physical";
  case block_type::OBJECT:
    return "object";
  }
  return "";
}

inline std::string contextual_declaration_name(node_element ne) {
  switch (ne) {
  case node_element::CONTEXTUAL_INT:
    return "contextual_int_declaration";
  case node_element::CONTEXTUAL_FLOAT:
    return "contextual_float_declaration";
  case node_element::CONTEXTUAL_BOOL:
    return "contextual_bool_declaration";
  default:
    return "";
  }
}

} // namespace xmi_detail

template <typename T> ast_node *chips_ast2xmi_visitor::as_node(T *ptr) {
  using U = std::remove_cv_t<T>;
  U *p = const_cast<U *>(ptr);
  if (!p) {
    return nullptr;
  }
  if constexpr (std::is_base_of_v<ast_node, U>) {
    return static_cast<ast_node *>(p);
  } else if constexpr (std::is_polymorphic_v<U>) {
    return dynamic_cast<ast_node *>(p);
  } else {
    static_assert(xmi_detail::dependent_false<T>,
                  "AST pointer type must derive from ast_node or be polymorphic");
    return nullptr;
  }
}

template <typename T>
void chips_ast2xmi_visitor::child(const std::string &role, T *node) {
  if (!node) {
    return;
  }
  ast_node *n = as_node(node);
  if (!n) {
    throw std::runtime_error("cannot resolve AST node for feature '" + role +
                             "'");
  }
  m_role = role;
  n->accept(*this);
}

template <typename... Ts>
void chips_ast2xmi_visitor::child(const std::string &role,
                                  const std::variant<Ts...> &node) {
  std::visit([this, &role](const auto &alt) { this->child(role, alt); }, node);
}

template <typename T>
void chips_ast2xmi_visitor::member(const std::string &role, T &node) {
  m_role = role;
  visit(node);
}

template <typename Seq>
void chips_ast2xmi_visitor::children(const std::string &role, Seq &nodes) {
  for (auto &n : nodes) {
    using E = std::decay_t<decltype(n)>;
    if constexpr (std::is_pointer_v<E> || xmi_detail::is_variant<E>::value) {
      child(role, n);
    } else {
      member(role, n);
    }
  }
}

template <typename N>
void chips_ast2xmi_visitor::binary(const std::string &ns_prefix,
                                   const std::string &eclass, N &node) {
  begin_element(ns_prefix, eclass, &node);
  child("left_operand", node.get_lhs());
  child("right_operand", node.get_rhs());
  end_element();
}

template <typename V>
void chips_ast2xmi_visitor::variable_node(const std::string &ns_prefix,
                                          const std::string &eclass, V &node) {
  begin_element(ns_prefix, eclass, &node);
  attribute("name", node.m_name);
  children("dimensions", node.m_dimensions);
  end_element();
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(function_parameter<dfk, dft> &node) {
  const std::string kind = xmi_detail::kind_name(dfk);
  begin_element("chips.parameters." + kind,
                type_name(dft) + "_" + kind + "_parameter", &node);
  attribute("name", node.get_name());
  child("declaration", node.get_declaration());
  child("default_value", node.get_default_value());
  end_element();
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(collective_parameter<dft> &node) {
  begin_element("chips.parameters.collective",
                type_name(dft) + "_collective_parameter", &node);
  child("declaration", node.get_declaration());
  child("default_value", node.get_default_value());
  end_element();
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(function_output<dfk, dft> &node) {
  auto &exprs = node.get_expressions();
  if (exprs.size() > 1) {
    throw std::runtime_error("output '" + node.get_name() +
                             "' has several expressions, Chips 1.1 allows one");
  }
  begin_element("chips.outputs." + xmi_detail::kind_name(dfk),
                type_name(dft) + "_output", &node);
  attribute("name", node.get_name());
  if (!exprs.empty()) {
    child("expression", exprs.front());
  }
  end_element();
}

template <dataflow_type dft, statement_env stenv>
void chips_ast2xmi_visitor::visit(dataflow_declaration<dft, stenv> &node) {
  begin_element("chips.statements." + env_name(stenv),
                type_name(dft) + "_declaration", &node);
  member("variable", node.m_variable);
  end_element();
}

template <dataflow_type dft, statement_env stenv>
void chips_ast2xmi_visitor::visit(dataflow_assignment<dft, stenv> &node) {
  begin_element("chips.statements." + env_name(stenv),
                type_name(dft) + "_assignment", &node);
  child("lvalue", node.get_lhs());
  child("rvalue", node.get_rhs());
  end_element();
}

template <statement_env stenv>
void chips_ast2xmi_visitor::visit(if_statement<stenv> &node) {
  begin_element("chips.statements." + env_name(stenv), "if", &node);
  child("condition", node.get_condition());
  member("if_section", node.get_if_section());
  end_element();
}

template <statement_env stenv>
void chips_ast2xmi_visitor::visit(if_else_statement<stenv> &node) {
  begin_element("chips.statements." + env_name(stenv), "if_else", &node);
  child("condition", node.get_condition());
  member("if_section", node.get_if_section());
  member("else_section", node.get_else_section());
  end_element();
}

template <statement_env stenv>
void chips_ast2xmi_visitor::visit(if_section<stenv> &node) {
  begin_untyped_element(&node);
  children("if_statements", node.get_statements());
  end_element();
}

template <statement_env stenv>
void chips_ast2xmi_visitor::visit(else_section<stenv> &node) {
  begin_untyped_element(&node);
  children("else_statements", node.get_statements());
  end_element();
}

template <statement_env stenv, dataflow_type dft>
void chips_ast2xmi_visitor::visit(foreach_statement<stenv, dft> &node) {
  begin_element("chips.statements." + env_name(stenv), "foreach", &node);
  child("iterator", node.get_iterator());
  child("iterable_expr", node.get_iterable());
  children("statements", node.get_statements());
  end_element();
}

template <block_type bt>
void chips_ast2xmi_visitor::visit(block_foreach_statement<bt> &node) {
  begin_element("chips.statements.system", "foreach", &node);
  child("iterator", node.get_iterator());
  child("iterable_expr", node.get_iterable());
  children("statements", node.get_statements());
  end_element();
}

template <block_type bt>
void chips_ast2xmi_visitor::visit(block_declaration<bt> &node) {
  begin_element("chips.statements.system",
                xmi_detail::block_name(bt) + "_declaration", &node);
  reference("def", as_node(node.get_definition()));
  member("variable", node.m_variable);
  end_element();
}

template <node_element ne>
void chips_ast2xmi_visitor::visit(node_element_declaration<ne> &node) {
  if constexpr (ne == node_element::CHANNEL) {
    begin_element("chips.statements.node", "channel_declaration", &node);
    attribute("name", node.get_name());
    attribute("type_identifier", node.get_variable());
    end_element();
  } else {
    begin_element("chips.statements.node",
                  xmi_detail::contextual_declaration_name(ne), &node);
    attribute("identifier", node.get_name());
    member("variable", node.m_variable_type);
    end_element();
  }
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(feeding_statement<dfk, dft> &node) {
  begin_element("chips.statements.system",
                "feeding_" + xmi_detail::kind_name(dfk) + "_" + type_name(dft),
                &node);
  member("eater", node.get_eater());
  child("feeder", node.get_feeder());
  end_element();
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(dataflow_primitive_variable<dft> &node) {
  variable_node("chips.variables.primitive", type_name(dft), node);
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(contextual_variable<dft> &node) {
  variable_node("chips.variables.node", type_name(dft), node);
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(dataflow_collective_variable<dft> &node) {
  variable_node("chips.variables.collective", type_name(dft), node);
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(dataflow_system_variable<dft> &node) {
  variable_node("chips.variables.system", type_name(dft), node);
}

template <block_type bt>
void chips_ast2xmi_visitor::visit(block_variable<bt> &node) {
  variable_node("chips.variables.system", xmi_detail::block_name(bt), node);
}

template <block_type bt>
void chips_ast2xmi_visitor::visit(system_variable_block_expression<bt> &node) {
  begin_element("chips.systemspecific.expressions",
                xmi_detail::block_name(bt) + "_variable_expression", &node);
  reference("variable", as_node(node.get_variable()));
  children("index", node.get_index());
  end_element();
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(eater<dfk, dft> &node) {
  begin_element("chips.systemspecific.expressions.eater",
                xmi_detail::kind_name(dfk) + "_" + type_name(dft) + "_eater",
                &node);
  reference("parameter", as_node(node.get_parameter()));
  if constexpr (dfk == dataflow_kind::LOGICAL) {
    std::visit(
        [this](auto *block) {
          m_role = "variable_expression";
          begin_element("chips.systemspecific.expressions",
                        "logical_variable_expression", block);
          reference("variable", as_node(block->get_variable()));
          children("index", block->get_index());
          end_element();
        },
        node.get_functional_block());
  } else {
    child("variable_expression", node.get_functional_block());
  }
  end_element();
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(feeder_block_expression<dfk, dft> &node) {
  begin_element("chips.systemspecific.expressions.feeder",
                type_name(dft) + "_" + xmi_detail::kind_name(dfk) + "_output",
                &node);
  reference("output", as_node(node.get_output()));
  if constexpr (dfk == dataflow_kind::LOGICAL) {
    std::visit(
        [this](auto *block) {
          m_role = "variable_expression";
          begin_element("chips.systemspecific.expressions",
                        "logical_variable_expression", block);
          reference("variable", as_node(block->get_variable()));
          children("index", block->get_index());
          end_element();
        },
        node.get_functional_block());
  } else {
    child("variable_expression", node.get_functional_block());
  }
  end_element();
}

template <dataflow_kind dfk, dataflow_type dft>
void chips_ast2xmi_visitor::visit(collective_cast<dfk, dft> &node) {
  const std::string kind = xmi_detail::kind_name(dfk);
  begin_element("chips.systemspecific.expressions.feeder",
                kind + "_collective_cast", &node);
  reference("collective_function", as_node(node.get_collective_function()));
  child(kind + "_feeder_expression", node.get_feeder_variant());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(direct<dft, expenv> &node) {
  begin_element(rvalues_ns(expenv), "direct_" + type_name(dft), &node);
  attribute("value", node.get_value());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(function<dft, expenv> &node) {
  begin_element(rvalues_ns(expenv), "function", &node);
  attribute("name", node.get_name());
  children("parameters", node.get_parameters());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(plus<dft, expenv> &node) {
  binary(operators_ns(expenv, dft), "plus", node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(minus<dft, expenv> &node) {
  binary(operators_ns(expenv, dft), "minus", node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(mult<dft, expenv> &node) {
  binary(operators_ns(expenv, dft), "mult", node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(chips::div<dft, expenv> &node) {
  binary(operators_ns(expenv, dft), "div", node);
}

template <expression_env expenv>
void chips_ast2xmi_visitor::visit(mod<expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::INT), "mod", node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(cast_as<dft, expenv> &node) {
  begin_element(operators_ns(expenv, dft), "cast_as_" + type_name(dft), &node);
  child("numeric", node.get_cast());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(uminus_operator<dft, expenv> &node) {
  using value_type = typename DfTypeToCppType<dft>::type;
  begin_element(operators_ns(expenv, dft), "minus", &node);
  m_role = "left_operand";
  begin_element(rvalues_ns(expenv), "direct_" + type_name(dft), nullptr);
  attribute("value", value_type{});
  end_element();
  child("right_operand", node.get_rhs());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(gt<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "gt_" + type_name(dft),
         node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(lt<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "lt_" + type_name(dft),
         node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(geq<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "geq_" + type_name(dft),
         node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(leq<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "leq_" + type_name(dft),
         node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(eq<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "eq_" + type_name(dft),
         node);
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(neq<dft, expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "neq_" + type_name(dft),
         node);
}

template <expression_env expenv>
void chips_ast2xmi_visitor::visit(or_operator<expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "or", node);
}

template <expression_env expenv>
void chips_ast2xmi_visitor::visit(and_operator<expenv> &node) {
  binary(operators_ns(expenv, dataflow_type::BOOL), "and", node);
}

template <expression_env expenv>
void chips_ast2xmi_visitor::visit(not_operator<expenv> &node) {
  begin_element(operators_ns(expenv, dataflow_type::BOOL), "not", &node);
  child("operand", node.get_operand());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(variable_expression<dft, expenv> &node) {
  begin_element("chips.xvalues." + env_name(expenv),
                type_name(dft) + "_variable_expression", &node);
  reference("variable", as_node(node.get_variable()));
  children("index", node.get_index());
  end_element();
}

template <dataflow_type dft, expression_env expenv>
void chips_ast2xmi_visitor::visit(
    variable_contextual_expression<dft, expenv> &node) {
  begin_element("chips.xvalues." + env_name(expenv),
                "contextual_" + type_name(dft) + "_expression", &node);
  reference("variable", as_node(node.get_variable()));
  children("index", node.get_index());
  end_element();
}

template <dataflow_type dft>
void chips_ast2xmi_visitor::visit(channeled_accumulator_expression<dft> &node) {
  begin_element("chips.rvalues.collective",
                type_name(dft) + "_channeled_expression", &node);
  reference("channel", as_node(node.get_channel()));
  reference("accu_parameter", as_node(node.get_accumulator()));
  end_element();
}

} // namespace chips

#endif
