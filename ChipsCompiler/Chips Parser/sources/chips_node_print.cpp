#include "chips_headers.hpp"
#include <iostream>

#include <typeinfo>
#include "cxxabi.h"

namespace chips {
    std::string dft_to_string(dataflow_type type){
        switch(type){
            case dataflow_type::INT: return "int";
            case dataflow_type::FLOAT: return "float";
            case dataflow_type::BOOL: return "bool";
        }
    }

    void program_node::hello(){
        std::cout << m_filename << std::endl;
        // if(get_preamble()){
        //     get_preamble()->hello();
        // }
        // if(get_system()){
        //     get_system()->hello();
        // }
    }

    void preamble_section_node::hello(){
        for(auto& def : this->m_definitions){

            #define TRY_DEF_CAST_HELLO(DEF)                         \
            try{                                                    \
                std::any_cast<DEF*>(std::get<DEF*>(def))->hello();  \
            } catch (const std::bad_variant_access& ex){            \
                std::cout<<ex.what()<<std::endl;                    \
            } catch (const std::bad_any_cast ex){                   \
                std::cout<<ex.what()<<std::endl;                    \
            }
            
            TRY_DEF_CAST_HELLO(object_definition)
            TRY_DEF_CAST_HELLO(logical_definition)
            TRY_DEF_CAST_HELLO(physical_definition)
            TRY_DEF_CAST_HELLO(implementation_defintion)
            TRY_DEF_CAST_HELLO(collective_function_definition)

            #undef TRY_DEF_CAST_HELLO
        }
    }

    void system_section_node::hello(){
        std::cout << "system " << (this->m_system_statements.empty() ? "vide" : "rempli") << std::endl;
    //     for(auto& statement : get_statements()){
    //         // std::visit([](auto* s){ s->hello(); }, statement);
    //     }
    }

    template<expression_env expenv>
    void array<expenv>::hello(){
        for(auto dim : get_dimensions()){
            std::cout << "[";
            std::cout << "TODO";
            // dim.hello();
            std::cout << "]";
        }
    }

    template<dataflow_type dft>
    void dataflow_primitive_variable<dft>::hello(){
        std::cout << dft_to_string(dft);
        array<expression_env::PRIMITIVE>::hello();
        std::cout << " " << get_name() << ";" << std::endl;
    }

    template<dataflow_type dft>
    void contextual_variable<dft>::hello(){}

    template<dataflow_type dft>
    void dataflow_collective_variable<dft>::hello(){}

    template<block_type bt>
    void block_variable<bt>::hello(){}

    template<dataflow_type dft>
    void dataflow_system_variable<dft>::hello(){}

    template<dataflow_type dft, statement_env sttenv>
    void dataflow_declaration<dft, sttenv>::hello(){
        get_variable().hello();
    }

    template<dataflow_type dft, statement_env sttenv>
    void dataflow_assignment<dft, sttenv>::hello(){
        std::cout << "DATAFLOW ASSIGNMENT" << std::endl;

        int status;
        const std::type_info& ti = typeid(get_lhs());
        char* realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
        std::cout << "Type dynamique de get_lhs() : " << (realname ? realname : ti.name()) << std::endl;
        free(realname);

        //TODO régler ce PUTAIN DE CORE DUMPED

        // std::cout << (get_lhs() ? "yes" : "no") << std::endl;
        get_lhs()->hello();
        std::cout << " = ";
        get_rhs().hello();
        std::cout << ";" << std::endl;
    }

    template<statement_env sttenv>
    void if_section<sttenv>::hello(){}

    template<statement_env sttenv>
    void else_section<sttenv>::hello(){}

    template<statement_env sttenv>
    void if_statement<sttenv>::hello(){}

    template<statement_env sttenv>
    void if_else_statement<sttenv>::hello(){}

    template<statement_env sttenv, dataflow_type dft>
    void foreach_statement<sttenv, dft>::hello(){}

    template<block_type bt>
    void block_foreach_statement<bt>::hello(){}

    template<block_type bt>
    void block_declaration<bt>::hello(){}

    void implements_statement::hello(){}

    void channel_plugging::hello(){}

    template<dataflow_kind dfk, dataflow_type dft>
    void feeding_statement<dfk, dft>::hello(){}

    void linking_statement::hello(){}

    template<node_element ne>
    void aliasing_statement<ne>::hello(){}

    template<node_element ne>
    void node_element_declaration<ne>::hello(){}

    template<dataflow_kind dfk, dataflow_type dft>
    void function_parameter<dfk, dft>::hello(){
        std::cout << "FUNCTION PARAMETER" << std::endl;
    }

