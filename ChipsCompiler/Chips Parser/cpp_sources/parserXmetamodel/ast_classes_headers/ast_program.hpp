#ifndef __chips_program_level__
#define __chips_program_level__
#include "ast_base.hpp"
#include "forward_declarations.hpp"
#include <string>

namespace chips {
    
    class program_node : public ast_node
    {
        std::string m_filename;
        preamble_section_node& m_preamble;
        system_section_node& m_system;

    public:
        program_node(std::string filename, preamble_section_node &preamble, system_section_node &system);
    };


    class preamble_section_node : public ast_node{}; // concrete
    class system_section_node : public ast_node{}; // concrete
}

#endif