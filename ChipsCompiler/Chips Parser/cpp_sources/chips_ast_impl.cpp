// cpp_sources/chips_ast_impl.cpp
#include "chips_overall.hpp"
#include "chips_expressions.hpp"
#include "chips_overall_stts.hpp"
#include "chips_declaration_ctx.hpp"
#include "ChipsAST.hpp"

// === DATAFLOW ===
void dataflow_type_node::accept(chips_visitor& v) { v.visit(*this); }

// === EXPRESSIONS ===
void binary_expression_node::accept(chips_visitor& v) { v.visit(*this); }
void unary_expression_node::accept(chips_visitor& v) { v.visit(*this); }
void number_literal_node::accept(chips_visitor& v) { v.visit(*this); }
void suffixised_node::accept(chips_visitor& v) { v.visit(*this); }
void variable_node::accept(chips_visitor& v) { v.visit(*this); }
void cast_node::accept(chips_visitor& v) { v.visit(*this); }
// paren_expression_node → SKIP (déjà dans .hpp ligne 79)
void suffixes_node::accept(chips_visitor& v) { v.visit(*this); }
void expressions_node::accept(chips_visitor& v) { v.visit(*this); }

// === STATEMENTS ===
void rhs_assignment_node::accept(chips_visitor& v) { v.visit(*this); }
void dataflow_full_declaration_node::accept(chips_visitor& v) { v.visit(*this); }
void if_node::accept(chips_visitor& v) { v.visit(*this); }
void if_else_node::accept(chips_visitor& v) { v.visit(*this); }
void loop_node::accept(chips_visitor& v) { v.visit(*this); }
void statements_node::accept(chips_visitor& v) { v.visit(*this); }

// === CONTEXT ===
void preambles_node::accept(chips_visitor& v) { v.visit(*this); }
void system_node::accept(chips_visitor& v) { v.visit(*this); }
