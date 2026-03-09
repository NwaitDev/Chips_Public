#ifndef __forward_declarations__
#define __forward_declarations__
#include "metamodel_enums.hpp"

namespace chips {

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////// GENERIC ELEMENTS FOR AST MANAGMENT ////////////
    ////////////////////////////////////////////////////////////////
    
    /**
     * Base abstract class for a node in the Chips 
     * Abstract Syntax Tree
     */
    class ast_node;

    /**
     * Base abstract class for a visitor that walks
     * through a Chips AST
     */
    class visitor;


    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////// VERY BROAD CONCEPTS FOR CHIPS SPECIFIC AST ////
    ////////////////////////////////////////////////////////////////

    /**
     * Concrete class
     * Root node for a Chips program in Chips AST
     */
    class program_node;

    /**
     * Concrete class
     * Node of the Chips AST that holds all the definitions
     * of Chips components (Logical, Physical and Objects)
     */
    class preamble_section_node;

    /**
     * Concrete class
     * Node of the Chips AST that holds the description
     * of a complete system (an assembly of Chips components)
     */
    class system_section_node;

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////// VARIABLE CONCEPTS /////////////////////////////
    ////////////////////////////////////////////////////////////////

    /**
     * Concrete class
     * Node of the AST that represents an array of elements
     * that can be instanciated in the parametering 
     * expression environment
     */
    template<expression_env>
    class array;
    
    /**
     * Abstract class
     * Node of the AST that represents a variable of any kind.
     * In chips, each variable is considered as a (dynamic) array.
     * By default, variables are arrays of dimension 1.
     * When declared with a [integer expression]+ suffix,
     * it is of the given dimension(s).
     */
    template<expression_env>
    class variable;

    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is manipulated inside a functional block or to
     * initialize other variables in nodes
     * (with/init/then sections)
     * A variable of this kind is NOT contextual
     */
    class primitive_variable;

    /**
     * Concrete class
     * Node of the AST that represents a variable that
     * is manipulated inside a functional block or to
     * initialize other variables in nodes
     * (it is currently the only specialization of
     * the primitive_variable class)
     */
    template<dataflow_type>
    class dataflow_primitive_variable;

    /**
     * Abstract class
     * Node of the AST that represents the kind of 
     * variables that can only be specified inside
     * the with section of a Node (i.e. Physical or Object)
     */
    class node_variable;

    /**
     * Concrete class
     * Node of the AST that represents a contextual
     * variable.
     */
    template<dataflow_type>
    class contextual_variable;
    
    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive.
     */
    class collective_variable;
    
    /**
     * Concrete class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive. 
     * (it is currently the only specialization of
     * the collective_variable class)
     */
    template<dataflow_type>
    class dataflow_collective_variable;
    
    /**
     * Abstract class
     * Node of the AST that represents a variable
     * that can be used in the system section.
     */
    class system_variable;
    
    /**
     * Concrete class
     * Node of the AST that represents a component
     * of the model that was instantiated from a
     * former definition (Object/Logical/physical)
     */
    template<block_type> 
    class block_variable;
    
    /**
     * Concrete class
     * Node of the AST that represents a variable holding 
     * an int/float/bool when used in an arithmetic/logical
     * expression of the system section. 
     * When used as the input of a component, it represents
     * a constant input dataflow of the value it contains
     * at compile time.
     */
    template<dataflow_type> 
    class dataflow_system_variable;
    

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////////STATEMENTS MANAGEMENT/////////////////////////
    ////////////////////////////////////////////////////////////////



    /**
     * Abstract class
     * Node of the AST that represents a statement in any 
     * Chips code environment.
     */
    template<statement_env, recurring_statement>
    class statement{};

