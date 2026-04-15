#ifndef __chips_system_spe__
#define __chips_system_spe__


#include <variant>
#include <vector>
#include "ast_base.hpp"

namespace chips {

    /**
     * Abstract class 
     * Node of the AST modeling an element that produces a dataflow that 
     * can be eaten by another component in system section
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder : public virtual ast_node{};

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
     * Interface
     * Node of the AST that represents something
     * that can be iterated on in the system section
     */
    class system_iterable{};

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
    };


    // /**
    //  * Abstract class
    //  * Base tamplate class for system component variable elements
    //  * logical, physical or object
    //  */
    // template<block_type bt>
    // class system_variable_block_expression : public ast_node, public system_iterable
    // {
        
    // };

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing LOGICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::LOGICAL> : public ast_node, public system_iterable, public linkable{
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::LOGICAL>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            block_variable<block_type::LOGICAL>* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            : m_variable(var), m_index(index){}

        void hello(){}
    };

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing PHYSICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::PHYSICAL> : public system_iterable, public linkable, public support, public node_variable_expression, public implementer {
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::PHYSICAL>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            block_variable_type* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            : m_variable(var), m_index(index){}

        void hello(){}
    };

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing OBJECT specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::OBJECT> 
    : public system_iterable, public linkable, public support, public node_variable_expression, public interface, public implementer {
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::OBJECT>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            block_variable<block_type::OBJECT>* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            : m_variable(var), m_index(index){}

        void hello(){}
    };


    /**
     * Concrete class
     * Node of the AST that represents a component that
     * can eat a dataflow produced by something else
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater : public ast_node
    {
        public:
        functional_block_variant m_variable_expression;
        function_parameter<dfk,dft>* m_parameter;

        eater(functional_block_variant variable, function_parameter<dfk,dft>* parameter)
            : m_variable_expression(variable), m_parameter(parameter){}

        inline void hello(){}
    }; 

    

    /**
     * Concrete class
     * Expression that can produce a dataflow eaten by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>
    {
        public:
        functional_block_variant m_variable_expression;
        function_output<dfk,dft>* m_output;
        
        feeder_block_expression(){}
        feeder_block_expression(functional_block_variant variable, function_output<dfk,dft>* output)
            : m_variable_expression(variable), m_output(output){}
        
        void set_variable_expression(functional_block_variant variable){
            m_variable_expression = variable;
        }

        void set_output(function_output<dfk,dft>* output){
            m_output = output;
        }

        inline void hello(){}
    };


    /**
     * Concrete class
     * Node of the AST that represents a channel input
     * of a Chips Node (Physical of Object)
     */
    class channel_eater : public ast_node
    {
        public:
        node_variable_expression* m_node;
        node_element_declaration<node_element::CHANNEL>* m_eating_channel;

        channel_eater(node_variable_expression* node, node_element_declaration<node_element::CHANNEL>* eating_channel)
            : m_node(node), m_eating_channel(eating_channel){}

        void hello() {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents a channel output
     * of a Chips Node (Physical of Object)
     */
    class channel_feeder : public ast_node
    {
        public:
        node_variable_expression* m_node;
        node_element_declaration<node_element::CHANNEL>* m_feeding_channel;

        channel_feeder(node_variable_expression* node, 
                       node_element_declaration<node_element::CHANNEL>* feeding_channel)
            : m_node(node), m_feeding_channel(feeding_channel){}

        void hello() override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents dataflow to
     * be spread or collected among many Chips Nodes
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft> {
        public:
        collective_function_definition* variable_expression;
        using feeder_variant = std::variant<
            feeder<dfk, dataflow_type::INT>*,
            feeder<dfk, dataflow_type::FLOAT>*,
            feeder<dfk, dataflow_type::BOOL>*
        >;

        feeder_variant m_feeder;

        explicit collective_cast(collective_function_definition* variable, feeder<dfk, dataflow_type::INT>& feed)
            : variable_expression(variable), m_feeder(&feed){}

        explicit collective_cast(collective_function_definition* variable, feeder<dfk, dataflow_type::FLOAT>& feed)
            : variable_expression(variable), m_feeder(&feed){}

        explicit collective_cast(collective_function_definition* variable, feeder<dfk, dataflow_type::BOOL>& feed)
            : variable_expression(variable), m_feeder(&feed){}

        template<dataflow_type feeder_dft>
        feeder<dfk, feeder_dft>* get_feeder_as(){
            if(auto* casted = std::get_if<feeder<dfk, feeder_dft>*>(&m_feeder)){
                return *casted;
            }
            return nullptr;
        }

        void hello(){}
    };
}

#endif