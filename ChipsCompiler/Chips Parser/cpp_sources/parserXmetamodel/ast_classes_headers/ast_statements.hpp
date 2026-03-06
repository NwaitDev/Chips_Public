#ifndef __chips_statements__
#define __chips_statements__
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_system_specific.hpp"

namespace chips {

    template<dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION>
    {
        private:
        using df_variable_type = typename ChipsEnvToVariableKind<dft,stenv>::type;
        df_variable_type m_variable;
    };

    
    template<dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT> 
    {
    private:
        static constexpr expression_env expr_env = ChipsEnvToExpressionEnv<stenv>::value;
        lvalue<dft, expr_env> m_lvalue;
        rvalue<dft, expr_env> m_rvalue;
    };

    template<statement_env stenv>
    class if_section : public ast_node  
    {
        using statement_type = typename ChipsStatementEnvToStatementVariant<stenv>::type;
        std::vector<statement_type> m_if_statements;
    };
    template<statement_env stenv>
    class else_section: public ast_node  
    {
        using statement_type = typename ChipsStatementEnvToStatementVariant<stenv>::type;
        std::vector<statement_type> m_else_statements;
    };

    template<statement_env stenv>
    class if_statement : public statement<stenv,recurring_statement::IF> 
    {
    private:
        static constexpr expression_env expr_env = ChipsEnvToExpressionEnv<stenv>::value;
        rvalue<dataflow_type::BOOL, expr_env> m_condition;
        if_section<stenv> m_if_section;
    };

    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv> 
    {
    private:
        else_section<stenv> m_else_section;
    };

    template<statement_env stenv, dataflow_type dft>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH>  
    {
    private:
        using statement_type = typename ChipsStatementEnvToStatementVariant<stenv>::type;
        static constexpr expression_env expenv = ChipsEnvToExpressionEnv<stenv>::value;
        dataflow_declaration<dft,stenv> m_iterator;
        rvalue<dft,expenv>  m_iterable_expr;
        std::vector<statement_type> m_statements;
    };
    
    template<block_type bt>
    class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH> 
    {
    private:
        block_declaration<bt> m_iterator;
        system_variable_block_expression<bt> m_iterable_expression;
        std::vector<system_statement_variant> m_statements;
    };

    


    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM , recurring_statement::DECLARATION>  
    {
    private:
        using block_definition_t = typename BlockTypeToAstBlockDefinition<bt>::type;
        using block_variable_t = typename ChipsBlockTypeToAstBlockVariable<bt>::type;

        block_definition_t& m_defintion;
        block_variable_t m_variable;
        
    };

    class implements_statement : public system_statement<recurring_statement::IMPLEMENTS>{}; 

    class channel_plugging : public system_statement<recurring_statement::PLUGGING>  
    {
    private:
        // need to perform check on channel types
        // need to perform check on connectivity
        // (only connect channels 1-to-1, never 1-to-many or many-to-one)
        
        channel_eater m_eater;
        channel_feeder m_feeder;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recurring_statement::FEEDING>, public feeder<dft,dfk>  
    {
    private:
        eater<dfk,dft> m_eater;
        feeder<dfk,dft> m_feeder;
    };

    class linking_statement : public system_statement<recurring_statement::LINKING>  
    {
    private:
        linkable m_linked_component;
        support m_support_node;
    };


    template <node_element ne>
    class aliasing_statement : public implementation_statement<recurring_statement::ALIASING>{}; 

    template<node_element ne>
    class node_element_declaration : public node_statement<recurring_statement::DECLARATION>  
    {
    private:
        using node_variable_t = ChipsNodeElementToAstNodeVariable<ne>::type;
        node_variable_t m_variable; // == type_identifier in case of channel declaration
        std::string m_declared_name; // == identifier in case of contextual variable
    };
}

#endif