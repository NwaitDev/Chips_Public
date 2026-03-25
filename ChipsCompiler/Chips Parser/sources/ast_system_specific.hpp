#ifndef __chips_system_spe__
#define __chips_system_spe__


#include <vector>

namespace chips {

    /**
     * Abstract class 
     * Node of the AST modeling an element that produces a dataflow that 
     * can be eaten by another component in system section
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder : public ast_node{};

    /**
     * Interface
     * Node of the AST that represents the reference to the way
     * some node can implement another node. 
     * Will maybe be renamed as "refinement_plan" or something like
     * that in future versions of Chips.
     * Work in progress, do not use.
     */
    class interface{};

    /**
     * Interface
     * Node of the AST that represents the reference to a node that
     * implements another node interface.
     * Will maybe be renamed as "refiner" or something like
     * that in future versions of Chips.
     * Work in progress, do not use.
     */
    class implementer{};

    /**
     * Interface
     * Node of the AST that represents something that
     * can be linked to another Chips Node
     */
    class linkable{};

    /**
     * Interface
     * Node of the AST that represents something that
     * can support another Chips Object
     */
    class support{};

    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can provide a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract : public ast_node {};

    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can consume a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract : public ast_node {};


    /**
     * Abstract class
     * Node of the AST that represents a reference 
     * to a Chips Node (Physical or Object)
     */
    class node_variable_expression : public ast_node{
        void hello() override {std::cout<<"hello"<<std::endl;};
    };


    /**
     * Abstract class
     * Base tamplate class for system component variable elements
     * logical, physical or object
     */
    template<block_type bt>
    class system_variable_block_expression : public ast_node, public system_iterable
    {
        using block_variable_type = typename BlockTypeToBlockVariable<bt>::type;
        block_variable_type& m_variable;
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
    class system_variable_block_expression<block_type::PHYSICAL> : public support, public node_variable_expression, public implementer {};

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing OBJECT specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::OBJECT> 
    : public linkable, public support, public node_variable_expression, public interface, public implementer {};


    /**
     * Concrete class
     * Node of the AST that represents a component that
     * can eat a dataflow produced by something else
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater : public ast_node
    {
        functional_block_variant m_variable_expression;
        function_parameter<dfk,dft>& m_parameter;
    }; 

    

    /**
     * Concrete class
     * Expression that can produce a dataflow eaten by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>, public ast_node
    {
        functional_block_variant m_variable_expression;
        function_output<dfk,dft>& m_output;
    };


    /**
     * Concrete class
     * Node of the AST that represents a channel input
     * of a Chips Node (Physical of Object)
     */
    class channel_eater : public ast_node
    {
        public:
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_eating_channel;
        void hello() override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents a channel output
     * of a Chips Node (Physical of Object)
     */
    class channel_feeder : public ast_node
    {
        public:
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_feeding_channel;
        void hello() override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents dataflow to
     * be spread or collected among many Chips Nodes
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft> {
        collective_function_definition& variable_expression;
        feeder<dfk, dft> m_feeder;
    };
}

#endif