    template<dataflow_type dft>
    void collective_parameter<dft>::hello(){}

    template<dataflow_kind dfk, dataflow_type dft>
    void function_output<dfk, dft>::hello(){}

    void default_output::hello(){}

    void target_output::hello(){}

    void channeled_output::hello(){}

    void with_section::hello(){}

    void init_section::hello(){
    // std::cout << "nombre stts init = " << get_statements().size() << std::endl;
    //     for(auto& statement : get_statements()){
    //         std::visit([](auto* s){ s->hello(); }, statement);
    //     }
    }

    void then_section::hello(){
    //     // std::cout << "nombre stts then = " << get_statements().size() << std::endl;
    //     for(auto& statement : get_statements()){
    //         std::visit([](auto* s){ s->hello(); }, statement);
    //     }
    }

    void collectiveops_section::hello(){}

    void accumulator_definition::hello(){}

    void object_definition::hello(){}

    void logical_definition::hello(){
        std::cout << "logical " << m_name << "(";
        std::cout << (m_parameters.empty() ? "vide" : "rempli") << std::endl;
        std::cout << ")" << std::endl;
        m_init.hello();
        m_then.hello();
        std::cout << "outputs " << (m_outputs.empty() ? "vide" : "rempli") << std::endl;
    }

    void physical_definition::hello(){}

    void implementation_defintion::hello(){}

    void collective_function_definition::hello(){}

    template<dataflow_type dft, expression_env expenv>
    void direct<dft, expenv>::hello(){
        if constexpr (dft == dataflow_type::FLOAT) {
            printf("%f", m_value);
        }else if constexpr(dft == dataflow_type::BOOL){ 
            std::cout << (m_value ? "true" : "false");
        }else {
            std::cout << m_value;
        }
    }

    template<dataflow_type dft, expression_env expenv>
    void function<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";

        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft, expression_env expenv>
    void plus<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " + ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft, expression_env expenv>
    void minus<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " - ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft, expression_env expenv>
    void uminus_operator<dft,expenv>::hello(){
        std::cout << " -";
        if(get_rhs()) get_rhs()->hello();
    }

    template<dataflow_type dft, expression_env expenv>
    void mult<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " * ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft, expression_env expenv>
    void div<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " / ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv>
    void mod<expenv>::hello(){
        if(get_lhs()) get_lhs()->hello();
        std::cout << " % ";
        if(get_rhs()) get_rhs()->hello();
    }

    template<dataflow_type dft, expression_env expenv>
    void cast_as<dft, expenv>::hello(){
        if(get_cast()){
            std::cout << "(";
            // std::cout << "cast";
            if constexpr(dft == dataflow_type::INT){
                std::cout << "int";
            }else if constexpr(dft == dataflow_type::FLOAT){
                std::cout << "float";
            }else if constexpr(dft == dataflow_type::BOOL){
                std::cout << "bool";
            }
            std::cout << ")";
            get_cast()->hello();
        }
    }

    template<expression_env expenv, dataflow_type dft>
    void gt<expenv, dft>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " > ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv, dataflow_type dft>
    void lt<expenv, dft>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " < ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv, dataflow_type dft>
    void leq<expenv, dft>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " <= ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv, dataflow_type dft>
    void geq<expenv, dft>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " >= ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv>
    void or_operator<expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " || ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv>
    void and_operator<expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " && ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<expression_env expenv>
    void not_operator<expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        std::cout << "!";
        if(get_lhs()) get_lhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft,expression_env expenv>
    void eq<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
        if(get_lhs()) get_lhs()->hello();
        std::cout << " == ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft,expression_env expenv>
    void neq<dft, expenv>::hello(){
        // if(this->is_parenthesage()) std::cout << "(";
         if(get_lhs()) get_lhs()->hello();
        std::cout << " != ";
        if(get_rhs()) get_rhs()->hello();
        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft,expression_env expenv>
    void variable_expression<dft, expenv>::hello(){
        std::cout << "VARIABLE EXPRESSION" << std::endl;
        get_variable()->hello();
    }

    template<dataflow_type dft, expression_env expenv>
    void variable_contextual_expression<dft, expenv>::hello(){}

    // ------------------------------------------------------
    // UNCOMMENT THE FOLLOWING WHEN THE REST OF 
    // THE DATA STRUCTURE IS ROBUST AND FUNCTIONAL

    // template<dataflow_kind dfk, dataflow_type dft>
    // void eater<dfk, dft>::hello(){}

    // template<dataflow_kind dfk, dataflow_type dft>
    // void feeder_block_expression<dfk, dft>::hello(){}

    // void channel_eater::hello(){}

    // void channel_feeder::hello(){}

    // template<dataflow_kind dfk, dataflow_type dft>
    // void collective_cast<dfk, dft>::hello(){}
    // ------------------------------------------------------

}

// ── Explicit template instantiations ──────────────────────────────────────────
// Nécessaire pour que les unités de compilation qui n'incluent pas chips_node_print.cpp
// puissent trouver les symboles des spécialisations utilisées (ex: main.cpp).
namespace chips {
    template void direct<dataflow_type::INT,   expression_env::PRIMITIVE>::hello();
    template void direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void direct<dataflow_type::BOOL,  expression_env::PRIMITIVE>::hello();
    template void direct<dataflow_type::INT,   expression_env::COLLECTIVE>::hello();
    template void direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void direct<dataflow_type::BOOL,  expression_env::COLLECTIVE>::hello();
    template void direct<dataflow_type::INT,   expression_env::SYSTEM>::hello();
    template void direct<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();
    template void direct<dataflow_type::BOOL,  expression_env::SYSTEM>::hello();