    // abstract (by definition of statement class)
    template<recurring_statement recstt>
    using system_statement = statement<statement_env::SYSTEM, recstt>;
    // abstract (by definition of statement class) 
    template<recurring_statement recstt>
    using node_statement = statement<statement_env::NODE, recstt>;
    // abstract (by definition of statement class) // do not use, work in progress
    template<recurring_statement recstt>
    using implementation_statement = statement<statement_env::IMPLEMENTATION, recstt>; 
     // abstract (by definition of statement class)
    template<recurring_statement recstt>
    using primitive_statement = statement<statement_env::DEFINITION, recstt>;
     // abstract (by definition of statement class)
    template<recurring_statement recstt>
    using collective_statement = statement<statement_env::COLLECTIVE, recstt>;

    /**
     * Concrete class
     * Node of the AST representing a dataflow declarations in any context.
     * Only treating generic dataflows, other kinds of variables 
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type, statement_env>
    class dataflow_declaration;
    
    /**
     * Concrete class
     * Node of the AST representing a dataflow assignements in any context
     * Only treating generic dataflows, other kinds of variables 
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type, statement_env>
    class dataflow_assignment;
    
    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements 
     * that compose the code executed when the condition of an if_statement 
     * is evaluated as true
     */
    template<statement_env>
    class if_section;
    
    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements 
     * that compose the code executed when the condition of an if_else_statement 
     * is evaluated as false
     */
    template<statement_env>
    class else_section;
    
    /**
     * Concrete class
     * Node of the AST that represents an if statement.
     * if (bool rvalue) { if_section }
     */
    template<statement_env>
    class if_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents an if_else statement
     * if (bool rvalue) { if_section } else { else_section }
     */
    template<statement_env>
    class if_else_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * Generic version only suitable for iterating over dataflow
     * variables
     */
    template<statement_env, dataflow_type>
    class foreach_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * System specific version only suitable for iterating
     * over components variables (logical, physical or objects)
     */
    template<block_type>
    class block_foreach_statement;
    
    /**
     * Abstract class 
     * Node of the AST modeling an element that produces a dataflow that 
     * can be eaten by another component in system section
     */
    template<dataflow_kind, dataflow_type>
    class feeder;
    
    /**
     * Concrete class
     * Node of the AST that represents the declaration
     * of a component variable (object, physical or logical)
     */
    template<block_type>
    class block_declaration;
    
    /**
     * Concrete class
     * Node of the AST that represents some concept that is not
     * theoretically gounded yet.
     * Work in progress, do not use.
     */
    class implements_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a channel output of a component to a channel input
     * of another component.
     * Such statement should assert that :
     * - channel types are compatibles
     * - connected channels inputs and outputs are not already
     *   connected
     */
    class channel_plugging;
    
    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a component dataflow output to a component dataflow
     * parameter.
     * Such statement should assert that
     * connected inputs and outputs are not already connected
     * (unless a collective_cast node is used)
     */
    template<dataflow_kind, dataflow_type>
    class feeding_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents the physical
     * dependency of two objects or of a node to a physical block
     * using the following syntax :
     * link linkable to support;
     */
    class linking_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents the implementation
     * of a contextual variable by another contextual variable
     * or of a channel by another channel.
     * Work in progress, do not use 
     */
    template <node_element ne>
    class aliasing_statement;
    
    /**
     * Concrete class
     * Node of the AST that represents the declaration 
     * of a contextual or of a channel in a with section
     */
    template <node_element>
    class node_element_declaration;
    
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////// PARAMETER DEFINITIONS MANAGEMENT //////////////////
    ////////////////////////////////////////////////////////////////

    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * functional block definition.
     */
    template<dataflow_kind, dataflow_type>
    class function_parameter;
    
    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * collective primitive definition.
     */
    template<dataflow_type>
    class collective_parameter;

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    /////////////// OUTPUT DEFINITIONS MANAGEMENT //////////////////
    ////////////////////////////////////////////////////////////////
    
    /**
     * Concrete class
     * Node of the AST that represents one output 
     * of a functional block.
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class function_output;
    
    /**
     * Abstract class
     * Node of the AST that represents one output 
     * of a collective primitive defintion.
     */
    template<collective_output_kind>
    class collective_output;
    
    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive that has no associated channel
     */
    class default_output;
    
    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive associated to the parameter
     * of the functional block that is hosting the partial 
     * collective primitive. 
     */
    class target_output;
    
