#ifndef CHIPS_TO_XMI_VISITOR_HPP
#define CHIPS_TO_XMI_VISITOR_HPP

/** problem override ? create methode in chips_ast_classes.hpp */

#include "../cpp_sources/chips_ast_classes.hpp"
#include "../cpp_sources/ChipsAST.hpp"
#include "../cpp_sources/chips_overall_system.hpp"
#include "../cpp_sources/chips_overall_stts.hpp"
#include "../cpp_sources/chips_declaration_ctx.hpp"
#include "../cpp_sources/chips_expressions.hpp"
#include "../cpp_sources/chips_config_stts.hpp"
#include "../cpp_sources/chips_semantic_analyzer.hpp"

#include "../cpp_sources/parserXmetamodel/ast_classes_headers/forward_declarations.hpp"
#include "../cpp_sources/parserXmetamodel/chips_overall_definition.hpp"

#include "ChipsToXmiWriter.hpp"
#include <ostream>
#include <map>
#include <vector>
#include <string>

/// @brief Complete XMI Visitor - implements ALL chips_visitor methods
class ChipsToXmiVisitor : public chips::visitor
{
public:
    ChipsToXmiVisitor(ChipsToXmiWriter &writer, std::ostream &out)
        : m_writer(writer), m_out(out), m_current_ast_path("/"), semanticAnalyzer(SemanticAnalyzer()) {}

    bool has_semantic_errors() const { return !m_semantic_errors.empty(); }
    const std::vector<std::string> &semantic_errors() const { return m_semantic_errors; }

    // // === PROGRAM & CONTEXT ===
    // void visit(chips::program_node& node) override;
    // void visit(chips::preamble_section_node& node) override;
    // void visit(chips::system_section_node& node) override;


    // // === DEFINITIONS ===
    // void visit(chips::definition& node) override;
    // void visit(chips::function_definition& node) override;
    // void visit(chips::logical_definition& node) override;


    // // === WITH / SECTIONS ===
    // void visit(chips::init_section& node) override;
    // void visit(chips::then_section& node) override;

    // void visit(chips::function_output_variant& node) override;

    // // === DATAFLOW TYPES & PARAMETERS ===
    // void visit(chips::function_parameter_variant& node) override;

    // // === PROGRAM & CONTEXT ===
    // void visit(chips_node &chips) override;
    // void visit(preambles_node &node) override;
    // void visit(preamble_node &node) override;
    // void visit(system_node &node) override;

    // // === SYSTEM STATEMENTS ===
    // void visit(s_statements_node &node) override;
    // void visit(const s_statements_node &node) override;
    // void visit(s_statement_node &node) override;

    // // === 3. S_STATEMENT subtypes ===
    // void visit(s_loop_node &node) override;
    // void visit(s_if_node &node) override;
    // void visit(s_if_else_node &node) override;
    // void visit(functionnal_block_instanciation_node &node) override;
    // void visit(implements_node &node) override;
    // void visit(link_node &node) override;
    // void visit(plugging_node &node) override;

    // // === 4. DECLARATION CONTEXT (preamble children) ===
    // void visit(object_definition_node &node) override;
    // void visit(function_definition_node &node) override;
    // void visit(logical_function_definition_node &node) override;
    // void visit(physical_function_definition_node &node) override;
    // void visit(collective_operation_definition_node &node) override;
    // void visit(implementation_definition_node &node) override;
    // void visit(node_mappings_node &node) override;
    // void visit(c_signature_node &node) override;
    // void visit(output_node &node) override;

    // // === 5. WITH / SECTIONS ===
    // void visit(with_section_node &node) override;
    // void visit(with_statements_node &node) override;
    // void visit(with_statement_node &node) override;
    // void visit(with_two_identifier_node &node) override;
    // void visit(with_context_statement_node &node) override;
    // void visit(init_section_node &node) override;
    // void visit(then_section_node &node) override;
    // void visit(statement_node &node) override;
    // void visit(dataflow_full_declaration_node &node) override;
    // void visit(variable_assignment_node &node) override;
    // void visit(context_variable_assignment_node &node) override;

    // void visit(physical_named_outputs_node &node) override;
    // void visit(physical_named_output_node &node) override;
    // void visit(named_outputs_node &node) override;
    // void visit(named_output_node &node) override;
    // void visit(actuator_node &node) override;
    // void visit(statements_node &node) override;
    // void visit(rhs_assignment_node &node) override;
    // void visit(assignment_node &node) override;
    // void visit(this_attribute_node &node) override;
    // void visit(function_call_statement_node &node) override;
    // void visit(if_node &node) override;
    // void visit(if_else_node &node) override;
    // void visit(loop_node &node) override;
    // void visit(block_node &node) override;