    template void plus<dataflow_type::INT,   expression_env::PRIMITIVE>::hello();
    template void plus<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void plus<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void plus<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void plus<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void plus<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void minus<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void minus<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void minus<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void minus<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void minus<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void minus<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void uminus_operator<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void uminus_operator<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void uminus_operator<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void uminus_operator<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void uminus_operator<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void uminus_operator<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void mult<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void mult<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void mult<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void mult<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void mult<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void mult<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void div<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void div<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void div<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void div<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void div<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void div<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void mod<expression_env::PRIMITIVE>::hello();
    template void mod<expression_env::COLLECTIVE>::hello();
    template void mod<expression_env::SYSTEM>::hello();

    template void lt<expression_env::PRIMITIVE, dataflow_type::INT>::hello();
    template void lt<expression_env::PRIMITIVE, dataflow_type::FLOAT>::hello();
    template void lt<expression_env::COLLECTIVE, dataflow_type::INT>::hello();
    template void lt<expression_env::COLLECTIVE, dataflow_type::FLOAT>::hello();
    template void lt<expression_env::SYSTEM, dataflow_type::INT>::hello();
    template void lt<expression_env::SYSTEM, dataflow_type::FLOAT>::hello();

    template void leq<expression_env::PRIMITIVE, dataflow_type::INT>::hello();
    template void leq<expression_env::PRIMITIVE, dataflow_type::FLOAT>::hello();
    template void leq<expression_env::COLLECTIVE, dataflow_type::INT>::hello();
    template void leq<expression_env::COLLECTIVE, dataflow_type::FLOAT>::hello();
    template void leq<expression_env::SYSTEM, dataflow_type::INT>::hello();
    template void leq<expression_env::SYSTEM, dataflow_type::FLOAT>::hello();

    template void gt<expression_env::PRIMITIVE, dataflow_type::INT>::hello();
    template void gt<expression_env::PRIMITIVE, dataflow_type::FLOAT>::hello();
    template void gt<expression_env::COLLECTIVE, dataflow_type::INT>::hello();
    template void gt<expression_env::COLLECTIVE, dataflow_type::FLOAT>::hello();
    template void gt<expression_env::SYSTEM, dataflow_type::INT>::hello();
    template void gt<expression_env::SYSTEM, dataflow_type::FLOAT>::hello();

    template void geq<expression_env::PRIMITIVE, dataflow_type::INT>::hello();
    template void geq<expression_env::PRIMITIVE, dataflow_type::FLOAT>::hello();
    template void geq<expression_env::COLLECTIVE, dataflow_type::INT>::hello();
    template void geq<expression_env::COLLECTIVE, dataflow_type::FLOAT>::hello();
    template void geq<expression_env::SYSTEM, dataflow_type::INT>::hello();
    template void geq<expression_env::SYSTEM, dataflow_type::FLOAT>::hello();

    template void eq<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void eq<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void eq<dataflow_type::BOOL, expression_env::PRIMITIVE>::hello();
    template void eq<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void eq<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void eq<dataflow_type::BOOL, expression_env::COLLECTIVE>::hello();
    template void eq<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void eq<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();
    template void eq<dataflow_type::BOOL, expression_env::SYSTEM>::hello();

    template void neq<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void neq<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void neq<dataflow_type::BOOL, expression_env::PRIMITIVE>::hello();
    template void neq<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void neq<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void neq<dataflow_type::BOOL, expression_env::COLLECTIVE>::hello();
    template void neq<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();
    template void neq<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void neq<dataflow_type::BOOL, expression_env::SYSTEM>::hello();