    /**
     * Concrete class
     * Node of the AST that represents the output of
     * a collective primitive associated channel
     */
    class channeled_output;
    

    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////// DEFINITIONS MANAGEMENT //////////////////////
    ////////////////////////////////////////////////////////////////

    /**
     * Abstract class
     * Node of the AST that represents an element of
     * the preamble section of a Chips program
     */
    class definition;
    
    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define node specific informations
     * (contextual variables and channels)
     */
    class with_section;
    
    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define and initialize a functional 
     * block stateful information (mainly inner variables)
     */
    class init_section;
    
    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to make a functional block state evolve 
     * according to its current state and its input parameters.
     */
    class then_section;
    
    /**
     * Concrete class
     * Node of the AST that represents the list of
     * statements that can be used define how an accumulated 
     * data can be propagated/aggregated among a set of
     * interconnected components
     */
    class collectiveops_section;
    
    /**
     * Concrete class
     * Node of the AST that represents the set of collective parameters
     * that compose the data accumulated by the associate collective
     * primitive.
     */
    class accumulator_definition;
    
    /**
     * Abstract class
     * Node of the AST that represents a Chips Node
     * (i.e. an Object or a Physical function)
     */
    class node_definition;
    
    /**
     * Concrete class
     * Node of the AST that represents an Node with no
     * additional features
     * (a location in space that can be connected 
     * to other spaces thank to channels)
     */
    class object_definition;
    
    /**
     * Abstract class
     * Node of the AST that represents a functional
     * block (i.e. something that has an "init" and a "then" section)
     */
    class function_definition;
    
    /**
     * Concrete class
     * Node of the AST that represents a functional 
     * block with no additional features
     */
    class logical_definition;
    
    
    /**
     * Concrete class
     * Node of the AST that represents a Chips model element
     * that acts both as a Node (a location in space that can be connected 
     * to other spaces thank to channels) and as a Functional block 
     * (i.e. something that has an "init" and a "then" section)
     */
    class physical_definition;
    
    /**
     * Concrete class
     * Node of the AST that represents the fact a
     * node can act as another node of the model
     * Maybe to be futurely renamed as "Refinement"
     * Work in progress, do not use
     */
    class implementation_defintion;
    
    /**
     * Concrete class
     * Node of the AST that represents the definition of a collective
     * primitive, it can be refered to in the system section using the
     * collective_cast node
     */
    class collective_function_definition;
    
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////
    //////////////////// L/R/XVALUES MANAGEMENT ////////////////////
    ////////////////////////////////////////////////////////////////

    /**
     * Abstract class
     * Node of the AST that represents something to 
     * be put on the left side of an assignment
     */
    template<dataflow_type dft, expression_env sttenv>
    class lvalue;
    
    /**
     * Abstract class
     * Node of the AST that represents something to 
     * that can be evaluated as a chips primitive value
     */
    template<dataflow_type dft, expression_env expenv>
    class rvalue;
    
    /**
     * Interface
     * Node of the AST that represents something 
     * that can be iterated on in the system section
     */
    class system_iterable{};
    
    /**
     * Concrete class
     * Node of the AST that represents a hard coded
     * value (any type or code section)
     */
    template<dataflow_type dft, expression_env expenv>
    class direct;
    
    /**
     * Concrete class
     * Node of the AST that represents a pure function call
     * As the language doesn't allow to define them yet, its
     * only purpose is to provide access to a limited set of
     * predefined functions with the following signatures :
     * - int[] range(int)
     * - int[] zeros(int)
     * - int[] ones(int)
     * - float random()
     * - bool is_fresh(dataflow_variable)
     */
    template<dataflow_type dft, expression_env expenv>
    class function;
    
    /**
     * Concret class
     * Node of the AST that represents + (plus) operator
     */
    template<dataflow_type dft, expression_env expenv>
    class plus;
    
    /**
     * Concrete class
     * Node of the AST that represents - (minus) operator
     */
    template<dataflow_type dft, expression_env expenv>
    class minus;
    
