#include "ast_base.hpp"
#include "ast_definitions.hpp"
#include "ast_inoutputs.hpp"
#include "ast_lrxvalues.hpp"
#include "ast_program.hpp"
#include "ast_statements.hpp"
#include "ast_system_specific.hpp"
#include "ast_variables.hpp"


#include <iostream>

#include <typeinfo>

namespace chips {
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
        // std::cout << "preambles " << (get_definitions().empty() ? "vide" : "rempli") << std::endl;
        for(auto& def : get_definitions()){
            std::visit([](auto* d){ 
                if(d){
                    d->hello();
                }
            }, def);
        }
    }

    void system_section_node::hello(){
        std::cout << "system " << (get_statements().empty() ? "vide" : "rempli") << std::endl;
    //     for(auto& statement : get_statements()){
    //         // std::visit([](auto* s){ s->hello(); }, statement);
    //     }
    }

    template<expression_env expenv>
    void array<expenv>::hello(){}

    template<dataflow_type dft>
    void dataflow_primitive_variable<dft>::hello(){
        std::cout << "DATAFLOW PRIMITIVE VARIABLE " << std::endl;
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
        std::cout << "DATAFLOW DECLARATION" << std::endl;
    }

    template<dataflow_type dft, statement_env sttenv>
    void dataflow_assignment<dft, sttenv>::hello(){}

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
        std::cout << "logical " << get_identifier() << "(";
        std::cout << (get_parameters().empty() ? "vide" : "rempli") << std::endl;
        for(auto& param : get_parameters()){
            std::visit([](auto* p){ 
                if(p){
                    p->hello();
                }else{
                    std::cout << "[nullptr param]" << std::endl;
                } 
            }, param);
        }
        std::cout << ")" << std::endl;
        if(get_init()){
            get_init()->hello();
        }
        if(get_then()){
            get_then()->hello();
        }
        std::cout << "outputs " << (get_outputs().empty() ? "vide" : "rempli") << std::endl;
        // for(auto& output : get_outputs()){
        //     std::cout << "output" << std::endl;
        //     std::visit([](auto* o){ o->hello(); }, output);
        // }
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
        // if(this->is_parenthesage()) std::cout << "(";

        // if(this->is_parenthesage()) std::cout << ")";
    }

    template<dataflow_type dft, expression_env expenv>
    void variable_contextual_expression<dft, expenv>::hello(){
        
    }

    template<dataflow_kind dfk, dataflow_type dft>
    void eater<dfk, dft>::hello(){}

    template<dataflow_kind dfk, dataflow_type dft>
    void feeder_block_expression<dfk, dft>::hello(){}

    void channel_eater::hello(){}

    void channel_feeder::hello(){}

    template<dataflow_kind dfk, dataflow_type dft>
    void collective_cast<dfk, dft>::hello(){}

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
}