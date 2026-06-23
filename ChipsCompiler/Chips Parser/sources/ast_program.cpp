#include "ast_program.hpp"
#include "ast_definitions.hpp"

namespace chips
{

    void preamble_section_node::add_definition(definition_variant dv)
    {
        std::cout << "ADD DEFINITION: " << m_definitions.size() << std::endl;
        m_definitions.push_back(dv);
        std::cout << "ADD DEFINITION: " << m_definitions.size() << std::endl;
    }

    std::vector<definition_variant>& preamble_section_node::get_definitions() { return m_definitions; }

    void preamble_section_node::hello()
    {
        for (auto &def : this->m_definitions)
        {

#define TRY_DEF_CAST_HELLO(DEF)               \
    try                                       \
    {                                         \
        std::get<DEF *>(def)->hello();        \
    }                                         \
    catch (const std::bad_variant_access &ex) \
    {                                         \
        std::cout << ex.what() << std::endl;  \
    }

            TRY_DEF_CAST_HELLO(object_definition)
            TRY_DEF_CAST_HELLO(logical_definition)
            TRY_DEF_CAST_HELLO(physical_definition)
            TRY_DEF_CAST_HELLO(implementation_defintion)
            TRY_DEF_CAST_HELLO(collective_function_definition)

#undef TRY_DEF_CAST_HELLO
        }
    }

    std::vector<system_statement_variant> system_section_node::get_statements() { return m_system_statements; }
    void system_section_node::hello() { std::cout << "system " << (this->m_system_statements.empty() ? "vide" : "rempli") << std::endl; }

    preamble_section_node &program_node::get_preamble() { return m_preamble; }
    const preamble_section_node &program_node::get_preamble() const { return m_preamble; }
    system_section_node &program_node::get_system() { return m_system; }
    const system_section_node &program_node::get_system() const { return m_system; }
}