#ifndef __chips_statements__
#define __chips_statements__

#include <vector>

#include "ast_variables.hpp"

namespace chips
{

    /**
     * Abstract class
     * Node of the AST that represents a statement in any
     * Chips code environment.
     */
    template <statement_env, recurring_statement>
    class statement : public ast_node
    {
    };

    /**
     * Concrete class
     * Node of the AST representing a dataflow declarations in any context.
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template <dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION>
    {
    public:
        using df_variable_type = typename SttEnvToVariableKind<dft, stenv>::type;
        df_variable_type m_variable;

        dataflow_declaration() = default;

        dataflow_declaration(std::string name) : m_variable(dataflow_primitive_variable<dft>(name)) {};

        dataflow_declaration(df_variable_type variable)
            : m_variable(variable) {}

        inline void set_variable(df_variable_type var) { m_variable = var; }
        inline df_variable_type get_variable() { return m_variable; }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            get_variable().hello();
            std::cout << ";" << std::endl;
        }
    };

    /**
     * Concrete class
     * Node of the AST representing a dataflow assignements in any context
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template <dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT>
    {
    public:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        lvalue<dft, expr_env> *m_lvalue;
        rvalue<dft, expr_env> *m_rvalue;

        dataflow_assignment() = default;
        dataflow_assignment(lvalue<dft, expr_env> *lhs, rvalue<dft, expr_env> *rhs)
            : m_lvalue(lhs), m_rvalue(rhs) {}

        lvalue<dft, expr_env> *get_lhs() { return m_lvalue; }
        rvalue<dft, expr_env> *get_rhs() { return m_rvalue; }

        void accept(visitor &v) { v.visit(*this); }
        void hello()
        {
            // std::cout << "DATAFLOW ASSIGNMENT" << std::endl;

            get_lhs()->hello();
            std::cout << " = ";
            get_rhs()->hello();
            std::cout << ";" << std::endl;
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_statement
     * is evaluated as true
     */
    template <statement_env stenv>
    class if_section : public ast_node
    {
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        std::vector<statement_type> m_if_statements;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_else_statement
     * is evaluated as false
     */
    template <statement_env stenv>
    class else_section : public ast_node
    {
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        std::vector<statement_type> m_else_statements;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents an if statement.
     * if (bool rvalue) { if_section }
     */
    template <statement_env stenv>
    class if_statement : public statement<stenv, recurring_statement::IF>
    {
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        bool_rvalue_expression_variant<expr_env> m_condition;
        if_section<stenv> m_if_section;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents an if_else statement
     * if (bool rvalue) { if_section } else { else_section }
     */
    template <statement_env stenv>
    class if_else_statement : public if_statement<stenv>
    {
        else_section<stenv> m_else_section;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * Generic version only suitable for iterating over dataflow
     * variables
     */
    template <statement_env stenv, dataflow_type dft>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH>
    {
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        static constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
        dataflow_declaration<dft, stenv> m_iterator;
        primitive_iterable_variant<expenv> m_iterable_expr;
        std::vector<statement_type> m_statements;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * System specific version only suitable for iterating
     * over components variables (logical, physical or objects)
     */
    template <block_type bt>
    class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH>
    {
        block_declaration<bt> m_iterator;
        system_variable_block_expression<bt> m_iterable_expression;
        std::vector<system_statement_variant> m_statements;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents the declaration
     * of a component variable (object, physical or logical)
     */
    template <block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM, recurring_statement::DECLARATION>
    {
        using block_definition_t = typename BlockTypeToBlockDef<bt>::type;
        using block_variable_t = typename BlockTypeToBlockVariable<bt>::type;

        block_definition_t *m_defintion;
        block_variable_t m_variable;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents some concept that is not
     * theoretically gounded yet.
     * Work in progress, do not use.
     */
    class implements_statement : public system_statement<recurring_statement::IMPLEMENTS>
    {
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a channel output of a component to a channel input
     * of another component.
     * Such statement should assert that :
     * - channel types are compatibles
     * - connected channels inputs and outputs are not already
     *   connected
     */
    class channel_plugging : public system_statement<recurring_statement::PLUGGING>
    {
        // need to perform check on channel types
        // need to perform check on connectivity
        // (only connect channels 1-to-1, never 1-to-many or many-to-one)

        channel_eater *m_eater;
        channel_feeder *m_feeder;
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a component dataflow output to a component dataflow
     * parameter.
     * Such statement should assert that
     * connected inputs and outputs are not already connected
     * (unless a collective_cast node is used)
     */
    template <dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recurring_statement::FEEDING>, public feeder<dfk, dft>
    {
        eater<dfk, dft> m_eater;
        feeder<dfk, dft> m_feeder;
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents the physical
     * dependency of two objects or of a node to a physical block
     * using the following syntax :
     * link linkable to support;
     */
    class linking_statement : public system_statement<recurring_statement::LINKING>
    {
        linkable *m_linked_component;
        support *m_support_node;
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the implementation
     * of a contextual variable by another contextual variable
     * or of a channel by another channel.
     * Work in progress, do not use
     */
    template <node_element ne>
    class aliasing_statement : public implementation_statement<recurring_statement::ALIASING>
    {
        void hello() {}
    };

    /**
     * Concrete class
     * Node of the AST that represents the declaration
     * of a contextual or of a channel in a with section
     */
    template <node_element ne>
    class node_element_declaration : public node_statement<recurring_statement::DECLARATION>
    {
    public:
        using node_variable_t = typename NodeElemToNodeVariable<ne>::type;
        node_variable_t m_variable_type; // == type_identifier in case of channel declaration
        std::string m_declared_name;     // == identifier in case of contextual variable
        void hello() {}
        node_element_declaration(node_variable_t type, std::string vname) : m_variable_type(type), m_declared_name(vname) {}
    };
}

#endif