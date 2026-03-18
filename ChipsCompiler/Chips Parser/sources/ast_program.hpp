#ifndef __chips_program__
#define __chips_program__
// #include "ast_base.hpp"
// #include "forward_declarations.hpp"
// #include "meta_type_conversions.hpp"
#include <string>
#include <vector>

#include "forward_declarations.hpp"
#include "ast_base.hpp"
#include "meta_type_conversions.hpp"
#include "ast_definitions.hpp"

//TODO: revoir tous les includes

namespace chips {
    
    class program_node : public ast_node
    {
        private:
        std::string m_filename;
        std::unique_ptr<preamble_section_node> m_preamble;
        std::unique_ptr<system_section_node> m_system;
        // preamble_section_node& m_preamble;
        // system_section_node& m_system;

    public:
        program_node(std::string filename, std::unique_ptr<preamble_section_node> preamble, std::unique_ptr<system_section_node> system)
            : m_filename(filename), m_preamble(std::move(preamble)), m_system(std::move(system)){}

        std::string get_filename() { return m_filename; }
        preamble_section_node* get_preamble() { return m_preamble.get(); }
        system_section_node* get_system() { return m_system.get(); }

        //void accept(visitor& v) { v.visit(*this); }
        virtual void hello() override;
    };


    class preamble_section_node : public ast_node{
        private:
            std::vector<definition_variant> m_definitions;
            std::vector<std::unique_ptr<definition>> m_storage; // Garantir la durée de vie d'un objet

            definition_variant make_variant(definition* def){
                if (auto p = dynamic_cast<object_definition*>(def)) return p;
                if (auto p = dynamic_cast<logical_definition*>(def)) return p;
                if (auto p = dynamic_cast<physical_definition*>(def)) return p;
                if (auto p = dynamic_cast<implementation_defintion*>(def)) return p;
                if (auto p = dynamic_cast<collective_function_definition*>(def)) return p;

                throw std::runtime_error("Unknown definition type");
            }

        public:
            preamble_section_node() = default;

            const std::vector<definition_variant>& get_definitions() const { return m_definitions; }

            void append(std::unique_ptr<definition> def){
                definition* ptr = def.get();
                m_storage.push_back(std::move(def));
                m_definitions.insert(m_definitions.begin(), make_variant(ptr));
            }

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    class system_section_node : public ast_node{
        private:
        std::vector<system_statement_variant> m_system_statements;

        public:
            system_section_node() = default;

            const std::vector<system_statement_variant>& get_statements() const { return m_system_statements; }

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
}

#endif