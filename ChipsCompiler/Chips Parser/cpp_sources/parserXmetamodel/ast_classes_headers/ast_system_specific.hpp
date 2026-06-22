#ifndef __chips_system_spe__
#define __chips_system_spe__
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include <vector>

namespace chips {

    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract : public ast_node {}; 
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract : public ast_node {};

    class node_variable_expression : public ast_node{}; // abstract

    template<block_type bt>
    class system_variable_block_expression : public ast_node, public system_iterable
    {
    private:
        using block_type = typename ChipsBlockTypeToAstBlockVariable<bt>::type;
        block_type& m_variable;
        rvalue<dataflow_type::INT,expression_env::SYSTEM> m_index;
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
    class eater
    {
    private:
        functional_block_variant m_variable_expression;
        function_parameter<dfk,dft>& m_parameter;
    }; 

    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>, public ast_node
    {
    private:
        functional_block_variant m_variable_expression;
        function_output<dfk,dft>& m_output;
    };


    class channel_eater : public ast_node
    {
        private:
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_eating_channel;
    };

    class channel_feeder : public ast_node
    {
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_eating_channel;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft> {
    private:
        collective_function_definition& variable_expression;
        feeder m_feeder;
    };
}

#endif