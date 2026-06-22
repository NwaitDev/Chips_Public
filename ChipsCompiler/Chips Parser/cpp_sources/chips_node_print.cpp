#include "chips_overall.hpp"
#include "chips_expressions.hpp"
#include "chips_overall_stts.hpp"
#include "chips_overall_system.hpp"
#include "chips_overall_collective.hpp"
#include "chips_declaration_ctx.hpp"
#include "chips_config_stts.hpp"
#include "chips_ast_classes.hpp"
#include "ChipsAST.hpp"
#include <iostream>

void chips_node::hello() {
    if(preambles){
        get_preambles()->hello();
    }
    if(system){
        get_system()->hello();
    }
}

void dataflow_type_node::hello() {
    switch(get_type()){
        case INT_DF: std::cout << "int "; break;
        case FLOAT_DF: std::cout << "float "; break;
        case BOOL_DF: std::cout << "bool "; break;
    }
    if(suff){
        get_suffixes()->hello();
    }
}

void expressions_node::hello() {
    if(get_expressions().size() == 1){
        get_expressions().at(0)->hello();
    }else{
        for(int i = 0; i < get_expressions().size(); i++){
            get_expressions().at(i)->hello();
            if(i != get_expressions().size() - 1){
                std::cout << ", ";
            }
        }
    }
}

void binary_expression_node::hello() {
    if(lhs){
        get_lhs()->hello();
    }
    switch(get_type()){
        case LT_EXP: std::cout << " < "; break;
        case GT_EXP: std::cout << " > "; break;
        case LEQ_EXP: std::cout << " <= "; break;
        case GEQ_EXP: std::cout << " >= "; break;
        case NEQ_EXP: std::cout << " != "; break;
        case EQ_EXP: std::cout << " == "; break;
        case AND_EXP: std::cout << " && "; break;
        case OR_EXP: std::cout << " || "; break;
        case PLUS_EXP: std::cout << " + "; break;
        case MINUS_EXP: std::cout << " - "; break;
        case TIMES_EXP: std::cout << " * "; break;
        case DIV_EXP: std::cout << " / "; break;
        case MOD_EXP: std::cout << " % "; break; 
    }
    if(rhs){
        get_rhs()->hello();
    }
}

void unary_expression_node::hello() {
    switch(get_type()){
        case U_MINUS_EXP: std::cout << "-"; break;
        case NOT_EXP: std::cout << "!"; break;
    }
    if(operand){
        get_rhs()->hello();
    }
}

void number_literal_node::hello() {
    switch(get_type()){
        case INT_EXP: std::cout << get_int(); break;
        case FLOAT_EXP: std::cout << get_float(); break;
        case BOOL_EXP: std::cout << (get_bool() ? "true" : "false"); break;
    }
}

void function_call_node::hello() {}

void variable_node::hello() {
    std::cout << get_identifier() << " ";
}

void plugging_expr_node::hello() {
    if(get_block()){
        get_block()->hello();
        std::cout << "." << get_identifier() << " "; 
    }
}

void object_virtual_output_node::hello() {}

void object_physical_attribute_node::hello() {}

void cast_node::hello() {
    std::cout << "(";
    if(type){
        get_df_type()->hello();
    }
    std::cout << ")";
    if(expr){
        get_expr()->hello();
    }
}

void suffixes_node::hello() {
    for(const auto& suf : get_suffixes()){
        std::cout << "[";
        if(suf){
            suf.get()->hello();
        }
        std::cout << "]";
    }
}

void suffixised_node::hello() {
    std::cout << get_identifier() << " ";
    if(suffixes){
        get_suffixes()->hello();
    }
}

void c_statements_node::hello() {
    for(const auto& sttmt : get_statements()){
        if(sttmt){
            sttmt->hello();
            if(sttmt->get_type() == IF_ST || sttmt->get_type() == LOOP_ST || sttmt->get_type() == IFELSE_ST){
                std::cout << std::endl;
            }else{
                std::cout << ";" << std::endl;
            }
        }
    }
}

