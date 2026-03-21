#ifndef __chips_system_spe__
#define __chips_system_spe__

#include "forward_declarations.hpp"
#include "ast_base.hpp"
#include "meta_type_conversions.hpp"
#include "metamodel_enums.hpp"
#include "ast_lrxvalues.hpp"

#include <vector>

namespace chips {

    template<dataflow_kind dfk, dataflow_type dft>
    class feeder : public ast_node{};
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract : public ast_node {}; 
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract : public ast_node {};

    class node_variable_expression : public ast_node{
        public:
            virtual void hello() override = 0;
    }; // abstract

    template<block_type bt>
    class system_variable_block_expression : public ast_node, public system_iterable
    {
    private:
        using block_variable_type = typename BlockTypeToBlockVariable<bt>::type;
        block_variable_type& m_variable;
        // rvalue<dataflow_type::INT,expression_env::SYSTEM> m_index; //TODO: regarder le probleme
    };

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing LOGICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::LOGICAL> : public linkable{};

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing PHYSICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::PHYSICAL> : public support, public node_variable_expression, implementer {};

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing OBJECT specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::OBJECT> 
    : public linkable, public support, public node_variable_expression, public interface, public implementer {};


    template<dataflow_kind dfk, dataflow_type dft>
    class eater : public ast_node
    {
    private:
        functional_block_variant m_variable_expression;
        function_parameter<dfk,dft>& m_parameter;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    }; 

    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>, public ast_node
    {
    private:
        functional_block_variant m_variable_expression;
        function_output<dfk,dft>& m_output;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };


    class channel_eater : public ast_node
    {
        private:
        // node_variable_expression m_node;
        std::unique_ptr<node_variable_expression> m_node;
        std::shared_ptr<node_element_declaration<node_element::CHANNEL>> m_eating_channel;

        public:
            
            // void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class channel_feeder : public ast_node
    {
        private:
            // node_variable_expression m_node;
            std::unique_ptr<node_variable_expression> m_node;
            std::shared_ptr<node_element_declaration<node_element::CHANNEL>> m_eating_channel;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft> {
    private:
        collective_function_definition& variable_expression;
        feeder<dfk, dft> m_feeder;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
}

#endif