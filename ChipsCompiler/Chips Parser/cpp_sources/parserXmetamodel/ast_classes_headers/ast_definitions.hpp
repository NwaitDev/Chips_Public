
#ifndef __chips_defintions__
#define __chips_defintions__
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include <vector>
#include <optional>

namespace chips {

    class definition : public ast_node
    {
    private:
        std::string m_name;
    };


    class with_section : public ast_node
    {
    private:
        std::vector<node_statement_variant> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };
    
    class init_section : public ast_node
    {
    private:
        std::vector<primitive_statement_variant> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class then_section : public ast_node
    {
    private:
        std::vector<primitive_statement_variant> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class collectiveops_section : public ast_node
    {
    private:
        std::vector<collective_statement_variant> m_statements;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class accumulator_definition : public ast_node
    {
    private:
        std::vector<collective_parameter_variant> m_accumulator;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class node_definition : public definition
    {
    private:
        with_section with;
    };

    class object_definition : public node_definition {
        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class function_definition : public definition
    {
    private:
        init_section init;
        then_section then;
        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;
    };
    class logical_definition : public function_definition{
        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class physical_definition : public function_definition, public node_definition
    {
    private:
        std::vector<physical_parameter_variant> m_sensor;
        std::vector<physical_output_variant> m_actuator;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };
    
    class implementation_defintion : public definition // do not use, work in progress
    {
    private:
        object_definition& m_implemented_object;
        node_definition& m_implementing_node;
        std::vector<implementation_statement_variant> m_having_statements;

        public:

            // void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class collective_function_definition : public definition
    {
    private:
        collective_function_type m_collective_function_type;
        accumulator_definition m_accumulator;
        node_definition& m_support_object;
        collectiveops_section m_operations;
        std::unique_ptr<collective_output<collective_output_kind::TARGET>> m_target_output;
        std::unique_ptr<collective_output<collective_output_kind::DEFAULTED>> m_default_output;
        std::vector<collective_output<collective_output_kind::CHANNELED>> m_channeled_outputs;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

}

#endif