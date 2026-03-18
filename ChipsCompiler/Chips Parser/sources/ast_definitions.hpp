
#ifndef __chips_defintions__
#define __chips_defintions__

#include "forward_declarations.hpp"
#include "ast_base.hpp"
#include "meta_type_conversions.hpp"

// #include "ast_variables.hpp"
// #include "ast_statements.hpp"
// #include "ast_inoutputs.hpp"
// #include "ast_lrxvalues.hpp"

#include <vector>
#include <optional>

namespace chips {

    class definition : public virtual ast_node
    {
    private:
        std::string m_name;

        public:
            definition(std::string name) : m_name(name){}

            std::string get_identifier() { return m_name; }
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
            init_section() = default;

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class then_section : public ast_node
    {
    private:
        std::vector<primitive_statement_variant> m_statements;

        public:
            then_section() = default;

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
        // with_section with;
        std::unique_ptr<with_section> with;
    };

    class object_definition : public node_definition {
        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

    class function_definition : public definition
    {
    private:
        // init_section m_init;
        // then_section m_then;
        std::unique_ptr<init_section> m_init;
        std::unique_ptr<then_section> m_then;
        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;

        public:
            function_definition(std::string identifier, std::vector<function_parameter_variant> parameters, std::unique_ptr<init_section> init,  
                                std::unique_ptr<then_section> then, std::vector<function_output_variant> outputs)
                                : definition(identifier), m_init(std::move(init)), m_then(std::move(then)), m_parameters(parameters), m_outputs(outputs){}

            init_section* get_init() { return m_init.get(); }
            then_section* get_then() { return m_then.get(); }
            const std::vector<function_parameter_variant>& get_parameters() const { return m_parameters; }
            const std::vector<function_output_variant>& get_outputs() const { return m_outputs; }
    };
    class logical_definition : public function_definition{
        public:
            logical_definition(std::string identifier, std::vector<function_parameter_variant> parameters, std::unique_ptr<init_section> init, 
                               std::unique_ptr<then_section> then, std::vector<function_output_variant> outputs)
                               : function_definition(identifier, parameters, std::move(init), std::move(then), outputs){}

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
        // accumulator_definition m_accumulator;
        std::unique_ptr<accumulator_definition> m_accumulator;
        node_definition& m_support_object;
        // collectiveops_section m_operations;
        std::unique_ptr<collectiveops_section> m_operations;
        std::unique_ptr<collective_output<collective_output_kind::TARGET>> m_target_output;
        std::unique_ptr<collective_output<collective_output_kind::DEFAULTED>> m_default_output;
        std::vector<collective_output<collective_output_kind::CHANNELED>> m_channeled_outputs;

        public:

            //void accept(visitor& v) { v.visit(*this); };
            virtual void hello() override;
    };

}

#endif