    // // === 6. EXPRESSIONS ===
    // void visit(expression_node &node) override;
    // void visit(suffixable_node &node) override;
    // void visit(binary_expression_node &node) override;
    // void visit(unary_expression_node &node) override;
    // void visit(number_literal_node &node) override;
    // void visit(function_call_node &node) override;
    // void visit(variable_node &node) override;
    // void visit(plugging_expr_node &node) override;
    // void visit(collective_cast_node &node) override;
    // void visit(collective_operation_node &node) override;
    // void visit(object_virtual_output_node &node) override;
    // void visit(object_physical_attribute_node &node) override;
    // void visit(cast_node &node) override;
    // void visit(stop_node &node) override;
    // void visit(input_node &node) override;
    // void visit(c_cast_node &node) override;
    // void visit(context_expression_node &node) override;
    // void visit(integrated_function_node &node) override;
    // void visit(context_decl_node &node) override;
    // void visit(suffixes_node &node) override;
    // void visit(suffixised_node &node) override;
    // void visit(paren_expression_node &node) override;

    // // === 6.5. COLLECTIVE / CONFIGURATION HELPERS ===
    // void visit(c_keywords_node &node) override;
    // void visit(spread_node &node) override;
    // void visit(collect_node &node) override;
    // void visit(c_statements_node &node) override;
    // void visit(c_statement_node &node) override;
    // void visit(c_loop_node &node) override;
    // void visit(c_if_node &node) override;
    // void visit(c_if_else_node &node) override;
    // void visit(c_expressions_node &node) override;
    // void visit(c_output_node &node) override;
    // void visit(c_optionnal_outputs_node &node) override;
    // void visit(collective_dataflow_defaulted_decls_node &node) override;
    // void visit(collective_dataflow_defaulted_decl_node &node) override;
    // void visit(collective_dataflow_full_declaration_node &node) override;
    // void visit(collective_rhs_assignment_node &node) override;
    // void visit(c_variable_assignment_node &node) override;
    // void visit(c_context_variable_assignment_node &node) override;

    // // === 7. DATAFLOW TYPES & PARAMETERS ===
    // void visit(dataflow_type_node &node) override;
    // void visit(physical_dataflow_parameter_type_node &node) override;
    // void visit(expressions_node &node) override;
    // void visit(dataflow_parameter_list_node &node) override;
    // void visit(physical_dataflow_parameter_list_node &node) override;
    // void visit(dataflow_parameter_decls_node &node) override;
    // void visit(physical_dataflow_parameter_decls_node &node) override;
    // void visit(dataflow_parameter_decl_node &node) override;
    // void visit(physical_dataflow_parameter_decl_node &node) override;

    // // === 7. FALLBACK (tous les autres) ===
    void visit(chips::ast_node &node) override;

    void printErrors() const {
        semanticAnalyzer.printErrors();
    }

    void printWarnings() const {
        semanticAnalyzer.printWarnings();
    }

    void printSummary() const {
        semanticAnalyzer.printSummary();
    }

    bool hasErrors() const { return semanticAnalyzer.hasErrors(); }

    bool hasWarnings() const { return semanticAnalyzer.hasWarnings(); }

    void verifyDependencyGraph() { semanticAnalyzer.verifyGraphCycle(); }

private:
    enum class StatementFamily {
        Auto,
        Primitive,
        System,
        Node,
        Collective,
        Implementation
    };

    // Structure pour stocker les informations de symbole
    struct SymbolInfo {
        std::string path;        // Chemin XMI
        std::string type;        // Type: "channel", "contextual", "variable", "object", "physical", "logical", "sensor"
        
        SymbolInfo() = default;
        SymbolInfo(const std::string& p, const std::string& t = "unknown") 
            : path(p), type(t) {}
    };

    // Structure pour stocker les informations de définition
    struct DefinitionInfo {
        std::string name;           // Nom de la définition
        std::string type;           // Type: "physical", "object", "logical", etc.
        std::string path;           // Chemin XMI complet: //@preamble/@definitions.X
        int index;                  // Index dans la liste des définitions
        std::map<std::string, SymbolInfo> variables;  // Nom -> info des variables/canaux déclarés dans le with
        
        DefinitionInfo() = default;
        DefinitionInfo(const std::string& n, const std::string& t, const std::string& p, int i) 
            : name(n), type(t), path(p), index(i) {}
    };

