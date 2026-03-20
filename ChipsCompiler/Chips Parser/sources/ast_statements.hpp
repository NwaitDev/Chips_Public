#ifndef __chips_statements__
#define __chips_statements__

#include "forward_declarations.hpp"
#include "ast_base.hpp"
#include "meta_type_conversions.hpp"

#include <vector>

// #include "ast_system_specific.hpp"
// #include "ast_base.hpp"
// #include "ast_lrxvalues.hpp"
// #include "ast_definitions.hpp"
// #include "ast_program.hpp"
// #include "ast_variables.hpp"
// #include "ast_inoutputs.hpp"

namespace chips {

    template<statement_env, recurring_statement>
    class statement : public ast_node{};

    template<dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION>
    {
        private:
        using df_variable_type = typename SttEnvToVariableKind<dft,stenv>::type;
        std::shared_ptr<df_variable_type> m_variable;

        public:
            dataflow_declaration() = default;

            dataflow_declaration(std::shared_ptr<df_variable_type> variable)
                : m_variable(std::move(variable)){}

            df_variable_type* get_variable() { return m_variable.get(); }
            
            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    
    template<dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT> 
    {
    private:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        lvalue<dft, expr_env> m_lvalue;
        rvalue<dft, expr_env> m_rvalue;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<statement_env stenv>
    class if_section : public ast_node  
    {
        private:
            using statement_type = typename SttEnvToSttVariant<stenv>::type;
            std::vector<statement_type> m_if_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    template<statement_env stenv>
    class else_section: public ast_node  
    {
        private:
            using statement_type = typename SttEnvToSttVariant<stenv>::type;
            std::vector<statement_type> m_else_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<statement_env stenv>
    class if_statement : public statement<stenv,recurring_statement::IF> 
    {
    private:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        rvalue<dataflow_type::BOOL, expr_env> m_condition;
        if_section<stenv> m_if_section;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv> 
    {
    private:
        else_section<stenv> m_else_section;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<statement_env stenv, dataflow_type dft>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH>  
    {
    private:
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        static constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
        dataflow_declaration<dft,stenv> m_iterator;
        rvalue<dft,expenv>  m_iterable_expr;
        std::vector<statement_type> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    
    template<block_type bt>
    class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH> 
    {
    private:
        block_declaration<bt> m_iterator;
        system_variable_block_expression<bt> m_iterable_expression;
        std::vector<system_statement_variant> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    


    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM , recurring_statement::DECLARATION>  
    {
    private:
        using block_definition_t = typename BlockTypeToBlockDef<bt>::type;
        using block_variable_t = typename BlockTypeToBlockVariable<bt>::type;

        block_definition_t& m_defintion;
        block_variable_t m_variable;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
        
    };

    class implements_statement : public system_statement<recurring_statement::IMPLEMENTS>{
        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    }; 

    class channel_plugging : public system_statement<recurring_statement::PLUGGING>  
    {
    private:
        // need to perform check on channel types
        // need to perform check on connectivity
        // (only connect channels 1-to-1, never 1-to-many or many-to-one)
        
        // channel_eater m_eater;
        // channel_feeder m_feeder;

        std::unique_ptr<channel_eater> m_eater;
        std::unique_ptr<channel_feeder> m_feeder;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recurring_statement::FEEDING>, public feeder<dfk,dft>  
    {
    private:
        eater<dfk,dft> m_eater;
        feeder<dfk,dft> m_feeder;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class linking_statement : public system_statement<recurring_statement::LINKING>  
    {
    private:
        linkable m_linked_component;
        support m_support_node;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };


    template <node_element ne>
    class aliasing_statement : public implementation_statement<recurring_statement::ALIASING>{
        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    }; 

    template<node_element ne>
    class node_element_declaration : public node_statement<recurring_statement::DECLARATION>  
    {
    private:
        using node_variable_t = typename NodeElemToNodeVariable<ne>::type;
        node_variable_t m_variable; // == type_identifier in case of channel declaration
        std::string m_declared_name; // == identifier in case of contextual variable

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
}

#endif