#ifndef CHIPS_TO_XMI_VISITOR_HPP
#define CHIPS_TO_XMI_VISITOR_HPP

#include "ChipsToXmiWriter.hpp"
#include "ast_base.hpp"
#include "utils.hpp"

#include <ostream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

#include <typeinfo>
#include <cxxabi.h>

using namespace chips;

/// @brief Complete XMI Visitor - implements ALL chips::visitor methods
class ChipsToXmiVisitor : public visitor{
    public:
        using visitor::visit;

        ChipsToXmiVisitor(ChipsToXmiWriter &writer, std::ostream &out) 
        : m_writer(writer), m_out(out), m_current_ast_path("/"){}

        template<dataflow_type dft, expression_env expenv>
        void visit(rvalue<dft,expenv>& node);

        template<dataflow_type dft, expression_env expenv>
        void visit(direct<dft, expenv>& node);

        template<dataflow_type dft, expression_env expenv>
        void visit(plus<dft,expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(minus<dft,expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(uminus_operator<dft, expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(mult<dft,expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(chips::div<dft,expenv>& node);
        template<expression_env expenv>
        void visit(mod<expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(cast_as<dft,expenv>& node);
        template<expression_env expenv, dataflow_type dft>
        void visit(gt<expenv,dft>& node);
        template<expression_env expenv, dataflow_type dft>
        void visit(lt<expenv,dft>& node);
        template<expression_env expenv, dataflow_type dft>
        void visit(leq<expenv,dft>& node);
        template<expression_env expenv, dataflow_type dft>
        void visit(geq<expenv,dft>& node);
        template<expression_env expenv>
        void visit(or_operator<expenv>& node);
        template<expression_env expenv>
        void visit(and_operator<expenv>& node);
        template<expression_env expenv>
        void visit(not_operator<expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(eq<dft,expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(neq<dft,expenv>& node);

        template<dataflow_type dft, expression_env expenv>
        void visit(variable_expression<dft,expenv>& node);
        template<dataflow_type dft, expression_env expenv>
        void visit(function<dft,expenv>& node);

        void visit(input& node);
        void visit(stop& node);

        void visit(ast_node& node) override;

        // ── FIX BUG 5 : 34 méthodes virtuelles pures manquantes ──────────────
        // chips::visitor déclare 35 méthodes = 0. ChipsToXmiVisitor n'en
        // implémentait que 2 → classe abstraite, impossible à instancier.
        // Stubs à compléter progressivement avec la vraie logique XMI.
        void visit(program_node& node);// override              { out() << "<!-- program_node -->\n"; }
        void visit(preamble_section_node& node);// override     { out() << "<!-- preamble_section_node -->\n"; }
        void visit(system_section_node& node);// override       { out() << "<!-- system_section_node -->\n"; }
        // void visit(primitive_variable& node) override        { out() << "<!-- primitive_variable -->\n"; }
        // void visit(node_variable& node) override             { out() << "<!-- node_variable -->\n"; }
        // void visit(collective_variable& node) override       { out() << "<!-- collective_variable -->\n"; }
        // void visit(system_variable& node) override           { out() << "<!-- system_variable -->\n"; }
        // void visit(implements_statement& node) override      { out() << "<!-- implements_statement -->\n"; }
        // void visit(channel_plugging& node) override          { out() << "<!-- channel_plugging -->\n"; }
        void visit(linking_statement& node);// override         { out() << "<!-- linking_statement -->\n"; }
        void visit(default_output& node);// override            { out() << "<!-- default_output -->\n"; }
        void visit(target_output& node);// override             { out() << "<!-- target_output -->\n"; }
        // void visit(channeled_output& node) override          { out() << "<!-- channeled_output -->\n"; }
        // void visit(definition& node) override                { out() << "<!-- definition -->\n"; }
        void visit(with_section& node);// override              { out() << "<!-- with_section -->\n"; }
        void visit(init_section& node);// override              { out() << "<!-- init_section -->\n"; }
        void visit(then_section& node);// override              { out() << "<!-- then_section -->\n"; }
        void visit(collectiveops_section& node);// override     { out() << "<!-- collectiveops_section -->\n"; }
        void visit(accumulator_definition& node);// override    { out() << "<!-- accumulator_definition -->\n"; }
        // void visit(node_definition& node) override           { out() << "<!-- node_definition -->\n"; }
        // void visit(object_definition& node) override         { out() << "<!-- object_definition -->\n"; }
        // void visit(function_definition& node) override       { out() << "<!-- function_definition -->\n"; }
        void visit(logical_definition& node);// override        { out() << "<!-- logical_definition -->\n"; }
        void visit(physical_definition& node);// override       { out() << "<!-- physical_definition -->\n"; }
        void visit(object_definition& node);
        void visit(collective_function_definition& node);
        // void visit(implementation_defintion& node) override  { out() << "<!-- implementation_defintion -->\n"; }
        // void visit(collective_function_definition& node) override { out() << "<!-- collective_function_definition -->\n"; }
        // void visit(system_iterable& node) override           { out() << "<!-- system_iterable -->\n"; }
        // void visit(linkable& node) override                  { out() << "<!-- linkable -->\n"; }
        // void visit(support& node) override                   { out() << "<!-- support -->\n"; }
        // void visit(interface& node) override                 { out() << "<!-- interface -->\n"; }
        // void visit(implementer& node) override               { out() << "<!-- implementer -->\n"; }
        // void visit(node_variable_expression& node) override  { out() << "<!-- node_variable_expression -->\n"; }
        // void visit(channel_eater& node) override             { out() << "<!-- channel_eater -->\n"; }
        // void visit(channel_feeder& node) override            { out() << "<!-- channel_feeder -->\n"; }
        // ── FIN stubs ─────────────────────────────────────────────────────────

        template<dataflow_kind dfk, dataflow_type dft>
        void handle_feeding_statement(feeding_statement<dfk, dft>& node);

        template<dataflow_kind dfk, dataflow_type dft>
        void visit(eater<dfk,dft>& node);

        template<dataflow_kind dfk, dataflow_type dft>
        void visit(feeder<dfk, dft>& node);

        template<dataflow_kind dfk, dataflow_type dft>
        void visit(feeder_block_expression<dfk, dft>& node);

        template<dataflow_kind dfk, dataflow_type dft>
        void visit(collective_cast<dfk, dft>& node);

        void visit(std::vector<physical_parameter_variant>& node);
        void visit(std::vector<function_parameter_variant>& node);

        template<expression_env expenv>
        void visit(std::vector<int_rvalue_expression_variant<expenv>>& node);

        void visit(std::vector<channeled_output>& node);

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
        // std::string getExpressionValue(expression_node &expr);
        // void write_collective_rvalue(const std::string &indent, const std::string &tag, expression_node &expr, const std::string &value_type);
        // void write_collective_output_expression(expression_node &expr, const std::string &tag, const std::string &indent);
        // void write_index_from_suffixes(suffixes_node *suffixes,
        //                             const std::string &indent,
        //                             const std::string &xvalue_prefix,
        //                             const std::string &rvalue_prefix,
        //                             bool emit_default);
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

        template<dataflow_type dft, expression_env expenv>
        void arithmetic_visit(rvalue<dft, expenv>& node){
            if(auto* dir = dynamic_cast<direct<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is direct" << std::endl;
                visit(*dir);
            }else if(auto* pl = dynamic_cast<plus<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is plus" << std::endl;
                visit(*pl); 
            }else if(auto* min = dynamic_cast<minus<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is minus" << std::endl;
                visit(*min);
            }else if(auto* min = dynamic_cast<uminus_operator<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is uminus" << std::endl;
                visit(*min);
            }else if(auto* mu = dynamic_cast<mult<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is mult" << std::endl;
                visit(*mu); 
            }else if(auto* di = dynamic_cast<chips::div<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is div" << std::endl;
                visit(*di); 
            }else if(auto* mo = dynamic_cast<mod<expenv>*>(&node)){
                std::cerr << "rvaleue is mod" << std::endl;
                visit(*mo); 
            }else if(auto* cast = dynamic_cast<cast_as<dft, expenv>*>(&node)){
                std::cerr << "rvaleue is cast" << std::endl;
                visit(*cast);
            }else if(auto* var = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                std::cerr << "rvaleue is var" << std::endl;
                visit(*var);
            }else if(auto* func = dynamic_cast<function<dft,expenv>*>(&node)){
                std::cerr << "rvalue is func" << std::endl;
                visit(*func);
            }else if(auto* in = dynamic_cast<input*>(&node)){
                std::cerr << "rvalue is input" << std::endl;
                visit(*in);
            }else if(auto* st = dynamic_cast<stop*>(&node)){
                std::cerr << "rvalue is stop" << std::endl;
                visit(*st);
            }else{
                std::cerr << "ERROR RVALUE IS NOTHING UP THERE: " << typeid(node).name() << std::endl;
            }
        }

        template<dataflow_type dft, expression_env expenv>
        void binary_boolean_visit(rvalue<dft,expenv>& node){
            std::cout << "binary" << std::endl;
            if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<eq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<neq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);

            }else if(auto* p = dynamic_cast<direct<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<direct<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<plus<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<plus<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<minus<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<minus<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<uminus_operator<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<uminus_operator<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<mult<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<mult<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<mod<expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<chips::div<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<chips::div<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<cast_as<dataflow_type::INT,expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<cast_as<dataflow_type::FLOAT,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::INT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::FLOAT>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<eq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::INT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::FLOAT, expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<neq<dataflow_type::BOOL, expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<and_operator<expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<or_operator<expenv>*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<not_operator<expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                visit(*p);
            }

            else if(auto* p = dynamic_cast<input*>(&node)){
                visit(*p);
            }else if(auto* p = dynamic_cast<stop*>(&node)){
                visit(*p);
            }

            std::cerr << "NOTHING UP THERE" << std::endl;
        }

        std::string repeat(const std::string&  s, int n){
            std::string out;
            // Protection: éviter les allocations massives si n est négatif
            if(n < 0) {
                std::cerr << "[WARNING] repeat() called with negative count: " << n << std::endl;
                n = 0;
            }
            std::size_t count = static_cast<std::size_t>(n);
            out.reserve(s.size() * count);
            for(std::size_t i = 0; i < count; i++){
                out += s;
            }
            return out;
        }

        std::string toLower(const std::string& str) {
            std::string result = str;
            std::transform(result.begin(), result.end(), result.begin(),
                        [](unsigned char c){ return std::tolower(c); });
            return result;
        }

        template<block_type bt>
        void handle_statement_declaration(block_declaration<bt>& node);

        template<dataflow_type dft, statement_env stenv>
        void handle_statement_declaration(dataflow_declaration<dft, stenv>& node);

        template<dataflow_type dft, statement_env stenv>
        void handle_statement_assignment(dataflow_assignment<dft, stenv>& node);

        template<node_element ne>
        void handle_node_element_declaration(node_element_declaration<ne>& node);

        template<expression_env expenv>
        void handle_condition(bool_rvalue_expression_variant<expenv>& node);

        template<statement_env stenv>
        void handle_statement(typename SttEnvToSttVariant<stenv>::type& statement);

        template<statement_env stenv>
        void handle_section_if(if_section<stenv>& node);

        template<statement_env stenv>
        void handle_section_else(else_section<stenv>& node);

        template<statement_env stenv>
        void handle_statement_if(if_statement<stenv>& node);

        template<statement_env stenv>
        void handle_statement_if_else(if_else_statement<stenv>& node);

        template<statement_env stenv, dataflow_type dft>
        void handle_foreach(foreach_statement<stenv, dft>& node);

        void handle_outputs(std::vector<function_output_variant>& outputs, bool is_actuator = false);

        template<dataflow_type dft, expression_env expenv>
        void handle_binary_expression(rvalue<dft, expenv>* left, rvalue<dft,expenv>* right, const std::string& type);

        template<dataflow_type dft, expression_env expenv>
        void handle_binary_boolean(rvalue<dft,expenv>* left, rvalue<dft,expenv>* right, const std::string& type);

        template<dataflow_type dft, expression_env expenv>
        bool only_one_child(rvalue<dft,expenv>& node){
            if(dynamic_cast<direct<dft,expenv>*>(&node) ||  dynamic_cast<input*>(&node) || dynamic_cast<stop*>(&node) ||
               dynamic_cast<variable_contextual_expression<dft,expenv>*>(&node)){
                std::cerr << "ONLY ONE CHILD" << std::endl;
                return true;
            }
            if(auto* var = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
                // out() << "TAILLE DE VAR: " << var->get_index().size() << "\n";
                return var->get_index().empty();
            }
            if(auto* func = dynamic_cast<function<dft,expenv>*>(&node)){
                return func->get_parameters().empty();
            }
            std::cerr << "NOT ONLY ONE CHILD" << std::endl;
            return false;
        }

        void dumpSymbolTable(){
            std::cout << "SYMBOL TABLE" << std::endl;
            for(const auto& [k, v] : m_symbol_table){
                std::cout << k << " (path: " << v.path << ", type:" << v.type << std::endl;
            }
            std::cout << "==============" << std::endl;
        }

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

        expression_env current_env;
        int def_index = 0;
        int param_index = 0;
        int sensor_index = 0;
        int nbTab = 1;
};

#endif