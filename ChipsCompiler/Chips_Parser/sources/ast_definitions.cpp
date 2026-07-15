#include "ast_definitions.hpp"

namespace chips {

    void logical_definition::hello(){
        std::cout << "logical " << m_name << "(";
        std::cout << (m_parameters.empty() ? "vide" : "rempli") << std::endl;
        std::cout << ")" << std::endl;
        m_init.hello();
        m_then.hello();
        std::cout << "outputs " << (m_outputs.empty() ? "vide" : "rempli") << std::endl;
    }

    void physical_definition::hello(){}

    void implementation_defintion::hello(){}

    void collective_function_definition::hello(){}
    
    void with_section::hello(){}

    void init_section::hello(){}

    void then_section::hello(){}
    
    void collectiveops_section::hello(){}
    
    void accumulator_definition::hello(){}

    void object_definition::hello(){}
    
}