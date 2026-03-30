
#ifndef __chips_inoutputs__
#define __chips_inoutputs__

#include "ast_variables.hpp"
#include <vector>
#include <optional>

namespace chips {


    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * functional block definition.
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node
    {
    public:
        std::optional<rvalue<dft,expression_env::PRIMITIVE>> m_default_value;
        dataflow_declaration<dft,statement_env::DEFINITION> m_declaration;
        std::string m_name;

        function_parameter(std::string name, dataflow_declaration<dft,statement_env::DEFINITION> declaration, std::optional<rvalue<dft,expression_env::PRIMITIVE>> default_value)
        : m_name(name), m_declaration(declaration), m_default_value(default_value){};
        function_parameter(std::string name, dataflow_declaration<dft,statement_env::DEFINITION> declaration)
        : m_name(name), m_declaration(declaration), m_default_value(std::nullopt){};
        
        void hello(){
            std::cout << "FUNCTION PARAMETER" << std::endl;
        };
    };
    
    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * collective primitive definition.
     */
    template<dataflow_type dft>
    class collective_parameter : public ast_node
    {
        rvalue<dft,expression_env::COLLECTIVE> m_default_value;
        dataflow_declaration<dft,statement_env::COLLECTIVE> m_declaration;
        std::string m_name;
        void hello(){};
    };

    /**
     * Concrete class
     * Node of the AST that represents one output 
     * of a functional block.
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class function_output : public ast_node
    {
        public:
        std::string m_name;
        // Note to the model to model transformations developer:
        // Chips 1.1 metamodel didn't cope with multiple 
        // expressions outputs though the grammar allows it... Here, we allow it too
        std::vector<rvalue_variant<expression_env::PRIMITIVE>> m_expressions;
        function_output(std::string name,rvalue<dft,expression_env::PRIMITIVE>* expr) : m_name(name){ m_expressions.push_back(expr);};
        inline void add_expression(rvalue_variant<expression_env::PRIMITIVE> exp) { m_expressions.push_back(exp);} 
        void hello(){};
    };
    
    /**
     * Abstract class
     * Node of the AST that represents one output 
     * of a collective primitive defintion.
     */
    template<enum collective_output_kind>
    class collective_output : public ast_node {};

    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive associated channel
     */
    class channeled_output : collective_output<collective_output_kind::CHANNELED>
    {
        node_element_declaration<node_element::CHANNEL>* m_channel;
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;
        void hello();
    };

    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive that has no associated channel
     */
    class default_output : collective_output<collective_output_kind::DEFAULTED>
    {
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;
        void hello();
    };
    

    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive associated to the parameter
     * of the functional block that is hosting the partial 
     * collective primitive. 
     */
    class target_output : collective_output<collective_output_kind::TARGET>
    {
        // you should only allow stopless expressions for this member attribute
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_expressions;
        void hello();
    };

}

#endif