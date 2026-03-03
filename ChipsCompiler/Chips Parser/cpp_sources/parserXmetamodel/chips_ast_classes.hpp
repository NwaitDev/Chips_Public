#ifndef ASTMETAMODEL_H
#define ASTMETAMODEL_H
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>
#include <iostream>

namespace chips
{
    /**
     * Components that can be plugged in system section
     */ 
    enum block_type {
        LOGICAL, // only using regular in/outputs
        PHYSICAL, // can use regular in/outputs, sensor/actuators and channel in/outputs
        OBJECT // can only be plugged to other objects with channel in/outputs
    };

    /** 
     * Types of the elements that can appear in the preamble section
     */
    enum definition_type {
        NODE, // to define objects and physicals
        FUNCTION, // to define logical and physicals
        IMPLEMENTATION // to define node inheritance (work in progress, do not use)
    };

    /**
     * Environments for the interpretation 
     * of direct values and variables
     */
    enum rvalue_env {
        PRIMITIVE, // each value is interpreted as a regular variable
        COLLECTIVE, // each value can be interpreted as either a value of its type or a "NULL" (stop value)
        SYSTEM // each value is interpreted as a regular variable until it is plugged. Then, it represents a constant dataflow
    };

    /**
     * Primitive types of data that Chips handles
     */
    enum dataflow_type {
        INT, // regular integers
        FLOAT, // floating point values
        BOOL // booleans
    };

    /**
     * Kind of signals to be distinguished when working with Cyber Physical Systems
     */
    enum dataflow_kind {
        LOGICAL, // produced by any functional block or system variable
        PHYSICAL // specific to physical functional blocks
    };

    /**
     * Node specific variable kinds
     */
    enum node_element {
        CHANNEL, // communication port to refer to when transmitting a signal between nodes
        CONTEXTUAL // variable shared by all the functional blocks supported by a node
    };

    //////////////// GENERIC ELEMENTS FOR AST MANAGMENT /////////////////////
    class visitor;
    class ast_node{
    public:
        void hello();
        virtual void accept(visitor& v) = 0;
    };
    class visitor{
    public:
        virtual void visit(ast_node &node) = 0;
    };


    //////////////// VERY BROAD CONCEPTS FOR CHIPS SPECIFIC AST //////////////
    class program_node : public ast_node; // concrete
    class preamble_section_node : public ast_node; // concrete
    class system_section_node : public ast_node; // concrete
    class definition : public ast_node; // abstract
    class system_statement : public ast_node; // abstract


    //////////////// VARIABLE CONCEPTS //////////////////////
    // In chips, each variable is considered as a (dynamic) array.
    // By default, variables are arrays of dimension 1.
    // When declared with a [integer expression]+ suffix,
    // it is of the given dimension(s).

    template<enum rvalue_env> 
    class array : public ast_node; // concrete
    template<enum rvalue_env V>
    class variable : public array<V>; // concrete


    //////////////////// VARIABLE AST NODES ////////////////////////

    class primitive_variable : public variable<chips::rvalue_env::PRIMITIVE>; // abstract
    template<dataflow_type dft> 
    class dataflow_primitive_variable : public primitive_variable; // concrete

    class node_variable : public variable<chips::rvalue_env::PRIMITIVE>; // abstract
    template<dataflow_type dft> 
    class contextual_variable : public node_variable; // concrete

    class collective_variable : public variable<chips::rvalue_env::COLLECTIVE>; // abstract
    template<dataflow_type dft> 
    class dataflow_collective_variable; // concrete


    class system_variable : public variable<chips::rvalue_env::SYSTEM>; // abstract
    template<block_type bt> 
    class block_variable : public system_variable; // concrete
    template<dataflow_type dft> 
    class dataflow_system_variable : public system_variable; // concrete

    ////////////////// STATEMENTS MANAGEMENT ////////////////////////

    /**
     * Statements that are encountered in different environments
     */
    enum recuring_statements {
        // generic
        IF, // if ( bool expr ){ statements } [ else { statements } ]
        FOREACH, // for variable in iterable { statements }
        DECLARATION, // type identifier
        ASSIGNMENT, // identifier = expression
        
        // specific to system section
        IMPLEMENTS, // identifier implements identifier using identifier
        PLUGGING, // identifier.identifier(identifier.identifier)
        FEEDING, // identifier.identifier(expression | identifier.identifier)
        LINKING // link identifier to identifier

        // specific to implementation section (work in progress, do not use)
        ALIASING

    };

    /**
     * Environments that should allow to distinguish
     * the kind of statements that can be used in the code
     */
    enum statement_env {
        PRIMITIVE, // in the body of function definitions (init/then sections)
        COLLECTIVE, // in the body of collective primitive definitions
        SYSTEM, // in the system description
        IMPLEMENTATION, // in the body of node implementation definition (work in progress, do not use)
        NODE // in the body of a node definitions (with sections)
    };


    template<enum statement_env, enum recuring_statements>
    class statement : public ast_node; // abstract class

    template<recuring_statements>
    using system_statement = statement<statement_env::SYSTEM>; // abstract (by definition)
    template<recuring_statements>
    using node_statement = statement<statement_env::NODE>; // abstract (by definition)
    template<recuring_statements>
    using implementation_statement = statement<statement_env::IMPLEMENTATION>; // abstract (by definition)
    template<recuring_statements>
    using primitive_statement = statement<statement_env::PRIMITIVE>; // abstract (by definition)
    template<recuring_statements>
    using collective_statement = statement<statement_env::COLLECTIVE>; // abstract (by definition)


    ////// Generic statements
    template<dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recuring_statements::DECLARATION>; // concrete
    template<dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recuring_statements::ASSIGNMENT>; // concrete

    template<statement_env stenv>
    class if_statement : public statement<stenv,recuring_statements::IF>; // concrete
    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv>; // concrete
    template<statement_env stenv>
    class foreach_statement : public statement<stenv, recuring_statements::FOREACH>; // concrete
    template<statement_env stenv>
    class if_section; // concrete
    template<statement_env stenv>
    class else_section; // concrete

    ////// System specific statements
    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM , recuring_statements::DECLARATION>; // concrete

    class implements_statement : public system_statement<recuring_statements::IMPLEMENTS>; // concrete (work in progress, do not use)

    class channel_plugging : public system_statement<recuring_statements::PLUGGING>; // concrete

    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recuring_statements::FEEDING>; // concrete

    class linking_statement : public system_statement<recuring_statements::LINKING>; // concrete

    ////// Implementation specific statements (work in progress, do not use)

    template <enum node_element>
    class aliasing_statement : public implementation_statement<recuring_statements::ALIASING>; // concrete

    ////// Node specific statements
    enum node_declarable{
        CHANNEL,
        INT,
        FLOAT,
        BOOL
    };
    template<enum node_declarable>
    class node_element_declaration : public node_statement<recuring_statements::DECLARATION>; // concrete



    class program_node : public ast_node
    {
    private:
        std::string m_filename;
        preamble_section_node m_preamble;
        system_section_node m_system;

    public:
        program_node(std::string filename, preamble_section_node &preamble, system_section_node &system);
    };
}

#endif