    template void and_operator<expression_env::PRIMITIVE>::hello();
    template void and_operator<expression_env::COLLECTIVE>::hello();
    template void and_operator<expression_env::SYSTEM>::hello();

    template void or_operator<expression_env::PRIMITIVE>::hello();
    template void or_operator<expression_env::COLLECTIVE>::hello();
    template void or_operator<expression_env::SYSTEM>::hello();

    template void not_operator<expression_env::PRIMITIVE>::hello();
    template void not_operator<expression_env::COLLECTIVE>::hello();
    template void not_operator<expression_env::SYSTEM>::hello();

    template void cast_as<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void cast_as<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void cast_as<dataflow_type::INT, expression_env::COLLECTIVE>::hello();
    template void cast_as<dataflow_type::FLOAT, expression_env::COLLECTIVE>::hello();
    template void cast_as<dataflow_type::INT, expression_env::SYSTEM>::hello();
    template void cast_as<dataflow_type::FLOAT, expression_env::SYSTEM>::hello();

    template void variable_expression<dataflow_type::INT, expression_env::PRIMITIVE>::hello();
    template void variable_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE>::hello();
    template void variable_expression<dataflow_type::BOOL, expression_env::PRIMITIVE>::hello();

    template void dataflow_primitive_variable<dataflow_type::INT>::hello();
    template void dataflow_primitive_variable<dataflow_type::FLOAT>::hello();
    template void dataflow_primitive_variable<dataflow_type::BOOL>::hello();

    template void array<expression_env::PRIMITIVE>::hello();
    template void array<expression_env::COLLECTIVE>::hello();
    template void array<expression_env::SYSTEM>::hello();

    template void dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>::hello();
    template void dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>::hello();
    template void dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>::hello();

    template void dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>::hello();
    template void dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>::hello();
    template void dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>::hello();

    template void function_parameter<dataflow_kind::LOGICAL,dataflow_type::BOOL>::hello();
    template void function_parameter<dataflow_kind::LOGICAL,dataflow_type::FLOAT>::hello();
    template void function_parameter<dataflow_kind::LOGICAL,dataflow_type::INT>::hello();
    template void function_parameter<dataflow_kind::PHYSICAL,dataflow_type::BOOL>::hello();
    template void function_parameter<dataflow_kind::PHYSICAL,dataflow_type::FLOAT>::hello();
    template void function_parameter<dataflow_kind::PHYSICAL,dataflow_type::INT>::hello();

    template void function_output<dataflow_kind::LOGICAL,dataflow_type::BOOL>::hello();
    template void function_output<dataflow_kind::LOGICAL,dataflow_type::FLOAT>::hello();
    template void function_output<dataflow_kind::LOGICAL,dataflow_type::INT>::hello();
    template void function_output<dataflow_kind::PHYSICAL,dataflow_type::BOOL>::hello();
    template void function_output<dataflow_kind::PHYSICAL,dataflow_type::FLOAT>::hello();
    template void function_output<dataflow_kind::PHYSICAL,dataflow_type::INT>::hello();

    template void node_element_declaration<node_element::CHANNEL>::hello();
    template void node_element_declaration<node_element::CONTEXTUAL_INT>::hello();
    template void node_element_declaration<node_element::CONTEXTUAL_FLOAT>::hello();
    template void node_element_declaration<node_element::CONTEXTUAL_BOOL>::hello();

    template void contextual_variable<chips::dataflow_type::INT>::hello();
    template void contextual_variable<chips::dataflow_type::FLOAT>::hello();
    template void contextual_variable<chips::dataflow_type::BOOL>::hello();

    template void if_else_statement<statement_env::NODE>::hello();
    template void if_statement<statement_env::NODE>::hello();
    template void else_section<statement_env::NODE>::hello();
    template void if_section<statement_env::NODE>::hello();

    template void foreach_statement<statement_env::NODE,dataflow_type::INT>::hello();
    template void foreach_statement<statement_env::NODE,dataflow_type::FLOAT>::hello();
    template void foreach_statement<statement_env::NODE,dataflow_type::BOOL>::hello();
    template void dataflow_declaration<dataflow_type::INT,statement_env::NODE>::hello();
    template void dataflow_declaration<dataflow_type::FLOAT,statement_env::NODE>::hello();
    template void dataflow_declaration<dataflow_type::BOOL,statement_env::NODE>::hello();
    template void dataflow_assignment<dataflow_type::INT,statement_env::NODE>::hello();
    template void dataflow_assignment<dataflow_type::FLOAT,statement_env::NODE>::hello();
    template void dataflow_assignment<dataflow_type::BOOL,statement_env::NODE>::hello();
    
}