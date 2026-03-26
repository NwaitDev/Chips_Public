#ifndef __chips_program__
#define __chips_program__

#include <string>
#include <vector>

#include "ast_base.hpp"
#include "meta_type_conversions.hpp"

namespace chips
{

    /**
     * Concrete class
     * Node of the Chips AST that holds all the definitions
     * of Chips components (Logical, Physical and Objects)
     */
    class preamble_section_node : public ast_node
    {
    public:
        std::vector<definition_variant> m_definitions;
        inline void add_definition(definition_variant obj){m_definitions.push_back(obj);};
        void hello();
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds the description
     * of a complete system (an assembly of Chips components)
     */
    class system_section_node : public ast_node
    {
    public:
        std::vector<system_statement_variant> m_system_statements;
        inline void add_system_statement(system_statement_variant obj){m_system_statements.push_back(obj);};
        void hello();// override {std::cout<<"hello"<<std::endl;}
    };

    /**
     * Concrete class
     * Root node for a Chips program in Chips AST
     */
    class program_node : public ast_node
    {
    public:
        std::string m_filename;
        preamble_section_node m_preamble;
        system_section_node m_system;

        void hello();
        preamble_section_node get_preamble(){return m_preamble;} 
        system_section_node get_system(){return m_system;}
    };
}

#endif