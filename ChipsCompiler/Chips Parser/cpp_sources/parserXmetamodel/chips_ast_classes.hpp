#ifndef ASTMETAMODEL_H
#define ASTMETAMODEL_H
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>
#include <iostream>

namespace chips
{
    

    enum block_type {
        LOGICAL,
        PHYSICAL,
        OBJECT
    };

    enum definition_type {
        NODE,
        FUNCTION,
        IMPLEMENTATION
    };

    enum rvalue_context {
        PRIMITIVE,
        COLLECTIVE,
        SYSTEM
    };

    enum statement_context {
        PRIMITIVE,
        COLLECTIVE,
        SYSTEM,
        IMPLEMENTATION,
        NODE
    };

    enum dataflow_type {
        INT,
        FLOAT,
        BOOL
    };

    enum recuring_statements {
        IF,
        IF_ELSE,
        FOREACH,
        DECLARATION,
        ASSIGNMENT
    };

    class ast_node;
    // all the following node types extend the ast_node class
    class program_node : public ast_node;
    class preamble_section_node : public ast_node;
    class system_section_node : public ast_node;
    class chips_visitor : public ast_node;
    class definition : public ast_node;
    class system_statement : public ast_node;

    template<enum rvalue_context> class array : public ast_node;
    template<enum rvalue_context V> class variable : public array<V>;


    class primitive_variable : public variable<chips::rvalue_context::PRIMITIVE>;
    template<dataflow_type dft> class dataflow_primitive_variable : public primitive_variable;

    class node_variable : public variable<chips::rvalue_context::PRIMITIVE>;
    template<dataflow_type dft> class contextual_variable : public node_variable;

    class collective_variable : public variable<chips::rvalue_context::COLLECTIVE>;
    template<dataflow_type dft> class dataflow_collective_variable;

    class system_variable : public variable<chips::rvalue_context::SYSTEM>;
    template<block_type bt> class block_variable : public system_variable;
    template<dataflow_type dft> class dataflow_system_variable : public system_variable;

    template<statement_context stctx, recuring_statements recstt>
    class statement : ast_node; // abstract

    template<recuring_statements recstt>
    using system_statement = statement<statement_context::SYSTEM>;
    template<recuring_statements recstt>
    using node_statement = statement<statement_context::NODE>;
    template<recuring_statements recstt>
    using implementation_statement = statement<statement_context::IMPLEMENTATION>;
    template<recuring_statements recstt>
    using primitive_statement = statement<statement_context::PRIMITIVE>;
    template<recuring_statements recstt>
    using collective_statement = statement<statement_context::COLLECTIVE>;

    template<dataflow_type dft, statement_context stctx>
    class dataflow_declaration : public statement<stctx, recuring_statements::DECLARATION>;
    template<dataflow_type dft, statement_context stctx>
    class dataflow_assignment : public statement<stctx, recuring_statements::ASSIGNMENT>;

    template<recuring_statements recstt, statement_context stctx>
    class if_statement : public statement;
    class if_else : public if_statement<>;
    class primitive_foreach : public primitive_statement;
    class if_section;
    class else_section;

    class program_node : public ast_node
    {
    private:
        std::string m_filename;
        preamble_section_node &m_preamble;
        system_section_node &m_system;

    public:
        program_node(std::string filename, preamble_section_node &preamble, system_section_node &system);
    };


    class chips_visitor
    {
    public:
        virtual void visit(ast_node &node) = 0;
    };
}

#endif