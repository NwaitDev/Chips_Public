#ifndef OVERALL_DEFINITION_METAMODEL
#define OVERALL_DEFINITION_METAMODEL

#include "chips_ast_classes.hpp"

namespace chips {

    class definition : public ast_node {
        private:
            std::string m_name;
        
        public:
            definition(const std::string name) : m_name(name) {}

            const std::string get_identifier() const { return m_name; }
    };

    class function_definition : public definition {
        private:
            std::unique_ptr<init_section> m_init;
            std::unique_ptr<then_section> m_then;
            std::vector<function_parameter_variant> m_parameters;
            std::vector<function_output_variant> m_outputs;

        public:
            function_definition(const std::string identifier, std::vector<function_parameter_variant> parameters,
                                std::unique_ptr<init_section> init, std::unique_ptr<then_section> then, std::vector<function_output_variant> outputs)
                                : definition(identifier), m_parameters(std::move(parameters)), m_init(std::move(init)), m_then(std::move(then)),
                                  m_outputs(std::move(outputs)) {}


            const std::vector<function_parameter_variant>& get_parameters() const { return m_parameters; }
            const std::vector<function_output_variant>& get_outputs() const { return m_outputs; }
            init_section* get_init() const { return m_init.get(); }
            then_section* get_then() const { return m_then.get(); }
    };

    // class with_section : public ast_node {
    //     private:
    //         std::vector<node_statement_variant> m_statements;

    //     public:
    //         with_section() = default;
    // };

    // class node_definition : public definition {
    //     private:
    //         std::unique_ptr<with_section> with;

    //     public:
    //         node_definition() = default;
    // };

    class init_section : public ast_node{
        private:
            std::vector<primitive_statement_variant> m_statements;

        public:
            init_section() = default;

            init_section(std::vector<primitive_statement_variant> statements)
                : m_statements(std::move(statements)){}

            void append(primitive_statement_variant statement){
                m_statements.insert(m_statements.begin(), statement);
            }

            const std::vector<primitive_statement_variant>& get_statements() const { return m_statements; }

            void accept(visitor& v) override;
            virtual void hello() override;
    };

    class then_section : public ast_node{
        private:
            std::vector<primitive_statement_variant> m_statements;

        public:
            then_section() = default;

            then_section(std::vector<primitive_statement_variant> statements)
                : m_statements(std::move(statements)){}

            void append(primitive_statement_variant statement){
                m_statements.insert(m_statements.begin(), statement);
            }

            const std::vector<primitive_statement_variant>& get_statements() const { return m_statements; }

            void accept(visitor& v) override;
            virtual void hello() override;
    };

    //TODO
    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node{
        private:
            

        public:

            function_parameter() = default;

            void accept(visitor& visitor) { visitor.visit(*this); } 

            virtual void hello() override;
    };

    //TODO
    template<dataflow_kind, dataflow_type>
    class function_output : public ast_node{
        public:
            function_output() = default;

            void accept(visitor& visitor) { visitor.visit(*this); } 

            virtual void hello() override;
    };

    class logical_definition : public function_definition {
    public:
        logical_definition(std::string identifier, 
                          std::vector<function_parameter_variant> parameters,
                          std::unique_ptr<init_section> init,
                          std::unique_ptr<then_section> then,
                          std::vector<function_output_variant> outputs)
            : function_definition(identifier, std::move(parameters), std::move(init), std::move(then), std::move(outputs)) {}

        void accept(visitor& visitor) override;
        
        virtual void hello() override;
    };

    // class physical_definition : public function_definition, public node_definition {
    //     private:
    //         std::vector<physical_parameter_variant> m_sensor;
    //         std::vector<physical_output_variant> m_actuator;

    //     public:
    //         physical_definition() = default;
    // };

}

#endif