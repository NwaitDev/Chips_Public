#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "antlr4-runtime.h"
#include "ast_node_definitions.hpp"

using namespace chips;

class visitor_env {
	public:

	// type aliases
	using node_definition_table = std::unordered_map<std::string, node_definition*>;
    using collective_table = std::unordered_map<std::string, collective_function_definition*>;

    using channels_table = std::unordered_map<std::string, std::unordered_map<std::string, node_element_declaration<node_element::CHANNEL>*>>;
	
	using contextuals_table = std::unordered_map<std::string, std::unordered_map<std::string, dataflow_type>>;
    using actuator_table = std::unordered_map<std::string, std::unordered_map<std::string, dataflow_type>>;
    using sensor_table = std::unordered_map<std::string, std::unordered_map<std::string, dataflow_type>>;
    using parameter_table = std::unordered_map<std::string, std::unordered_map<std::string, dataflow_type>>;
    using variable_scope = std::unordered_map<std::string, dataflow_type>;
	using output_table = std::unordered_map<std::string, std::unordered_map<std::string, dataflow_type>>;
	using scopes_stack = std::vector<std::unordered_map<std::string, dataflow_type>>;
    using node_scope = std::unordered_map<std::string, ast_node*>;


    std::vector<std::unique_ptr<ast_node>> m_all_nodes; // to be replaced by a non ambiguous name
	scopes_stack m_scopes;
    std::vector<node_scope> m_node_scopes;
    collective_table m_collectives;
    node_definition_table m_nodes;
    std::unordered_map<std::string, logical_definition*> m_logicals;
    std::unordered_map<std::string, physical_definition*> m_physicals;
    std::unordered_map<std::string, object_definition*> m_objects;


    parameter_table m_parameters;
	sensor_table m_sensors;

    contextuals_table m_contextuals;
    std::unordered_map<std::string, node_scope> m_contextual_nodes;
    channels_table m_channels;

    output_table m_outputs;
    actuator_table m_actuators;



    std::string m_support_name;
    std::string m_current_def_name;
    std::vector<input*> m_collective_inputs;
    std::optional<dataflow_type> expected_type_for_input = std::nullopt;
    bool m_system_reached = false;
    std::vector<std::unordered_map<std::string, std::pair<block_type, std::string>>> m_block_scopes;
    std::vector<node_scope> m_block_node_scopes;

    // ctor
    visitor_env(){}
    
    // deleted ctor and operator to prevent default copy assignment
    // (we don't want that because of unique_ptr)
    visitor_env(const visitor_env&) = delete;
    visitor_env& operator=(const visitor_env&) = delete;


	void push_scope();
    void pop_scope();


    bool definition_exists(const std::string& name) const;


    template <dataflow_type type> 
    void declare_variable(const std::string &name) {
    if (m_scopes.empty()) {
        throw std::runtime_error("variable '" + name +
                                "' declared outside of any scope");
    }
    if (m_scopes.back().find(name) != m_scopes.back().end()) {
        throw std::runtime_error("duplicate variable '" + name + "' in '" +
                                m_current_def_name + "'");
    }
    m_scopes.back()[name] = type;
    }


    std::optional<dataflow_type> lookup_variable(const std::string& name) const;

    void declare_variable_node(const std::string& name, ast_node* node);

    template <typename V>
    V* lookup_variable_node(const std::string& name) const {
        for (auto it = m_node_scopes.rbegin(); it != m_node_scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return dynamic_cast<V*>(found->second);
            }
        }
        return nullptr;
    }

	void declare_contextual(const std::string& var, dataflow_type type, ast_node* node = nullptr);
    std::optional<dataflow_type> lookup_contextual(const std::string& var) const;

    template <typename V>
    V* lookup_contextual_node(const std::string& var) const {
        const std::string& owner = m_support_name.empty() ? m_current_def_name : m_support_name;
        auto node = m_contextual_nodes.find(owner);
        if (node == m_contextual_nodes.end()) {
            return nullptr;
        }
        auto it = node->second.find(var);
        return it == node->second.end() ? nullptr : dynamic_cast<V*>(it->second);
    }
    
	void declare_parameter(const std::string& function, const std::string& var, dataflow_type type);
    void declare_sensor(const std::string& function, const std::string& sensor, dataflow_type type);
    std::optional<dataflow_type> lookup_parameter(const std::string& function, const std::string& var) const;
	std::optional<dataflow_type> lookup_sensor(const std::string& function, const std::string& sensor) const;

    void declare_output(const std::string& function, const std::string& name, dataflow_type type);
	void declare_actuator(const std::string& function, const std::string& actuator, dataflow_type type);
    std::optional<dataflow_type> lookup_output(const std::string& function, const std::string& name) const;
    std::optional<dataflow_type> lookup_actuator(const std::string& function, const std::string& actuator) const;

    void declare_channel(const std::string& channel, node_element_declaration<node_element::CHANNEL>* decl);
    node_element_declaration<node_element::CHANNEL>* lookup_channel(const std::string& node, const std::string& channel) const;
	std::size_t channel_count(const std::string& node) const;

    void declare_collective(const std::string& name, collective_function_definition* function);
    collective_function_definition* lookup_collective(const std::string& name, antlr4::ParserRuleContext* ctx) const;


    void declare_definition(const std::string& name, logical_definition* definition);
	logical_definition* lookup_logical(const std::string& name) const;
    void declare_definition(const std::string& name, physical_definition* definition);
    physical_definition* lookup_physical(const std::string& name) const;
    void declare_definition(const std::string& name, object_definition* definition);
    object_definition* lookup_object(const std::string& name) const;

    function_definition* lookup_function(const std::string& name) const;
    node_definition* lookup_node(const std::string &name) const;
    
	void declare_block(const std::string& name, block_type type, const std::string& definition, ast_node* node = nullptr);
    std::pair<block_type, std::string> lookup_block(const std::string& name, antlr4::ParserRuleContext* ctx) const;
    bool is_block(const std::string& name) const;

    template <block_type bt>
    block_variable<bt>* lookup_block_node(const std::string& name) const {
        for (auto it = m_block_node_scopes.rbegin(); it != m_block_node_scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return dynamic_cast<block_variable<bt>*>(found->second);
            }
        }
        return nullptr;
    }
    
    struct scope_guard {
		visitor_env& venv;
        explicit scope_guard(visitor_env& venv) : venv(venv) { venv.push_scope(); }
        ~scope_guard() { venv.pop_scope(); }
        scope_guard(const scope_guard&) = delete;
        scope_guard& operator=(const scope_guard&) = delete;
    };

	const std::string& current_definition() const { return m_current_def_name; }
    bool system_reached() const { return m_system_reached; }

};