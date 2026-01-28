#ifndef CHIPS_TO_XMI_VISITOR_HPP
#define CHIPS_TO_XMI_VISITOR_HPP

#include "../cpp_sources/chips_ast_classes.hpp"
#include "../cpp_sources/ChipsAST.hpp"
#include "../cpp_sources/chips_overall_system.hpp"
#include "../cpp_sources/chips_overall_stts.hpp"
#include "../cpp_sources/chips_declaration_ctx.hpp"
#include "../cpp_sources/chips_expressions.hpp"
#include "../cpp_sources/chips_config_stts.hpp"
#include "ChipsToXmiWriter.hpp"
#include <ostream>

/// @brief Complete XMI Visitor - implements ALL chips_visitor methods
class ChipsToXmiVisitor : public chips_visitor
{
public:
    ChipsToXmiVisitor(ChipsToXmiWriter &writer, std::ostream &out)
        : m_writer(writer), m_out(out) {}

    // === PROGRAM & CONTEXT ===
    void visit(chips_node &chips) override;
    void visit(preambles_node &node) override;
    void visit(preamble_node &node) override;
    void visit(system_node &node) override;

    // === SYSTEM STATEMENTS ===
    void visit(s_statements_node &node) override;
    void visit(const s_statements_node &node) override;
    void visit(s_statement_node &node) override;

    // === 3. S_STATEMENT subtypes ===
    void visit(s_loop_node &node) override;
    void visit(s_if_node &node) override;
    void visit(s_if_else_node &node) override;
    void visit(functionnal_block_instanciation_node &node) override;
    void visit(implements_node &node) override;
    void visit(link_node &node) override;
    void visit(plugging_node &node) override;

    // === 4. DECLARATION CONTEXT (preamble children) ===
    void visit(object_definition_node &node) override;
    void visit(function_definition_node &node) override;
    void visit(logical_function_definition_node &node) override;
    void visit(physical_function_definition_node &node) override;
    void visit(collective_operation_definition_node &node) override;
    void visit(implementation_definition_node &node) override;
    void visit(node_mappings_node &node) override;
    void visit(c_signature_node &node) override;
    void visit(output_node &node) override;

    // === 5. WITH / SECTIONS ===
    void visit(with_section_node &node) override;
    void visit(with_statements_node &node) override;
    void visit(with_statement_node &node) override;
    void visit(with_two_identifier_node &node) override;
    void visit(with_context_statement_node &node) override;
    void visit(init_section_node &node) override;
    void visit(then_section_node &node) override;

    // === 6. EXPRESSIONS ===
    void visit(expression_node &node) override;
    void visit(suffixable_node &node) override;
    void visit(binary_expression_node &node) override;
    void visit(unary_expression_node &node) override;
    void visit(number_literal_node &node) override;
    void visit(function_call_node &node) override;
    void visit(variable_node &node) override;
    void visit(object_virtual_output_node &node) override;
    void visit(object_physical_attribute_node &node) override;
    void visit(cast_node &node) override;
    void visit(suffixes_node &node) override;
    void visit(suffixised_node &node) override;
    void visit(paren_expression_node &node) override;

    // === 7. FALLBACK (tous les autres) ===
    void visit(ast_node &node) override;

private:
    // Helpers
    std::ostream &out() { return m_out; }
    void writeAttribute(const std::string &name, const std::string &value);
    void endEmptyElement();
    void visit_generic(ast_node &node); // squelette commun

    // Members
    ChipsToXmiWriter &m_writer;
    std::ostream &m_out;
};

#endif // CHIPS_TO_XMI_VISITOR_HPP
