
#ifndef __chips_defintions__
#define __chips_defintions__

#include <vector>
#include <optional>

namespace chips
{

    /**
     * Abstract class
     * Node of the AST that represents an element of
     * the preamble section of a Chips program
     */
    class definition : public ast_node
    {
        public:
        std::string m_name;
        definition(std::string id) : m_name(id) {}
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define node specific informations
     * (contextual variables and channels)
     */
    class with_section : public ast_node
    {
        public:
        std::vector<node_statement_variant> m_statements;
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define and initialize a functional 
     * block stateful information (mainly inner variables)
     */
    class init_section : public ast_node
    {
        public:
        std::vector<primitive_statement_variant> m_statements;
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to make a functional block state evolve 
     * according to its current state and its input parameters.
     */
    class then_section : public ast_node
    {
        public:
        std::vector<primitive_statement_variant> m_statements;
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of
     * statements that can be used define how an accumulated 
     * data can be propagated/aggregated among a set of
     * interconnected components
     */
    class collectiveops_section : public ast_node
    {
        public:
        std::vector<collective_statement_variant> m_statements;
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Node of the AST that represents the set of collective parameters
     * that compose the data accumulated by the associate collective
     * primitive.
     */
    class accumulator_definition : public ast_node
    {
        public:
        std::vector<collective_parameter_variant> m_accumulator;
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Abstract class
     * Node of the AST that represents a Chips Node
     * (i.e. an Object or a Physical function)
     */
    class node_definition : public definition
    {
        public:
        with_section with;
    };

    /**
     * Concrete class
     * Node of the AST that represents an Node with no
     * additional features
     * (a location in space that can be connected 
     * to other spaces thank to channels)
     */
    class object_definition : public node_definition
    {
        public:
        void hello();
    };

    /**
     * Abstract class
     * Node of the AST that represents a functional
     * block (i.e. something that has an "init" and a "then" section)
     */
    class function_definition : public definition
    {
        public:
        init_section m_init;
        then_section m_then;
        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;
        function_definition(std::string identifier, std::vector<function_parameter_variant> parameters, init_section init,
                            then_section then, std::vector<function_output_variant> outputs)
            : definition(identifier), m_init(init), m_then(then), m_parameters(parameters), m_outputs(outputs) {}
        
    };
    
    /**
     * Concrete class
     * Node of the AST that represents a functional 
     * block with no additional features
     */
    class logical_definition : public function_definition
    {
        public:
        logical_definition(std::string identifier, std::vector<function_parameter_variant> parameters, init_section init,
                           then_section then, std::vector<function_output_variant> outputs)
            : function_definition(identifier, parameters, init, then, outputs) {}
        
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents a Chips model element
     * that acts both as a Node (a location in space that can be connected 
     * to other spaces thank to channels) and as a Functional block 
     * (i.e. something that has an "init" and a "then" section)
     */
    class physical_definition : public function_definition, public node_definition
    {
        public:
        std::vector<physical_parameter_variant> m_sensor;
        std::vector<physical_output_variant> m_actuator;
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the fact a
     * node can act as another node of the model
     * Maybe to be futurely renamed as "Refinement"
     * Work in progress, do not use
     */
    class implementation_defintion : public definition // do not use, work in progress
    {
        public:
        object_definition& m_implemented_object;
        node_definition& m_implementing_node;
        std::vector<implementation_statement_variant> m_having_statements;
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the definition of a collective
     * primitive, it can be refered to in the system section using the
     * collective_cast node
     */
    class collective_function_definition : public definition
    {
        public:
        collective_function_type m_collective_function_type;
        accumulator_definition m_accumulator;
        node_definition& m_support_object;
        collectiveops_section m_operations;
        target_output m_target_output;
        default_output m_default_output;
        std::vector<channeled_output> m_channeled_outputs;
        void hello();
    };

}

#endif