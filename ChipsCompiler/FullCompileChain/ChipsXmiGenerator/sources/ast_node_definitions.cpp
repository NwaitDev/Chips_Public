#include "ast_node_definitions.hpp"

#include <stdexcept>

#include "ChipsToXmiWriter.hpp"

namespace chips {

void with_section::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void init_section::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void then_section::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void collectiveops_section::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void accumulator_definition::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}
void probe_statement::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void object_definition::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void logical_definition::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void physical_definition::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void collective_function_definition::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void channeled_output::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void default_output::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void target_output::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void system_variable_block_expression<block_type::LOGICAL>::accept(
    chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void system_variable_block_expression<block_type::PHYSICAL>::accept(
    chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void system_variable_block_expression<block_type::OBJECT>::accept(
    chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void channel_eater::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void channel_feeder::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void input::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void stop::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void preamble_section_node::accept(chips_ast2xmi_visitor &v) {
  v.visit(*this);
}

void system_section_node::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void program_node::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void channel_plugging::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void linking_statement::accept(chips_ast2xmi_visitor &v) { v.visit(*this); }

void node_variable::accept(chips_ast2xmi_visitor &) {
  throw std::runtime_error(
      "abstract node_variable reached, a contextual_variable is expected");
}

void collective_variable::accept(chips_ast2xmi_visitor &) {
  throw std::runtime_error("abstract collective_variable reached, a "
                           "dataflow_collective_variable is expected");
}

void system_variable::accept(chips_ast2xmi_visitor &) {
  throw std::runtime_error("abstract system_variable reached, a block_variable "
                           "or dataflow_system_variable is expected");
}

} // namespace chips
