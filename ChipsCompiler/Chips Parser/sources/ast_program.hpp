#ifndef __chips_program__
#define __chips_program__

#include <string>
#include <vector>


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
        void hello();// override {std::cout<<"hello"<<std::endl;}
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

        void hello();// override { std::cout << "hello from program_node" << std::endl; }
    };
}

#endif