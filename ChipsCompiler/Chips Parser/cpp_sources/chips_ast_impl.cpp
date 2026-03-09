// cpp_sources/chips_ast_impl.cpp
#include "chips_overall.hpp"
#include "chips_expressions.hpp"
#include "chips_overall_stts.hpp"
#include "chips_declaration_ctx.hpp"
#include "ChipsAST.hpp"

#include "parserXmetamodel/ast_classes_headers/forward_declarations.hpp"
#include "parserXmetamodel/chips_overall_definition.hpp"

namespace chips {
    // void program_node::accept(visitor& v) { v.visit(*this); }
    // void preamble_section_node::accept(visitor& v) { v.visit(*this); }
    // void system_section_node::accept(visitor& v) { v.visit(*this); }

    // void logical_definition::accept(visitor& v) { v.visit(*this); }

    // void init_section::accept(visitor& v) { v.visit(*this); }
    // void then_section::accept(visitor& v) { v.visit(*this); }
}

//TODO: deleting this below after because linkage error

// === DATAFLOW ===
void dataflow_type_node::accept(chips_visitor& v) { v.visit(*this); }

// === EXPRESSIONS ===
void binary_expression_node::accept(chips_visitor& v) { v.visit(*this); }
void unary_expression_node::accept(chips_visitor& v) { v.visit(*this); }
void number_literal_node::accept(chips_visitor& v) { v.visit(*this); }
void suffixised_node::accept(chips_visitor& v) { v.visit(*this); }
void variable_node::accept(chips_visitor& v) { v.visit(*this); }
void cast_node::accept(chips_visitor& v) { v.visit(*this); }
void function_call_node::accept(chips_visitor& v) { v.visit(*this); }
// paren_expression_node → SKIP (déjà dans .hpp ligne 79)
void suffixes_node::accept(chips_visitor& v) { v.visit(*this); }
void expressions_node::accept(chips_visitor& v) { v.visit(*this); }

// === STATEMENTS ===
void statement_node::accept(chips_visitor& v) { v.visit(*this); }
void rhs_assignment_node::accept(chips_visitor& v) { v.visit(*this); }
void dataflow_full_declaration_node::accept(chips_visitor& v) { v.visit(*this); }
void if_node::accept(chips_visitor& v) { v.visit(*this); }
void if_else_node::accept(chips_visitor& v) { v.visit(*this); }
void loop_node::accept(chips_visitor& v) { v.visit(*this); }
void statements_node::accept(chips_visitor& v) { v.visit(*this); }

// === CONTEXT ===
void preambles_node::accept(chips_visitor& v) { v.visit(*this); }
void system_node::accept(chips_visitor& v) { v.visit(*this); }