void c_loop_node::hello() {
    std::cout << "for " << get_ident1() << " in ";
    if(get_loop_expr()){
        get_loop_expr()->hello();
    }
    std::cout << "{\n";
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void c_if_node::hello() {
    std::cout << "if (";
    if(cond){
        get_condition()->hello();
    }
    std::cout << "){\n\t";
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void c_if_else_node::hello() {
    if(ifnode){
        get_if_node()->hello();
    }
    std::cout << "else{\n";
    if(elsestts){
        get_else_node()->hello();
    }
    std::cout << "}\n";
}

void c_expressions_node::hello() {
    if(get_expressions().size() == 1){
        get_expressions().at(0)->hello();
    }else{
        for(int i = 0; i < get_expressions().size(); i++){
            get_expressions().at(i)->hello();
            if(i != get_expressions().size() - 1){
                std::cout << ", ";
            }
        }
    }
}

void s_statements_node::hello() {
    for(const auto& sttmt : get_statements()){
        if(sttmt){
            sttmt->hello();
            if(sttmt->get_type() == IF_ST || sttmt->get_type() == LOOP_ST || sttmt->get_type() == IFELSE_ST){
                std::cout << std::endl;
            }else{
                std::cout << ";" << std::endl;
            }
        }
    }
}

void s_loop_node::hello() {
    std::cout << "for " << get_identifier() << " in ";
    if(get_loop_expr()){
        get_loop_expr()->hello();
        std::cout << "{\n\t";
    }
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void s_if_node::hello() {
    std::cout << "if (";
    if(cond){
        get_condition()->hello();
    }
    std::cout << "){\n\t";
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void s_if_else_node::hello() {
    if(ifnode){
        get_if_node()->hello();
    }
    std::cout << "else{\n\t";
    if(elsestts){
        get_else_node()->hello();
    }
    std::cout << "}\n";
}

void link_node::hello() {
    std::cout << "link " << get_source();
    if(get_suffixes_source()){
        get_suffixes_source()->hello();
    }
    std::cout << " to " << get_target();
    if(get_suffixes_target()){
        get_suffixes_target()->hello();
    }
}

void implements_node::hello() {
    std::cout << get_ident1() << " ";
    if(suffixes1){
        get_suffixes1()->hello();
    }
    std::cout << " implements " << get_ident2() << " ";
    if(suffixes2){
        get_suffixes2()->hello();
    }
    std::cout << " using " << get_ident3();
}

void plugging_node::hello() {
    if(block){
        get_block()->hello();
    }
    std::cout << " . " << get_identifier() << " ";
    if(suff){
        get_suffixes()->hello();
    } 
    if(expr){
        std::cout << "(";
        get_expression()->hello();
        std::cout << ")";
    }
}

void statements_node::hello() {
    for(const auto& sttmt : get_statements()){
        sttmt->hello();
        if(sttmt->get_type() == IF_ST || sttmt->get_type() == LOOP_ST || sttmt->get_type() == IFELSE_ST){
            std::cout << std::endl;
        }else{
            std::cout << ";" << std::endl;
        }
    }
}

void rhs_assignment_node::hello() {
    if(value){
        std::cout << "= ";
        value->hello();
    }
}

void assignment_node::hello() {}

void variable_assignment_node::hello() {
    std::cout << get_identifier() << " ";
    if(suff){
        get_suffixes()->hello();
    }
    std::cout << " = ";
    if(expr){
        get_expression()->hello();
    }
}

void this_attribute_node::hello() {}

void dataflow_full_declaration_node::hello() {
    if(type){
        get_df_type()->hello();
    }
    std::cout << " " << get_identifier() << " ";
    if(assign){
        get_rhs()->hello();
    }
}

void function_call_statement_node::hello() {}

void if_node::hello() {
    std::cout << "if (";
    if(cond){
        get_condition()->hello();
    }
    std::cout << "){\n\t";
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void if_else_node::hello() {
    if(ifnode){
        get_if_node()->hello();
    }
    std::cout << "else{\n";
    if(elsestts){
        get_else_node()->hello();
    }
    std::cout << "}\n";
}

void loop_node::hello() {
    std::cout << "for " << get_ident1() << " in ";
    if(get_loop_expr()){
        get_loop_expr()->hello();
    }
    std::cout << "{\n";
    if(stts){
        get_statements()->hello();
    }
    std::cout << "}\n";
}

void preambles_node::hello() {
    for(const auto& preamble : get_preamble_list()){
        if(preamble) {
            preamble.get()->hello();
        }
    }
}

void object_definition_node::hello() {
    std::cout << "object " << get_identifier() << " ";
    if(with){
        get_with()->hello();
    }
    std::cout << "\n";
}

void function_definition_node::hello() {}

void logical_function_definition_node::hello() {
    std::cout << "logical " << get_identifier() << "( ";
    if(df_parameter_list){
        get_df_parameter_list()->hello();
    }
    std::cout << ") ";
    if(init){
        get_init()->hello();
    }
    if(then){
        get_then()->hello();
    }
    if(outputs){
        get_outputs()->hello();
    }
    std::cout << "\n";
}

void physical_function_definition_node::hello() {
    std::cout << "physical " << get_identifier() << "(";
    if(pdf_parameter_list){
        get_pdf_parameter_list()->hello();
    }
    std::cout << ") ";
    if(with){
        get_with()->hello();
    }
    if(init){
        get_init()->hello();
    }
    if(then){
        get_then()->hello();
    }
    if(outputs){
        get_outputs()->hello();
    }
    std::cout << "\n";
}

void collective_operation_definition_node::hello() {
    if(get_signature()){
        get_signature()->hello();
        std::cout << "{\n\t";
    }
    if(get_statements()){
        get_statements()->hello();
    }
    std::cout << "}\n-> @(";
    if(get_expressions()){
        get_expressions()->hello();
    }
    std::cout << ")\n";
    if(get_output()){
        get_output()->hello();
    }
    if(get_optionnal_output()){
        get_optionnal_output()->hello();
    }
}

void implementation_definition_node::hello() {
    std::cout << "implementation " << get_ident1() 
              << " : " << get_ident2() << " by " 
              << get_ident3() << "{\n\t";
    if(node){
        get_node()->hello();
    }
    std::cout << "}\n";
}

void node_mappings_node::hello() {
    if(node){
        std::cout << "having " << get_ident1() << " as " << get_ident2() << ";\n";
        get_node()->hello();
    }
}

void output_node::hello() {}

void with_statements_node::hello() {
    for(const auto& sttm : get_statements()){
        sttm.get()->hello();
        if(sttm->get_type() == IF_ST || sttm->get_type() == LOOP_ST || sttm->get_type() == IFELSE_ST){
            std::cout << std::endl;
        }else{
            std::cout << ";" << std::endl;
        }
    }
}

void with_two_identifier_node::hello() {
    std::cout << get_ident1() << " " << get_ident2();
}

void with_context_statement_node::hello() {
    std::cout << "ctx ";
    if(type){
        get_df_type()->hello();
    }
    std::cout << " " << get_identifier() << " ";
    if(rhs){
        get_rhs()->hello();
    }
}

void system_node::hello() {
    std::cout << "system {\n\t";
    if(get_system_statements()){
        get_system_statements()->hello();
    }
    std::cout << "}\n";
}

// void function_declaration_node::hello() {}

void c_optionnal_outputs_node::hello() {
    for(const auto& output : get_outputs()){
        output->hello();
    }
}

void c_output_node::hello() {
    std::cout << "-> " << get_identifier() << "(";
    if(exprs){
        get_expressions()->hello();
    }
    std::cout << ")" << std::endl;
}

void c_signature_node::hello() {
    if(keywords){
        get_keywords()->hello();
    }
    std::cout << "(";
    if(cdf_defaulted_decls){
        get_collective_dataflow_defaulted_decls()->hello();
    }
    std::cout << ") " << get_ident1() << " among " << get_ident2();
}

void spread_node::hello() {
    std::cout << "spread ";
}

void collect_node::hello() {
    std::cout << "collect ";
}

void stop_node::hello() {
    std::cout << "stop ";
}

void input_node::hello() {
    std::cout << "input ";
}

void with_section_node::hello() {
    if(sttms){
        if(!get_statements()->get_statements().empty()){
            std::cout << "with {\n\t";
            get_statements()->hello();
            std::cout << "}\n";
        }
    }
}

void init_section_node::hello() {
    if(statements){
        if(!get_statements()->get_statements().empty()){
            std::cout << "init {\n\t";
            get_statements()->hello();
            std::cout << "}\n";
        }
    }    
}

void then_section_node::hello() {
    if(statements){
        if(!get_statements()->get_statements().empty()){
            std::cout << "then {\n\t";
            get_statements()->hello();
            std::cout << "}\n";
        }
    }
    
}

void paren_expression_node::hello() {
    std::cout << "(";
    if(expr){
        get_expr()->hello();
    }
    std::cout << ")";
}

void c_cast_node::hello() {
    std::cout << "(";
    if(type){
        get_df_type()->hello();
    }
    std::cout << ")";
    if(expr){
        get_expr()->hello();
    }
}

// void s_suffixable_node::hello() {}

void block_node::hello() {
    std::cout << get_identifier() << " ";
    if(suff){
        get_suffixes()->hello();
    }
}

void named_outputs_node::hello() {
    for(const auto& output : get_outputs()){
        output.get()->hello();
    }
}

void physical_named_output_node::hello() {
    // Base implementation for physical named output nodes
}

void named_output_node::hello() {
    std::cout << "-> " << get_identifier() << " (";
    if(exprs){
        get_expressions()->hello();
    }
    std::cout << ")\n";
}

void physical_named_outputs_node::hello() {
    for(const auto& output : get_outputs()){
        output.get()->hello();
    }
}

void actuator_node::hello() {
    std::cout << "-> actuator " << get_identifier() << "(";
    if(exprs){
        get_expressions()->hello();
    }
    std::cout << ")\n";
}

void dataflow_parameter_list_node::hello() {}

void dataflow_parameter_decls_node::hello() {
    if(df_param_decls.size() == 1){
        df_param_decls.at(0).get()->hello();
    }else{
        for(int i = 0; i < df_param_decls.size(); i++){
            df_param_decls.at(i).get()->hello();
            if(i != df_param_decls.size() - 1){
                std::cout << ", ";
            }
        }
    }
}

void dataflow_parameter_decl_node::hello() {
    if(type){
        get_df_type()->hello();
    }
    std::cout << " " << get_identifier() << " ";
    if(assign){
        get_rhs()->hello();
    }
}

void physical_dataflow_parameter_type_node::hello() {
    if(is_sensor){
        std::cout << "sensor ";
    }
    if(type){
        get_df_type()->hello();
    }
}

void physical_dataflow_parameter_list_node::hello() {
    for(const auto& df_param : get_physical_dataflow_parameter_decls()){
        df_param.get()->hello();
    }
}

void physical_dataflow_parameter_decls_node::hello() {
    if(pdf_param_decls.size() == 1){
        pdf_param_decls.at(0).get()->hello();
    }else{
        for(int i = 0; i < pdf_param_decls.size(); i++){
            pdf_param_decls.at(i).get()->hello();
            if(i != pdf_param_decls.size() - 1){
                std::cout << ", ";
            }
        }
    }
}

void physical_dataflow_parameter_decl_node::hello() {
    if(type){
        get_df_type()->hello();
    }
    std::cout << " " << get_identifier() << " ";
    if(assign){
        get_rhs()->hello();
    }
}

void collective_dataflow_defaulted_decls_node::hello() {
    if(cdf_defaulted_decls.size() == 1){
        cdf_defaulted_decls.at(0).get()->hello();
    }else{
        for(int i = 0; i < cdf_defaulted_decls.size(); i++){
            cdf_defaulted_decls.at(i).get()->hello();
            if(i != cdf_defaulted_decls.size() - 1){
                std::cout << ", ";
            }
        }
    }
}

void collective_dataflow_defaulted_decl_node::hello() {
    if(type){
        get_df_type()->hello();
    }
    std::cout << get_identifier() << " = ";
    if(expr){
        get_expression()->hello();
    }
}

void collective_rhs_assignment_node::hello() {
    if(expr){
        std::cout << " = ";
        get_expression()->hello();
    }
}

void functionnal_block_instanciation_node::hello() {
    std::cout << get_ident1() << " ";
    if(suff){
        get_suffixes()->hello();
    }
    std::cout << " " << get_ident2();
}

void collective_dataflow_full_declaration_node::hello() {
    if(get_df_type()) {
        get_df_type()->hello();
    }
    std::cout << get_identifier();
    if(get_rhs()) {
        get_rhs()->hello();
    }
}

void c_variable_assignment_node::hello() {
    std::cout << get_identifier();
    if(get_suffixes()) {
        get_suffixes()->hello();
    }
    if(get_expression()) {
        std::cout << " = ";
        get_expression()->hello();
    }
}

void c_context_variable_assignment_node::hello() {
    std::cout << "ctx." << get_identifier();
    if(get_suffixes()){
        get_suffixes()->hello();
    }
    std::cout << " = ";
    if(get_expression()){
        get_expression()->hello();
    }
}

void context_expression_node::hello() {
    std::cout << "ctx." << get_identifier();
    if(get_suffixes()){
        get_suffixes()->hello();
    }
}

void integrated_function_node::hello() {
    std::cout << get_identifier() << "(";
    if(get_expressions()){
        get_expressions()->hello();
    }
    std::cout << ")";
}

void context_variable_assignment_node::hello() {
    std::cout << "ctx." << get_identifier();
    if(get_suffixes()){
        get_suffixes()->hello();
    }
    std::cout << " = ";
    if(get_expression()){
        get_expression()->hello();
    }
}

void context_decl_node::hello() {
    std::cout << "ctx." << get_identifier();
    if(get_suffixes()){
        get_suffixes()->hello();
    }
}

void collective_cast_node::hello() {
    if(get_collective_operation()){
        get_collective_operation()->hello();
    }
    if(get_block()){
        get_block()->hello();
    }
    std::cout << "." << get_identifier();
}

void collective_operation_node::hello() {
    std::cout << "(" << get_identifier()  << ")";
}

void statement_node::hello() {
    std::cout << "[Abstract statement_node]" << std::endl;
}