    // Helpers
    std::ostream &out() { return m_out; }
    std::string get_ast_path() const { return m_current_ast_path; }
    std::string get_ast_path_by_name(const std::string &name);
    SymbolInfo get_symbol_info(const std::string &name);
    void register_variable(const std::string &name, const std::string &path, const std::string &type = "variable") {
        auto existing = m_symbol_table.find(name);
        if (existing != m_symbol_table.end()) {
            report_semantic_error("Duplicate variable declaration: " + name);
        }
        m_symbol_table[name] = SymbolInfo(path, type);
    }
    
    // Track a definition (called when visiting definition nodes)
    void register_definition(const std::string &name, const std::string &type, const std::string &path, int index) {
        m_definitions_table[name] = DefinitionInfo(name, type, path, index);
        std::cerr << "[DEBUG] Definition '" << name << "' enregistrée avec le chemin: " << path << std::endl;
    }
    
    // Register a variable within a definition (called when visiting with/init/then statements)
    void register_definition_variable(const std::string &def_name, const std::string &var_name, const std::string &var_path, const std::string &var_type) {
        auto it = m_definitions_table.find(def_name);
        if (it != m_definitions_table.end()) {
            it->second.variables[var_name] = SymbolInfo(var_path, var_type);
            std::cerr << "[DEBUG] Variable '" << var_name << "' registered in definition '" << def_name << "' with path: " << var_path << std::endl;
        }
    }
    
    // Find the path of a variable within a definition
    SymbolInfo find_variable_in_definition(const std::string &def_name, const std::string &var_name) {
        auto it = m_definitions_table.find(def_name);
        if (it != m_definitions_table.end()) {
            auto var_it = it->second.variables.find(var_name);
            if (var_it != it->second.variables.end()) {
                return var_it->second;
            }
        }
        return SymbolInfo("", "unknown");
    }
    
    void push_ast_path(const std::string &segment) { m_current_ast_path += segment; }
    void pop_ast_path(const std::string &segment) { 
        size_t pos = m_current_ast_path.rfind(segment);
        if (pos != std::string::npos) {
            m_current_ast_path.erase(pos);
        }
    }
    void set_ast_path(const std::string &path) { m_current_ast_path = path; }
    void writeAttribute(const std::string &name, const std::string &value);
    void endEmptyElement();
    std::string getExpressionValue(expression_node &expr);
    void write_collective_rvalue(const std::string &indent, const std::string &tag, expression_node &expr, const std::string &value_type);
    void write_collective_output_expression(expression_node &expr, const std::string &tag, const std::string &indent);
    void write_index_from_suffixes(suffixes_node *suffixes,
                                   const std::string &indent,
                                   const std::string &xvalue_prefix,
                                   const std::string &rvalue_prefix,
                                   bool emit_default);
    void visit_generic(ast_node &node); // squelette commun
    void report_semantic_error(const std::string &message);
    void ensure_namespace_for_prefix(const std::string &ns_prefix);
    void ensure_namespace_for_type(const std::string &type_value);
    StatementFamily detect_statement_family() const;
    std::string statement_prefix(StatementFamily family = StatementFamily::Auto) const;
    std::string statement_type(const std::string &suffix, StatementFamily family = StatementFamily::Auto) const;
    
    // Get xsi:type for variable expression based on symbol type (physical, logical, object)
    std::string get_xsi_type_for_symbol(const SymbolInfo &info);
    
    // Get xsi:type for system declaration based on definition type (physical->physical_declaration, etc.)
    std::string get_declaration_type_from_definition(const std::string &definition_type);

    // Members
    ChipsToXmiWriter &m_writer;
    std::ostream &m_out;
    std::string m_current_ast_path;
    std::map<std::string, SymbolInfo> m_symbol_table;  // nom -> (chemin AST, type)
    std::map<std::string, DefinitionInfo> m_definitions_table;  // nom -> info définition
    std::string m_current_definition;  // Nom de la définition actuellement visitée
    std::string m_impl_def_implementing_node;  // Nom du nœud implémentant (défini lors de visit(implementation_definition_node))
    std::string m_impl_def_implemented_object;  // Nom de l'objet implémenté (défini lors de visit(implementation_definition_node))
    std::string m_statement_tag = "statements";  // Tag name override for if/else sections
    std::vector<std::string> m_semantic_errors;
    int m_extra_statements_generated = 0;  // Compteur de statements supplémentaires générés

    SemanticAnalyzer semanticAnalyzer;
};

#endif // CHIPS_TO_XMI_VISITOR_HPP
