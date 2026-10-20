#include "ChipsToXmiWriter.hpp"

#include <iomanip>
#include <limits>
#include <locale>
#include <stdexcept>
#include <utility>

namespace chips {

chips_ast2xmi_visitor::chips_ast2xmi_visitor(
    std::ostream &out,
    std::string schema_location,
    std::string xmi_version,
    std::string xmi_url): 
    m_out(out), m_schema_location(std::move(schema_location)),
    m_xmi_version(std::move(xmi_version)), m_xmi_url(std::move(xmi_url)) {}

void chips_ast2xmi_visitor::write(program_node &root) {
  m_body.str("");
  m_body.clear();
  m_role.clear();
  m_open_elements.clear();
  m_tag_pending = false;
  m_depth = 1;
  m_id_counter = 0;
  m_node_ids.clear();
  m_namespaces.clear();

  visit(root);

  write_header(root.m_filename);
  m_out << m_body.str();
  write_footer();
}

void chips_ast2xmi_visitor::visit(program_node &node) {
  member("preamble", node.m_preamble);
  member("system", node.m_system);
}

void chips_ast2xmi_visitor::visit(preamble_section_node &node) {
  begin_untyped_element(&node);
  children("definitions", node.get_definitions());
  end_element();
}

void chips_ast2xmi_visitor::visit(system_section_node &node) {
  begin_untyped_element(&node);
  children("system_statements", node.get_statements());
  end_element();
}

void chips_ast2xmi_visitor::visit(object_definition &node) {
  begin_element("definitions", "object_definition", &node);
  attribute("name", node.m_name);
  member("with", node.m_with);
  end_element();
}

void chips_ast2xmi_visitor::visit(logical_definition &node) {
  begin_element("definitions", "logical_definition", &node);
  attribute("name", node.m_name);
  children("outputs", node.get_outputs());
  children("parameters", node.get_parameters());
  member("init", node.get_init_section());
  member("then", node.get_then_section());
  end_element();
}

void chips_ast2xmi_visitor::visit(physical_definition &node) {
  begin_element("definitions", "physical_definition", &node);
  attribute("name", node.m_name);
  member("with", node.m_with);
  children("outputs", node.get_outputs());
  children("parameters", node.get_parameters());
  member("init", node.get_init_section());
  member("then", node.get_then_section());
  children("sensor", node.m_sensors);
  children("actuator", node.m_actuators);
  end_element();
}

void chips_ast2xmi_visitor::visit(collective_function_definition &node) {
  begin_element("definitions", "collective_function_definition", &node);
  attribute("name", node.m_name);
  attribute("collective_function_type",
            std::string(node.m_collective_function_type ==
                                collective_function_type::SPREAD
                            ? "spread"
                            : "collect"));
  reference("support_object", as_node(node.m_support_object));
  member("accumulator", node.m_accumulator);
  member("operations", node.m_operations);
  member("target_output", node.m_target_output);
  children("channeled_output", node.get_channeled_outputs());
  if (auto &defaulted = node.get_default_output(); defaulted.has_value()) {
    member("default_output", *defaulted);
  }
  end_element();
}

void chips_ast2xmi_visitor::visit(with_section &node) {
  begin_untyped_element(&node);
  children("statements", node.get_statements());
  end_element();
}

void chips_ast2xmi_visitor::visit(init_section &node) {
  begin_untyped_element(&node);
  children("statements", node.get_statements());
  end_element();
}

void chips_ast2xmi_visitor::visit(then_section &node) {
  begin_untyped_element(&node);
  children("statements", node.get_statements());
  end_element();
}

void chips_ast2xmi_visitor::visit(collectiveops_section &node) {
  begin_untyped_element(&node);
  children("statements", node.get_statements());
  end_element();
}

void chips_ast2xmi_visitor::visit(accumulator_definition &node) {
  begin_untyped_element(&node);
  children("accumulator", node.get_accumulators());
  end_element();
}

void chips_ast2xmi_visitor::visit(channeled_output &node) {
  begin_element("chips.outputs.collective", "channeled_output", &node);
  reference("channel", as_node(node.get_channel()));
  auto exprs = node.get_expressions();
  children("accumulator_expressions", exprs);
  end_element();
}

void chips_ast2xmi_visitor::visit(default_output &node) {
  begin_element("chips.outputs.collective", "default_output", &node);
  auto exprs = node.get_expressions();
  children("accumulator_expressions", exprs);
  end_element();
}

void chips_ast2xmi_visitor::visit(target_output &node) {
  begin_element("chips.outputs.collective", "target_output", &node);
  children("expression", node.get_expressions());
  end_element();
}

void chips_ast2xmi_visitor::visit(channel_plugging &node) {
  begin_element("chips.statements.system", "channel_plugging", &node);
  child("eater", node.get_eater());
  child("feeder", node.get_feeder());
  end_element();
}

void chips_ast2xmi_visitor::visit(linking_statement &node) {
  begin_element("chips.statements.system", "link", &node);
  child("linked_component", node.get_linkable());
  child("support_node", node.get_support());
  end_element();
}

void chips_ast2xmi_visitor::visit(channel_eater &node) {
  begin_element("chips.systemspecific.expressions.eater", "channel_eater",
                &node);
  reference("eating_channel", as_node(node.get_eating_channel()));
  child("node", node.get_node());
  end_element();
}

void chips_ast2xmi_visitor::visit(channel_feeder &node) {
  begin_element("chips.systemspecific.expressions.feeder", "channel_feeder",
                &node);
  reference("feeding_channel", as_node(node.get_feeding_channel()));
  child("node", node.get_node());
  end_element();
}

void chips_ast2xmi_visitor::visit(input &node) {
  begin_element("chips.rvalues.collective", "input_kw", &node);
  end_element();
}

void chips_ast2xmi_visitor::visit(stop &node) {
  begin_element("chips.rvalues.collective", "stop_kw", &node);
  end_element();
}

void chips_ast2xmi_visitor::begin_element(const std::string &ns_prefix,
                                          const std::string &eclass,
                                          ast_node *self) {
  begin_untyped_element(self);
  attribute("xsi:type", qualified_type(ns_prefix, eclass));
}

void chips_ast2xmi_visitor::begin_untyped_element(ast_node *self) {
  if (m_role.empty()) {
    throw std::logic_error("element written without a containing feature");
  }
  if (m_tag_pending) {
    m_body << ">\n";
  }
  indent();
  m_body << "<" << m_role;
  m_open_elements.push_back(m_role);
  m_role.clear();
  m_tag_pending = true;
  ++m_depth;
  if (self) {
    m_body << " xmi:id=\"" << node_id(self) << "\"";
  }
}

void chips_ast2xmi_visitor::attribute(const std::string &name,
                                      const std::string &value) {
  if (!m_tag_pending) {
    throw std::logic_error("attribute '" + name +
                           "' written after element content");
  }
  m_body << " " << name << "=\"" << escape(value) << "\"";
}

void chips_ast2xmi_visitor::attribute(const std::string &name, int value) {
  attribute(name, std::to_string(value));
}

void chips_ast2xmi_visitor::attribute(const std::string &name, double value) {
  std::ostringstream os;
  os.imbue(std::locale::classic());
  os << std::setprecision(std::numeric_limits<double>::max_digits10) << value;
  attribute(name, os.str());
}

void chips_ast2xmi_visitor::attribute(const std::string &name, bool value) {
  attribute(name, std::string(value ? "true" : "false"));
}

void chips_ast2xmi_visitor::reference(const std::string &name,
                                      ast_node *target) {
  if (!target) {
    return;
  }
  attribute(name, node_id(target));
}

void chips_ast2xmi_visitor::end_element() {
  if (m_open_elements.empty()) {
    throw std::logic_error("end_element without matching begin_element");
  }
  --m_depth;
  std::string role = m_open_elements.back();
  m_open_elements.pop_back();
  if (m_tag_pending) {
    m_body << "/>\n";
    m_tag_pending = false;
  } else {
    indent();
    m_body << "</" << role << ">\n";
  }
}

std::string chips_ast2xmi_visitor::qualified_type(const std::string &ns_prefix,
                                                  const std::string &eclass) {
  register_namespace(ns_prefix);
  return ns_prefix + ":" + eclass;
}

void chips_ast2xmi_visitor::register_namespace(const std::string &ns_prefix) {
  const auto &known = known_namespaces();
  auto it = known.find(ns_prefix);
  if (it == known.end()) {
    throw std::logic_error("unknown metamodel namespace prefix '" + ns_prefix +
                           "'");
  }
  m_namespaces.emplace(it->first, it->second);
}

const std::map<std::string, std::string> &
chips_ast2xmi_visitor::known_namespaces() {
  static const std::map<std::string, std::string> namespaces = {
      {"chips.variables", "http://chips/variables"},
      {"chips.variables.primitive", "http://chips/variables/primitive"},
      {"chips.variables.node", "http://chips/variables/node"},
      {"chips.variables.collective", "http://chips/variables/collective"},
      {"chips.variables.system", "http://chips/variables/system"},
      {"chips.statements", "http://chips/statements"},
      {"chips.statements.primitive", "http://chips/statements/primitive"},
      {"chips.statements.collective", "http://chips/statements/collective"},
      {"chips.statements.system", "http://chips/statements/system"},
      {"chips.statements.implementation",
       "http://chips/statements/implementation"},
      {"chips.statements.node", "http://chips/statements/node"},
      {"chips.parameters", "http://chips/parameters"},
      {"chips.parameters.logical", "http://chips/parameters/logical"},
      {"chips.parameters.physical", "http://chips/parameters/physical"},
      {"chips.parameters.collective", "http://chips/parameters/collective"},
      {"chips.outputs", "http://chips/outputs"},
      {"chips.outputs.logical", "http://chips/outputs/logical"},
      {"chips.outputs.physical", "http://chips/outputs/physical"},
      {"chips.outputs.collective", "http://chips/outputs/collective"},
      {"definitions", "http://chips/definitions"},
      {"chips.lvalues", "http://chips/lvalues"},
      {"chips.xvalues", "http://chips/xvalues"},
      {"chips.xvalues.primitive", "http://chips/xvalues/primitive"},
      {"chips.xvalues.collective", "http://chips/xvalues/collective"},
      {"chips.xvalues.system", "http://chips/xvalues/system"},
      {"chips.rvalues", "http://chips/rvalues"},
      {"chips.rvalues.primitive", "http://chips/rvalues/primitive"},
      {"chips.rvalues.primitive.operators",
       "http://chips/rvalues/primitive/operators"},
      {"chips.rvalues.primitive.operators.int",
       "http://chips/rvalues/primitive/operators/int"},
      {"chips.rvalues.primitive.operators.float",
       "http://chips/rvalues/primitive/operators/float"},
      {"chips.rvalues.primitive.operators.bool",
       "http://chips/rvalues/primitive/operators/bool"},
      {"chips.rvalues.system", "http://chips/rvalues/system"},
      {"chips.rvalues.dataflow.operators",
       "http://chips/rvalues/dataflow/operators"},
      {"chips.rvalues.dataflow.operators.int",
       "http://chips/rvalues/dataflow/operators/int"},
      {"chips.rvalues.dataflow.operators.float",
       "http://chips/rvalues/dataflow/operators/float"},
      {"chips.rvalues.dataflow.operators.bool",
       "http://chips/rvalues/dataflow/operators/bool"},
      {"chips.rvalues.collective", "http://chips/rvalues/collective"},
      {"chips.rvalues.collective.operators",
       "http://chips/rvalues/collective/operators"},
      {"chips.rvalues.collective.operators.int",
       "http://chips/rvalues/collective/operators/int"},
      {"chips.rvalues.collective.operators.float",
       "http://chips/rvalues/collective/operators/float"},
      {"chips.rvalues.collective.operators.bool",
       "http://chips/rvalues/collective/operators/bool"},
      {"chips.systemspecific", "http://chips/systemspecific"},
      {"chips.systemspecific.expressions",
       "http://chips/systemspecific/expressions"},
      {"chips.systemspecific.expressions.eater",
       "http://chips/systemspecific/expressions/eater"},
      {"chips.systemspecific.expressions.feeder",
       "http://chips/systemspecific/expressions/feeder"},
  };
  return namespaces;
}

std::string chips_ast2xmi_visitor::schema_fragment(const std::string &ns_url) {
  static const std::string root = "http://chips";
  static const std::string dataflow = "/rvalues/dataflow/";
  static const std::string system = "/rvalues/system/";
  std::string path = ns_url.substr(root.size());
  if (path.compare(0, dataflow.size(), dataflow) == 0) {
    path = system + path.substr(dataflow.size());
  }
  return "#/" + path;
}

std::string chips_ast2xmi_visitor::type_name(dataflow_type dft) {
  switch (dft) {
  case dataflow_type::INT:
    return "int";
  case dataflow_type::FLOAT:
    return "float";
  case dataflow_type::BOOL:
    return "bool";
  }
  throw std::logic_error("unknown dataflow type");
}

std::string chips_ast2xmi_visitor::env_name(expression_env expenv) {
  switch (expenv) {
  case expression_env::PRIMITIVE:
    return "primitive";
  case expression_env::COLLECTIVE:
    return "collective";
  case expression_env::SYSTEM:
    return "system";
  }
  throw std::logic_error("unknown expression environment");
}

std::string chips_ast2xmi_visitor::env_name(statement_env stenv) {
  switch (stenv) {
  case statement_env::DEFINITION:
  case statement_env::NODE:
    return "primitive";
  case statement_env::COLLECTIVE:
    return "collective";
  case statement_env::SYSTEM:
    return "system";
  }
  throw std::logic_error("unknown statement environment");
}

std::string chips_ast2xmi_visitor::rvalues_ns(expression_env expenv) {
  return "chips.rvalues." + env_name(expenv);
}

std::string chips_ast2xmi_visitor::operators_ns(expression_env expenv,
                                                dataflow_type dft) {
  if (expenv == expression_env::SYSTEM) {
    return "chips.rvalues.dataflow.operators." + type_name(dft);
  }
  return "chips.rvalues." + env_name(expenv) + ".operators." + type_name(dft);
}

std::string chips_ast2xmi_visitor::escape(const std::string &raw) {
  std::string out;
  out.reserve(raw.size());
  for (char c : raw) {
    switch (c) {
    case '&':
      out += "&amp;";
      break;
    case '<':
      out += "&lt;";
      break;
    case '>':
      out += "&gt;";
      break;
    case '"':
      out += "&quot;";
      break;
    case '\'':
      out += "&apos;";
      break;
    case '\n':
      out += "&#10;";
      break;
    case '\t':
      out += "&#9;";
      break;
    default:
      out += c;
    }
  }
  return out;
}

std::string chips_ast2xmi_visitor::node_id(ast_node *node) {
  auto it = m_node_ids.find(node);
  if (it != m_node_ids.end()) {
    return it->second;
  }
  std::string id = "_" + std::to_string(++m_id_counter);
  m_node_ids.emplace(node, id);
  return id;
}

void chips_ast2xmi_visitor::indent() {
  m_body << std::string(static_cast<std::size_t>(m_depth) * 2, ' ');
}

void chips_ast2xmi_visitor::write_header(const std::string &filename) {
  m_out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  m_out << "<chips:program xmi:version=\"" << escape(m_xmi_version) << "\"\n";
  m_out << "    xmlns:xmi=\"" << escape(m_xmi_url) << "\"\n";
  m_out << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
  m_out << "    xmlns:chips=\"http://chips\"\n";
  for (const auto &[prefix, url] : m_namespaces) {
    m_out << "    xmlns:" << prefix << "=\"" << url << "\"\n";
  }
  m_out << "    xsi:schemaLocation=\"http://chips " << escape(m_schema_location);
  for (const auto &[prefix, url] : m_namespaces) {
    m_out << " " << url << " " << escape(m_schema_location)
          << schema_fragment(url);
  }
  m_out << "\"\n";
  m_out << "    fileName=\"" << escape(filename) << "\">\n";
}

void chips_ast2xmi_visitor::write_footer() { m_out << "</chips:program>\n"; }

} // namespace chips