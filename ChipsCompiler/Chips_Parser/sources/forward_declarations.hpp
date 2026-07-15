#ifndef __FORWARD_DECLS__
#define __FORWARD_DECLS__

#include "metamodel_enums.hpp"

namespace chips
{
    class program_node;
    class preamble_section_node;
    class system_section_node;
    template <expression_env expenv>
    class array;
    template <expression_env expenv>
    class variable;
    class primitive_variable;
    template <dataflow_type dft>
    class dataflow_primitive_variable;
    class node_variable;
    template <dataflow_type dft>
    class contextual_variable;
    class collective_variable;
    template <dataflow_type dft>
    class dataflow_collective_variable;
    class system_variable;
    template <block_type bt>
    class block_variable;
    template <dataflow_type dft>
    class dataflow_system_variable;

    template<statement_env, recurring_statement>
    class statement;
    template <dataflow_type dft, statement_env sttenv>
    class dataflow_declaration;
    template <dataflow_type dft, statement_env sttenv>
    class dataflow_assignment;
    template <statement_env sttenv>
    class if_section;
    template <statement_env sttenv>
    class else_section;
    template <statement_env sttenv>
    class if_statement;
    template <statement_env sttenv>
    class if_else_statement;
    template <statement_env sttenv, dataflow_type dft>
    class foreach_statement;
    template <block_type bt>
    class block_foreach_statement;
    template <dataflow_kind dfk, dataflow_type dft>
    class feeder;
    template <block_type bt>
    class block_declaration;
    class implements_statement;
    class channel_plugging;
    template <dataflow_kind dfk, dataflow_type dft>
    class feeding_statement;
    class linking_statement;
    template <node_element ne>
    class aliasing_statement;
    template <node_element ne>
    class node_element_declaration;

    template <dataflow_kind dfk, dataflow_type dft>
    class function_parameter;
    template <dataflow_type dft>
    class collective_parameter;

    template <dataflow_kind dfk, dataflow_type dft>
    class function_output;
    template <collective_output_kind cok>
    class collective_output;
    class default_output;
    class target_output;
    class channeled_output;

    class definition;
    class with_section;
    class init_section;
    class then_section;
    class collectiveops_section;
    class accumulator_definition;
    class node_definition;
    class object_definition;
    class function_definition;
    class logical_definition;
    class physical_definition;
    class implementation_defintion;
    class collective_function_definition;

    template <dataflow_type dft, expression_env expenv>
    class lvalue;
    template <dataflow_type dft, expression_env expenv>
    class rvalue;
    template <dataflow_type dft, expression_env expenv>
    class direct;
    template <dataflow_type dft, expression_env expenv>
    class function;
    template <dataflow_type dft, expression_env expenv>
    class plus;
    template <dataflow_type dft, expression_env expenv>
    class minus;
    template <dataflow_type dft, expression_env expenv>
    class mult;
    template <dataflow_type dft, expression_env expenv>
    class div;
    template <expression_env expenv>
    class mod;
    template <dataflow_type dft, expression_env expenv>
    class cast_as;
    template <dataflow_type dft, expression_env expenv>
    class uminus_operator;
    template <expression_env expenv, dataflow_type dft>
    class gt;
    template <expression_env expenv, dataflow_type dft>
    class lt;
    template <expression_env expenv, dataflow_type dft>
    class geq;
    template <expression_env expenv, dataflow_type dft>
    class leq;
    template <expression_env expenv>
    class or_operator;
    template <expression_env expenv>
    class and_operator;
    template <expression_env expenv>
    class not_operator;
    template <dataflow_type dft, expression_env expenv>
    class eq;
    template <dataflow_type dft, expression_env expenv>
    class neq;
    template <dataflow_type dft, expression_env expenv>
    class variable_expression;
    class input;
    class stop;
    template <dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract;
    template <dataflow_kind dfk, dataflow_type dft>
    class eater_abstract;
    class linkable;
    class support;
    class interface;
    class implementer;
    class node_variable_expression;
    template <block_type bt>
    class system_variable_block_expression;
    template <dataflow_kind dfk, dataflow_type dft>
    class eater;
    template <dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression;
    class channel_eater;
    class channel_feeder;
    template <dataflow_kind dfk, dataflow_type dft>
    class collective_cast;
    template<statement_env env>
    class statement_fillable;
}

#endif //__FORWARD_DECLS__