#ifndef __chips_program__
#define __chips_program__
#include "ast_base.hpp"
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include <string>
#include <vector>

namespace chips {
    
    class program_node : public ast_node
    {
        std::string m_filename;
        preamble_section_node& m_preamble;
        system_section_node& m_system;

    public:
        program_node(std::string filename, preamble_section_node &preamble, system_section_node &system);
    };


    class preamble_section_node : public ast_node{
        private:
        std::vector<definition_variant> m_definitions;
    };
    class system_section_node : public ast_node{
        private:
        std::vector<system_statement_variant> m_system_statements;
    };
}

#endif