    /**
     * Concrete class
     * Node of the AST that represents * (multiplication) operator
     */
    template<dataflow_type dft, expression_env expenv>
    class mult;
    
    /**
     * Concrete class
     * Node of the AST that represents / (division) operator
     */
    template<dataflow_type dft, expression_env expenv>
    class div;
    
    /**
     * Concrete class
     * Node of the AST that represents % (modulo) operator
     */
    template<expression_env expenv>
    class mod;
    
    /**
     * Concrete class
     * Node of the AST that represents the type casting operation
     */
    template<dataflow_type dft, expression_env expenv>
    class cast_as;
    
    /**
     * Concrete class
     * Node of the AST that represents > (greater than) operator
     */
    template<expression_env expenv, dataflow_type dft>
    class gt;
    
    /**
     * Concrete class
     * Node of the AST that represents < (lower than) operator
     */
    template<expression_env expenv, dataflow_type dft>
    class lt;
    
    /**
     * Concrete class
     * Node of the AST that represents the >= (greater or equal) operator
     */
    template<expression_env expenv, dataflow_type dft>
    class geq;
    
    /**
     * Concrete class
     * Node of the AST that represents <= (lower or equal) operator
     */
    template<expression_env expenv, dataflow_type dft>
    class leq;
    
    /**
     * Concrete class
     * Node of the AST that represents || (or) operator
     */
    template<expression_env expenv>
    class or_operator;
    
    /**
     * Concrete class
     * Node of the AST that represents && (and) operator
     */
    template<expression_env expenv>
    class and_operator;
    
    /**
     * Concrete class
     * Node of the AST that represents ! (not) operator
     */
    template<expression_env expenv>
    class not_operator;
    
    /**
     * Concrete class
     * Node of the AST that represents ==
     */
    template<dataflow_type dft,expression_env expenv>
    class eq;
    
    /**
     * Concrete class
     * Node of the AST that represents != (not equal) operator
     */
    template<dataflow_type dft,expression_env expenv>
    class neq;
    
    /**
     * Concrete class
     * Node of the AST that represents an expression 
     * referencing a dataflow variable
     */
    template<dataflow_type dft, expression_env expenv>
    class variable_expression;
    
    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can provide a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract;
    
    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can consume a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract;
    
    /**
     * Interface
     * Node of the AST that represents something that
     * can be linked to another Chips Node
     */
    class linkable{};
    
    /**
     * Interface
     * Node of the AST that represents something that
     * can support another Chips Object
     */
    class support{};
    
    /**
     * Interface
     * Node of the AST that represents the reference to the way
     * some node can implement another node. 
     * Will maybe be renamed as "refinement_plan" or something like
     * that in future versions of Chips.
     * Work in progress, do not use.
     */
    class interface{};
    
    /**
     * Interface
     * Node of the AST that represents the reference to a node that
     * implements another node interface.
     * Will maybe be renamed as "refiner" or something like
     * that in future versions of Chips.
     * Work in progress, do not use.
     */
    class implementer{};
    
    /**
     * Abstract class
     * Node of the AST that represents a reference 
     * to a Chips Node (Physical or Object) 
     */
    class node_variable_expression;
    
    /**
     * Abstract class
     * Base tamplate class for system component variable elements
     * logical, physical or object
     */
    template<block_type bt>
    class system_variable_block_expression;
    
    /**
     * Concrete class
     * Node of the AST that represents a component that
     * can eat a dataflow produced by something else
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater;
    
    /**
     * Concrete class
     * Expression that can produce a dataflow eaten by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression;
    
    /**
     * Concrete class
     * Node of the AST that represents a channel input
     * of a Chips Node (Physical of Object)
     */
    class channel_eater;
    
    /**
     * Concrete class
     * Node of the AST that represents a channel output
     * of a Chips Node (Physical of Object)
     */
    class channel_feeder;
    
    /**
     * Concrete class
     * Node of the AST that represents dataflow to
     * be spread or collected among many Chips Nodes
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast;
    

}
#endif