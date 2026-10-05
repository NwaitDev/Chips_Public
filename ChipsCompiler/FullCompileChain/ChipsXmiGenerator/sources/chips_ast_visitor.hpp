#include "ast_node_definitions.hpp"

using namespace chips;

class chips_ast_visitor {

    void visit(with_section);

    void visit(init_section);

    void visit(then_section);
	
	void visit(collectiveops_section);
    
	void visit(accumulator_definition);

	void visit(object_definition);
	
	void visit(logical_definition);

    void visit(physical_definition);
 
 
    void visit(channeled_output);
 
    void visit(default_output);
 
    void visit(target_output);

    void visit(collective_function_definition);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(function_parameter<dfk,dft>);
    
    template<dataflow_type dft>
    void visit(collective_parameter<dft>);
    
    template<dataflow_kind dfk, dataflow_type dft>
    void visit(function_output<dfk,dft>);

    void visit(system_variable_block_expression<block_type::LOGICAL>);
 
    void visit(system_variable_block_expression<block_type::PHYSICAL>);
 
	void visit(system_variable_block_expression<block_type::OBJECT>);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(eater<dfk,dft>);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(feeder_block_expression<dfk,dft>);

    void visit(channel_eater);
 
    void visit(channel_feeder);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(collective_cast<dfk,dft>);

    template<dataflow_type dft, expression_env expenv> 
	void visit(direct<dft,expenv>);

    template<dataflow_type dft, expression_env expenv> 
	void visit(class function<dft,expenv>);

    
    template <dataflow_type dft, expression_env expenv>
    void visit(plus<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(minus<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(mult<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(div<dft,expenv>);

    template <expression_env expenv>
    void visit(mod<expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(cast_as<dft,expenv>);

    template <expression_env expenv, dataflow_type dft>
    void visit(gt<expenv,dft>);

    template <expression_env expenv, dataflow_type dft>
    void visit(lt<expenv,dft>);

    template <expression_env expenv, dataflow_type dft>
    void visit(geq<expenv,dft>);

    template <expression_env expenv, dataflow_type dft>
    void visit(leq<expenv,dft>);

    template <expression_env expenv>
    void visit(or_operator<expenv>);

    template <expression_env expenv>
    void visit(and_operator<expenv>);

    template <expression_env expenv>
    void visit(not_operator<expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(uminus_operator<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(eq<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(neq<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(variable_expression<dft,expenv>);

    template <dataflow_type dft, expression_env expenv>
    void visit(variable_contextual_expression<dft,expenv>);

    void visit(input);

    void visit(stop);

    void visit(preamble_section_node);

    void visit(system_section_node);

    void visit(program_node);
    
    template<dataflow_type dft, statement_env stenv>
    void visit(dataflow_declaration<dft,stenv>);

    template<dataflow_type dft, statement_env stenv> 
    void visit(dataflow_assignment<dft,stenv>);

    template<statement_env stenv> 
    void visit(if_section<stenv>);

    template<statement_env stenv> 
    void visit(else_section<stenv>);

    template<statement_env stenv>
    void visit(if_statement<stenv>);

    template<statement_env stenv>
    void visit(if_else_statement<stenv>);

    template<statement_env stenv, dataflow_type dft>
    void visit(foreach_statement<stenv,dft>);

    template<block_type bt>
    void visit(block_foreach_statement<bt>);

    template<block_type bt>
    void visit(block_declaration<bt>);

    void visit(channel_plugging);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(feeding_statement<dfk,dft>);

    void visit(linking_statement);

    template<node_element ne>
    void visit(node_element_declaration<ne>);

    template<expression_env expenv> 
    void visit(array<expenv>);


    template<dataflow_type dft> 
    void visit(dataflow_primitive_variable<dft>);

    template<dataflow_type dft> 
    void visit(contextual_variable<dft>);

    template<dataflow_type dft> 
    void visit(dataflow_collective_variable<dft>);

    template<block_type bt> 
    void visit(block_variable<bt>);

    template<dataflow_type dft> 
    void visit(dataflow_system_variable<dft> system_dft_var);
};