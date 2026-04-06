#ifndef __chips_base__
#define __chips_base__

#include <iostream>
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"

namespace chips
{

    /**
     * Base abstract class for a visitor that walks
     * through a Chips AST
     */
    class visitor;

    template<statement_env env>
    class statement_fillable {
        public:
        virtual void add_statement(typename SttEnvToSttVariant<env>::type) = 0;
    };

    /**
     * Base abstract class for a node in the Chips 
     * Abstract Syntax Tree
     */
    class ast_node
    {
    private:
        int line;
        int column;

    public:
        inline int get_line() { return line; }
        inline int get_column() { return column; }
        inline void set_line(int l) { line = l; }
        inline void set_column(int c) { column = c; }

        virtual void hello() = 0;
        virtual ~ast_node() = default;
    };

    class visitor
    {
    public:
        virtual ~visitor() = default;

        virtual void visit(ast_node &node) = 0;
        virtual void visit(program_node& node) = 0;
        virtual void visit(preamble_section_node& node) = 0;
        virtual void visit(system_section_node& node) = 0;

        // template<expression_env expenv>
        // void visit(array<expenv>& node);
        // template<expression_env expenv>
        // void visit(variable<expenv>& node);
        // virtual void visit(primitive_variable& node) = 0;
        // template<dataflow_type dft>
        // void visit(dataflow_primitive_variable<dft>& node);
        // virtual void visit(node_variable& node) = 0;
        // template<dataflow_type dft>
        // void visit(contextual_variable<dft>& node);
        // virtual void visit(collective_variable& node) = 0;
        // template<dataflow_type dft>
        // void visit(dataflow_collective_variable<dft>& node);
        // virtual void visit(system_variable& node) = 0;
        // template<block_type bt>
        // void visit(block_variable<bt>& node);
        // template<dataflow_type dft>
        // void visit(dataflow_system_variable<dft>& node);

        // template<dataflow_type dft, statement_env sttenv>
        // void visit(dataflow_declaration<dft, sttenv>& node);
        // template<dataflow_type dft, statement_env sttenv>
        // void visit(dataflow_assignment<dft, sttenv>& node);
        // template<statement_env sttenv>
        // void visit(if_section<sttenv>& node);
        // template<statement_env sttenv>
        // void visit(else_section<sttenv>& node);
        // template<statement_env sttenv>
        // void visit(if_statement<sttenv>& node);
        // template<statement_env sttenv>
        // void visit(if_else_statement<sttenv>& node);
        // template<statement_env sttenv, dataflow_type dft>
        // void visit(foreach_statement<sttenv, dft>& node);
        // template<block_type bt>
        // void visit(block_foreach_statement<bt>& node);
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(feeder<dfk, dft>& node);
        // template<block_type bt>
        // void visit(block_declaration<bt>& node);
        // virtual void visit(implements_statement& node) = 0;
        // virtual void visit(channel_plugging& node) = 0;
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(feeding_statement<dfk, dft>& node);
        // virtual void visit(linking_statement& node) = 0;
        // template<node_element ne>
        // void visit(aliasing_statement<ne>& node);
        // template<node_element ne>
        // void visit(node_element_declaration<ne>& node);

        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(function_parameter<dfk, dft>& node);
        // template<dataflow_type dft>
        // void visit(collective_parameter<dft>& node);

        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(function_output<dfk, dft>& node);
        // template<collective_output_kind cok>
        // void visit(collective_output<cok>& node);
        // virtual void visit(default_output& node) = 0;
        // virtual void visit(target_output& node) = 0;
        // virtual void visit(channeled_output& node) = 0;

        // virtual void visit(definition& node) = 0;
        // virtual void visit(with_section& node) = 0;
        // virtual void visit(init_section& node) = 0;
        // virtual void visit(then_section& node) = 0;
        // virtual void visit(collectiveops_section& node) = 0;
        // virtual void visit(accumulator_definition& node) = 0;
        // virtual void visit(node_definition& node) = 0;
        // virtual void visit(object_definition& node) = 0;
        // virtual void visit(function_definition& node) = 0;
        // virtual void visit(logical_definition& node) = 0;
        // virtual void visit(physical_definition& node) = 0;
        // virtual void visit(implementation_defintion& node) = 0;
        // virtual void visit(collective_function_definition& node) = 0;

        // template<dataflow_type dft, expression_env expenv>
        // void visit(lvalue<dft,expenv>& node);
        // template<dataflow_type dft, expression_env expenv>
        // void visit(rvalue<dft,expenv>& node){
        //     std::cerr << "ast_base rvalue" << std::endl;
        //     visit(static_cast<ast_node&>(node));
        // }
        // virtual void visit(system_iterable& node) = 0;
        // template<dataflow_type dft, expression_env expenv>
        // void visit(direct<dft, expenv>& node){
        //     std::cerr << "ast_base direct" << std::endl;
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(function<dft, expenv>& node);
        // template<dataflow_type dft, expression_env expenv>
        // void visit(plus<dft, expenv>& node){
        //     std::cerr << "ast_base plus" << std::endl;
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(minus<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(uminus_operator<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(mult<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(div<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv>
        // void visit(mod<expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(cast_as<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv, dataflow_type dft>
        // void visit(gt<expenv, dft>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv, dataflow_type dft>
        // void visit(lt<expenv, dft>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv, dataflow_type dft>
        // void visit(geq<expenv, dft>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv, dataflow_type dft>
        // void visit(leq<expenv, dft>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv>
        // void visit(or_operator<expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv>
        // void visit(and_operator<expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<expression_env expenv>
        // void visit(not_operator<expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(eq<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(neq<dft, expenv>& node){
        //     visit(static_cast<ast_node&>(node));
        // }
        // template<dataflow_type dft, expression_env expenv>
        // void visit(variable_expression<dft, expenv>& node);
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(feeder_abstract<dfk, dft>& node);
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(eater_abstract<dfk, dft>& node);
        // virtual void visit(linkable& node) = 0;
        // virtual void visit(support& node) = 0;
        // virtual void visit(interface& node) = 0;
        // virtual void visit(implementer& node) = 0;
        // virtual void visit(node_variable_expression& node) = 0;
        // template<block_type bt>
        // void visit(system_variable_block_expression<bt>& node);
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(eater<dfk, dft>& node);
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(feeder_block_expression<dfk, dft>& node);
        // virtual void visit(channel_eater& node) = 0;
        // virtual void visit(channel_feeder& node) = 0;
        // template<dataflow_kind dfk, dataflow_type dft>
        // void visit(collective_cast<dfk, dft>& node);
    };

}

#endif