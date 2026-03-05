#ifndef OVERALL_DEFINITION_METAMODEL
#define OVERALL_DEFINITION_METAMODEL

#include "chips_ast_classes.hpp"

namespace chips {

    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node{
        private:
            std::unique_ptr<dataflow_primitive_variable> type;
            std::string identifier;
            std::unique_ptr<dataflow_assignment> rhs;

        public:

            function_parameter() = default;

            function_parameter(std::string identifier)
                : identifier(identifier) {}

            std::string get_identifier() { return identifier; }
            static constexpr dataflow_kind get_kind() { return dfk; }
            static constexpr dataflow_type get_type() { return dft; }

            void accept(visitor& visitor) { visitor.visit(*this); } 

            virtual void hello() override;
    };

    //TODO: modifier pas un vector en attribut
    template<dataflow_kind, dataflow_type>
    class function_output : public ast_node{
        private:
            std::vector<function_output_variant> outputs;

        public:
            function_output() = default;

            void append(std::unique_ptr<function_output_variant> output){
                outputs.insert(outputs.begin(), std::move(*output));
            }

            std::vector<function_output_variant> get_outputs() { return outputs; }

            void accept(visitor& visitor) { visitor.visit(*this); } 

            virtual void hello() override;
    };

    class logical_definition : public function_definition {
    private:
        std::string m_identifier;

    public:
        logical_definition(std::string identifier, 
                          std::vector<function_parameter_variant> parameters,
                          std::unique_ptr<init_section> init,
                          std::unique_ptr<then_section> then,
                          std::vector<function_output_variant> outputs)
            : function_definition(std::move(parameters), std::move(outputs), 
                                  std::move(init), std::move(then)),
              m_identifier(std::move(identifier)) {}

        std::string get_identifier() const { return m_identifier; }

        void accept(visitor& visitor) override;
        
        virtual void hello() override;
    };

}

#endif