
#ifndef __chips_inoutputs__
#define __chips_inoutputs__
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include <vector>

namespace chips {


    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node
    {
    private:
        std::optional<rvalue<dft,expression_env::PRIMITIVE>> m_default_value;
        dataflow_declaration<dft,statement_env::DEFINITION> m_declaration;
        std::string m_name;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    
    template<dataflow_type dft>
    class collective_parameter : public ast_node
    {
    private:
        rvalue<dft,expression_env::COLLECTIVE> m_default_value;
        dataflow_declaration<dft,statement_env::COLLECTIVE> m_declaration;
        std::string m_name;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class function_output : public ast_node
    {
    private:
        std::string m_name;
        // Note to the model to model transformations developer:
        // Chips 1.1 metamodel didn't cope with multiple 
        // expressions outputs though the grammar allows it... Here, we allow it too
        std::vector<rvalue_variant<expression_env::PRIMITIVE>> m_expressions;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    
    template<enum collective_output_kind>
    class collective_output : public ast_node {};

    class channeled_output : collective_output<collective_output_kind::CHANNELED>
    {
    private:
        node_element_declaration<node_element::CHANNEL>& m_channel;
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class default_output : collective_output<collective_output_kind::DEFAULTED>
    {
    private:
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    

    class target_output : collective_output<collective_output_kind::TARGET>
    {
    private:
        // you should only allow stopless expressions for this member attribute
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_expressions;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

}

#endif