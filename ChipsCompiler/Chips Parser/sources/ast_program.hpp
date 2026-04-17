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
        void add_definition(definition_variant obj);

        std::vector<definition_variant>& get_definitions();

        void accept(visitor& v) { v.visit(*this); }

        void hello();
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds the description
     * of a complete system (an assembly of Chips components)
     */
    class system_section_node : public ast_node, public statement_fillable<statement_env::SYSTEM>
    {
    public:
        std::vector<system_statement_variant> m_system_statements;
        inline void add_statement(typename SttEnvToSttVariant<statement_env::SYSTEM>::type obj){
            m_system_statements.push_back(obj);
        }

        std::vector<system_statement_variant> get_statements();

        void accept(visitor& v) { v.visit(*this); }
        void hello();
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

        void accept(visitor& v) { v.visit(*this); }

        inline void hello()
        {
            std::cout << m_filename << std::endl;
        }
        preamble_section_node &get_preamble();
        const preamble_section_node &get_preamble() const;
        system_section_node &get_system();
        const system_section_node &get_system() const;
    };
}

#endif