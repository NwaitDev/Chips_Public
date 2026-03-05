#ifndef ASTMETAMODEL_H
#define ASTMETAMODEL_H
#include <cstddef>
#include <variant>
#include <vector>
#include <functional>
#include <type_traits>
#include <optional>
#include <string>
#include <iostream>

namespace chips
{
    /**
     * Components that can be plugged in system section
     */ 
    enum class block_type {
        LOGICAL, // only using regular in/outputs
        PHYSICAL, // can use regular in/outputs, sensor/actuators and channel in/outputs
        OBJECT // can only be plugged to other objects with channel in/outputs
    };

    /** 
     * Types of the elements that can appear in the preamble section
     */
    enum class definition_type {
        NODE, // to define objects and physicals
        FUNCTION, // to define logical and physicals
        IMPLEMENTATION // to define node inheritance (work in progress, do not use)
    };

    /**
     * Environments for the interpretation 
     * of direct values and variables
     */
    enum class expression_env {
        PRIMITIVE, // each value is interpreted as a regular variable
        COLLECTIVE, // each value can be interpreted as either a value of its type or a "NULL" (stop value)
        SYSTEM // each value is interpreted as a regular variable until it is plugged. Then, it represents a constant dataflow
    };

    /**
     * Primitive types of data that Chips handles
     */
    enum class dataflow_type {
        INT, // regular integers
        FLOAT, // floating point values
        BOOL // booleans
    };

    /**
     * Kind of signals to be distinguished when working with Cyber Physical Systems
     */
    enum class dataflow_kind {
        LOGICAL, // produced by any functional block or system variable
        PHYSICAL // specific to physical functional blocks
    };

    /**
     * Node specific variable kinds
     */
    enum class node_element {
        CHANNEL, // communication port to refer to when transmitting a signal between nodes
        // variable shared by all the functional blocks supported by a node
        CONTEXTUAL_INT,
        CONTEXTUAL_FLOAT,
        CONTEXTUAL_BOOL
    };

    //////////////// GENERIC ELEMENTS FOR AST MANAGMENT /////////////////////
    class visitor;
    class ast_node{
    public:
        void hello();
        void accept(visitor& v);
    };
    class visitor{
    public:
        void visit(ast_node &node);
    };


    //////////////// VERY BROAD CONCEPTS FOR CHIPS SPECIFIC AST //////////////
    class program_node : public ast_node{}; // concrete
    class preamble_section_node : public ast_node{}; // concrete
    class system_section_node : public ast_node{}; // concrete


    //////////////// VARIABLE CONCEPTS //////////////////////
    // In chips, each variable is considered as a (dynamic) array.
    // By default, variables are arrays of dimension 1.
    // When declared with a [integer expression]+ suffix,
    // it is of the given dimension(s).

    template<expression_env expenv> 
    class array : public ast_node{}; // concrete
    template<expression_env expenv>
    class variable : public array<expenv>{}; // abstract


    //////////////////// VARIABLE AST NODES ////////////////////////

    template<dataflow_type dft>
    struct ChipsTypeToContextualDeclarationType;

    /////// All dataflow types specializations

    template<>
    struct ChipsTypeToContextualDeclarationType<dataflow_type::INT>{
        using type = node_element_declaration<node_element::CONTEXTUAL_INT>;
    };

    struct ChipsTypeToContextualDeclarationType<dataflow_type::FLOAT>{
        using type = node_element_declaration<node_element::CONTEXTUAL_FLOAT>;
    };

    struct ChipsTypeToContextualDeclarationType<dataflow_type::BOOL>{
        using type = node_element_declaration<node_element::CONTEXTUAL_BOOL>;
    };

    template<dataflow_type dft, statement_env sttenv>
    class dataflow_declaration;

    class primitive_variable : public variable<chips::expression_env::PRIMITIVE>{}; // abstract
    template<dataflow_type dft> 
    class dataflow_primitive_variable : public primitive_variable  // concrete
    {
    private:
        dataflow_declaration<dft,statement_env::DEFINITION>& m_declaration;
    };

    class node_variable : public variable<chips::expression_env::PRIMITIVE>{}; // abstract
    template<dataflow_type dft> 
    class contextual_variable : public node_variable // concrete
    {
    private:
        using node_element_declaration_type = typename ChipsTypeToContextualDeclarationType<dft>::type;
        node_element_declaration_type& m_declaration;
    };

    class collective_variable : public variable<chips::expression_env::COLLECTIVE>{}; // abstract
    template<dataflow_type dft> 
    class dataflow_collective_variable : public collective_variable// concrete
    {
    private:
        dataflow_declaration<dft,statement_env::COLLECTIVE>& m_declaration;
    };


    class system_variable : public variable<chips::expression_env::SYSTEM>{}; // abstract
    
    template<block_type bt> 
    class block_variable : public system_variable // concrete
    {
    private:
        block_declaration<bt>& m_declaration;
    };
    
    template<dataflow_type dft> 
    class dataflow_system_variable : public system_variable // concrete
    {
    private:
        dataflow_declaration<dft,statement_env::SYSTEM>& m_declaration;
    };

    ////////////////// STATEMENTS MANAGEMENT ////////////////////////

    /**
     * Statements that are encountered in different environments
     */
    enum class recurring_statement {
        // generic statements
        IF, // if ( bool expr ){ statements } [ else { statements } ]
        FOREACH, // for variable in iterable { statements }
        DECLARATION, // type identifier
        ASSIGNMENT, // identifier = expression
        // system specific statements
        IMPLEMENTS, // identifier implements identifier using identifier
        PLUGGING, // identifier.identifier(identifier.identifier)
        FEEDING, // identifier.identifier(expression | identifier.identifier)
        LINKING, // link identifier to identifier
        // implementation specific statements
        ALIASING // specific to implementation section (work in progress, do not use)
    };

    /**
     * Environments that should allow to distinguish
     * the kind of statements that can be used in the code
     */
    enum class statement_env {
        DEFINITION, // in the body of function definitions (init/then sections)
        COLLECTIVE, // in the body of collective primitive definitions
        SYSTEM, // in the system description
        IMPLEMENTATION, // in the body of node implementation definition (work in progress, do not use)
        NODE // in the body of a node definitions (with sections)
    };


    template<statement_env sttenv, recurring_statement recstt>
    class statement : public ast_node{}; // abstract class

    template<recurring_statement recstt>
    using system_statement = statement<statement_env::SYSTEM, recstt>{}; // abstract (by definition)
    template<recurring_statement recstt>
    using node_statement = statement<statement_env::NODE, recstt>{}; // abstract (by definition)
    template<recurring_statement recstt>
    using implementation_statement = statement<statement_env::IMPLEMENTATION, recstt>{}; // abstract (by definition)
    template<recurring_statement recstt>
    using primitive_statement = statement<statement_env::DEFINITION, recstt>{}; // abstract (by definition)
    template<recurring_statement recstt>
    using collective_statement = statement<statement_env::COLLECTIVE, recstt>{}; // abstract (by definition)


    template<dataflow_type dft, statement_env sttenv>
    struct ChipsEnvToVariableKind;

    /////// All dataflow types specializations

    template<dataflow_type dft>
    struct ChipsEnvToVariableKind<dft,statement_env::DEFINITION>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct ChipsEnvToVariableKind<dft,statement_env::COLLECTIVE>{
        using type = dataflow_collective_variable<dft>;
    };

    // work in progress, do not use
    template<dataflow_type dft>
    struct ChipsEnvToVariableKind<dft,statement_env::IMPLEMENTATION>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct ChipsEnvToVariableKind<dft,statement_env::NODE>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct ChipsEnvToVariableKind<dft,statement_env::SYSTEM>{
        using type = dataflow_primitive_variable<dft>;
    };
    
    //////////////////////////////////////////////////////////////////////

    template<statement_env sttenv>
    struct ChipsEnvToExpressionEnv;

    /////// All evironment types specializations

    template<>
    struct ChipsEnvToExpressionEnv<statement_env::DEFINITION>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct ChipsEnvToExpressionEnv<statement_env::COLLECTIVE>{
        static constexpr expression_env value = expression_env::COLLECTIVE;
    };

    // work in progress, do not use
    template<>
    struct ChipsEnvToExpressionEnv<statement_env::IMPLEMENTATION>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct ChipsEnvToExpressionEnv<statement_env::NODE>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct ChipsEnvToExpressionEnv<statement_env::SYSTEM>{
        static constexpr expression_env value = expression_env::SYSTEM;
    };

    ////// Generic statements

    /**
     * Generic type for the nodes representing a dataflow declarations in any context
     * Only treating generic dataflows, other kinds of variables 
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION>  // concrete
    {
        private:
        using df_variable_type = typename ChipsEnvToVariableKind<dft,stenv>::type;
        df_variable_type m_variable;
    };

    /**
     * Generic type for the nodes representing a dataflow assignements in any context
     * Only treating generic dataflows, other kinds of variables 
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT> // concrete
    {
    private:
        static constexpr expression_env expr_env = ChipsEnvToExpressionEnv<stenv>::value;
        lvalue<dft, expr_env> m_lvalue;
        rvalue<dft, expr_env> m_rvalue;
    };



    template<statement_env>
    struct ChipsStatementEnvToStatementVariant{};

    using node_statement_variant = std::variant<
        node_statement<recurring_statement::IF>*,
        node_statement<recurring_statement::FOREACH>*,
        node_element_declaration<node_element::CHANNEL>*,
        node_element_declaration<node_element::CONTEXTUAL_INT>*,
        node_element_declaration<node_element::CONTEXTUAL_FLOAT>*,
        node_element_declaration<node_element::CONTEXTUAL_BOOL>*,
        node_statement<recurring_statement::DECLARATION>*, // this one is for regular variable declarations
        node_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct ChipsStatementEnvToStatementVariant<statement_env::NODE>{
        using type = node_statement_variant;
    };

    using primitive_statement_variant = std::variant<
        primitive_statement<recurring_statement::IF>*,
        primitive_statement<recurring_statement::FOREACH>*,
        primitive_statement<recurring_statement::DECLARATION>*,
        primitive_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct ChipsStatementEnvToStatementVariant<statement_env::DEFINITION>{
        using type = primitive_statement_variant;
    };

    using collective_statement_variant = std::variant<
        collective_statement<recurring_statement::IF>*,
        collective_statement<recurring_statement::FOREACH>*,
        collective_statement<recurring_statement::DECLARATION>*,
        collective_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct ChipsStatementEnvToStatementVariant<statement_env::COLLECTIVE>{
        using type = collective_statement_variant;
    };

    using system_statement_variant = std::variant<
        system_statement<recurring_statement::IF>*,
        system_statement<recurring_statement::FOREACH>*,
        system_statement<recurring_statement::DECLARATION>*, // this one is for regular variable declarations
        system_statement<recurring_statement::IMPLEMENTS>*, // work in progress, do not use
        system_statement<recurring_statement::FEEDING>*,
        system_statement<recurring_statement::LINKING>*,
        system_statement<recurring_statement::PLUGGING>*,
        system_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct ChipsStatementEnvToStatementVariant<statement_env::COLLECTIVE>{
        using type = collective_statement_variant;
    };

    // do not use, work in progress
    using implementation_statement_variant = std::variant<
        aliasing_statement<node_element::CHANNEL>*,
        aliasing_statement<node_element::CONTEXTUAL_BOOL>*,
        aliasing_statement<node_element::CONTEXTUAL_INT>*,
        aliasing_statement<node_element::CONTEXTUAL_FLOAT>*>;

    template<>
    struct ChipsStatementEnvToStatementVariant<statement_env::IMPLEMENTATION>{
        using type = implementation_statement_variant;
    };
    

    template<statement_env stenv>
    class if_section : public ast_node  // concrete
    {
        using statement_type = typename ChipsStatementEnvToStatementVariant<stenv>::type;
        std::vector<statement_type> m_if_statements;
    };
    template<statement_env stenv>
    class else_section: public ast_node  // concrete
    {
        using statement_type = typename ChipsStatementEnvToStatementVariant<stenv>::type;
        std::vector<statement_type> m_else_statements;
    };

    template<statement_env stenv>
    class if_statement : public statement<stenv,recurring_statement::IF> // concrete
    {
    private:
        static constexpr expression_env expr_env = ChipsEnvToExpressionEnv<stenv>::value;
        rvalue<dataflow_type::BOOL, expr_env> m_condition;
        if_section<stenv> m_if_section;
    };

    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv> // concrete
    {
    private:
        else_section<stenv> m_else_section;
    };


    template<statement_env stenv, dataflow_type dft>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH>  // concrete (but reserved to dataflows)
    {
    private:
        static constexpr expression_env expenv = ChipsEnvToExpressionEnv<stenv>::value;
        dataflow_declaration<dft,stenv> m_iterator;
        rvalue<dft,expenv>  m_iterable_expr;
        std::vector<> m_statements;
    };
    
    template<block_type bt>
    class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH> // concrete (but reserved to functional blocks and nodes)
    {
    private:
        block_declaration<bt> m_iterator;
        system_variable_block_expression<bt> m_iterable_expression;
        std::vector<system_statement_variant> m_statements;
    };

    ////// System specific statements

    /**
     * Abstract class modeling an element that produces a dataflow that 
     * can be eaten in system section
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder{}; 

    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM , recurring_statement::DECLARATION>  // concrete
    {
    private:
    };

    class implements_statement : public system_statement<recurring_statement::IMPLEMENTS>{}; // concrete (work in progress, do not use)

    template<dataflow_kind dfk, dataflow_type dft>
    class channel_plugging : public system_statement<recurring_statement::PLUGGING>  // concrete
    {
    private:
        // need to perform check on channel types
        // need to perform check on connectivity
        // (only connect channels 1-to-1, never 1-to-many or many-to-one)
        channel_eater m_eater;
        channel_feeder m_feeder;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recurring_statement::FEEDING>, public feeder<dft,dfk>  // concrete
    {
    private:
        eater<dfk,dft> m_eater;
        feeder<dfk,dft> m_feeder;
    };

    class linking_statement : public system_statement<recurring_statement::LINKING>{}; // concrete

    ////// Implementation specific statements (work in progress, do not use)

    template <node_element ne>
    class aliasing_statement : public implementation_statement<recurring_statement::ALIASING>{}; // concrete

    ////// Node specific statements
    
    template<node_element ne>
    class node_element_declaration : public node_statement<recurring_statement::DECLARATION>{}; // concrete

    ////////////////////////// DEFINITION PARAMETERS MANAGEMENT ///////////////////////////////

    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node{}; // concrete
    
    template<dataflow_type>
    class collective_parameter : public ast_node{}; // concrete

    ////////////////////////// DEFINITION OUTPUTS MANAGEMENT //////////////////////////////////

    /**
     * Different forms of output to use within the collective primitive definitions
     */
    enum collective_output_kind {
        CHANNELED,
        DEFAULTED,
        TARGET
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class function_output : public ast_node{}; // concrete
    
    template<enum collective_output_kind>
    class collective_output : public ast_node{}; // concrete


    ////////////////////////// DEFINITIONS MANAGEMENT ///////////////////////////////////////

    /**
     * Different types of collective primitives
     */
    enum collective_function_type {
        SPREAD, // generalization of the broadcast operation
        COLLECT // generalization of the merge operation
    };

    class definition : public ast_node // abstract
    {
    private:
        std::string m_name;
    };

    

    class with_section : public ast_node // concrete
    {
    private:
        std::vector<node_statement_variant> m_statements;
    };

    
    
    class init_section : public ast_node // concrete
    {
    private:
        std::vector<primitive_statement_variant> m_statements;
    };

    class then_section : public ast_node // concrete
    {
    private:
        std::vector<primitive_statement_variant> m_statements;
    };

    class collectiveops_section : public ast_node //concrete
    {
    private:
        std::vector<collective_statement_variant> m_statements;
    };

    using collective_parameter_variant = std::variant<
        collective_parameter<dataflow_type::INT>*,
        collective_parameter<dataflow_type::FLOAT>*,
        collective_parameter<dataflow_type::BOOL>*>;

    class accumulator_definition : public ast_node // concrete
    {
    private:
        std::vector<collective_parameter_variant> m_accumulator;
    };


    class node_definition : public definition // abstract
    {
    private:
        with_section with;
    };

    class object_definition : public node_definition {}; // concrete



    using function_parameter_variant = std::variant<
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::INT>*,
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;

    using function_output_variant = std::variant<
        function_output<dataflow_kind::LOGICAL, dataflow_type::INT>*,
        function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,
        function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;
        
    class function_definition : public definition // abstract
    {
    private:
        init_section init;
        then_section then;
        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;
    };
    class logical_definition : public function_definition{}; // concrete

    using physical_parameter_variant = std::variant<
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;
    
    using physical_output_variant = std::variant<
        function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;

    class physical_definition : public function_definition, public node_definition // concrete
    {
    private:
        std::vector<physical_parameter_variant> m_sensor;
        std::vector<physical_output_variant> m_actuator;
    };
    
    class implementation_defintion : public definition // concrete // do not use, work in progress
    {
    private:
        object_definition& m_implemented_object;
        node_definition& m_implementing_node;
        std::vector<implementation_statement_variant> m_having_statements;
    };

    class collective_function_definition : public definition // concrete
    {
    private:
        collective_function_type m_collective_function_type;
        accumulator_definition m_accumulator;
        node_definition& m_support_object;
        collectiveops_section m_operations;
        collective_output<collective_output_kind::TARGET> m_target_output;
        std::optional<collective_output<collective_output_kind::DEFAULTED>> m_default_output;
        std::vector<collective_output<collective_output_kind::CHANNELED>> m_channeled_outputs;
    };

    ///////////////////////// LVALUES MANAGEMENT ///////////////////////////////////

    template<dataflow_type dft, expression_env sttenv>
    class lvalue : public ast_node{}; // abstract

    ///////////////////////// RVALUES MANAGEMENT //////////////////////////////////

    template<dataflow_type dft, expression_env expenv>
    class rvalue : public ast_node{}; // abstract

    /**
     * rvalue specialization for interfacing "constexpr" in system
     * section as constant dataflow streams 
     * (syntactic sugar for additional trival logical blocks)
     */ 
    template<dataflow_type dft>
    class rvalue<dft, expression_env::SYSTEM> : public feeder<dataflow_kind::LOGICAL,dft> {}; // abstract too

    // used in system specific ast nodes
    class system_iterable{}; // interface

    // Primary template for direct values
    template<dataflow_type dft>
    struct ChipsDftToCppType;

    // Specializations
    template<>
    struct ChipsDftToCppType<dataflow_type::INT> {
        using type = int;
    };

    template<>
    struct ChipsDftToCppType<dataflow_type::FLOAT> {
        using type = double;
    };

    template<>
    struct ChipsDftToCppType<dataflow_type::BOOL> {
        using type = bool;
    };


    template<dataflow_type dft, expression_env expenv>
    class direct: public rvalue<dft,expenv> // concrete
    {
    private:
        using value_type = typename ChipsDftToCppType<dft>::type;
        value_type m_value;
    };

    //////////////////////Functions

    template<expression_env expenv>
    using rvalue_variant = std::variant<
        rvalue<dataflow_type::INT,expenv>*,
        rvalue<dataflow_type::FLOAT,expenv>*,
        rvalue<dataflow_type::BOOL,expenv>*>;

    template<dataflow_type dft, expression_env expenv>
    class function : public rvalue<dft,expenv>, system_iterable //concrete
    {
    private:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;
    };

    /////// Operators as Chips expressions

    // Primary template for operand nodes
    template<dataflow_type DFT, expression_env expenv>
    struct ChipsOperandToAstType;

    template<dataflow_type DFT, expression_env expenv>
    struct ChipsOperandToAstNumericType;

    /////// All dataflow types specializations

    template<expression_env expenv>
    struct ChipsOperandToAstType<dataflow_type::INT,expenv>{
        using type = rvalue<dataflow_type::INT,expenv>;
    };

    template<expression_env expenv>
    struct ChipsOperandToAstType<dataflow_type::FLOAT,expenv>{
        using type = rvalue<dataflow_type::FLOAT,expenv>;
    };

    template<expression_env expenv>
    struct ChipsOperandToAstType<dataflow_type::BOOL,expenv>{
        using type = rvalue<dataflow_type::BOOL,expenv>;
    };

    /////// Numeric Only dataflow types specializations

    template<expression_env expenv>
    struct ChipsOperandToAstNumericType<dataflow_type::INT,expenv>{
        using type = rvalue<dataflow_type::INT,expenv>;
    };

    template<expression_env expenv>
    struct ChipsOperandToAstNumericType<dataflow_type::FLOAT,expenv>{
        using type = rvalue<dataflow_type::FLOAT,expenv>;
    };

    ////////////// Numeric operands operator nodes

    template<dataflow_type dft, expression_env expenv>
    class plus : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class mod : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type numeric;
    };

    template<expression_env expenv>
    class gt : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv>
    class lt : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv>
    class geq : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv>
    class leq : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    ////////////// Bool operands operator nodes

    template<expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };

    template<expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };

    template<expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> operand;
    };

    ////////////// Any dataflow operator nodes

    template<dataflow_type dft,expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft,expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL , expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };



    ///////////////////////////////// XVALUES MANAGEMENT ///////////////////////////

    template<dataflow_type dft, expression_env expenv>
    class variable_expression : rvalue<dft,expenv>, lvalue<dft,expenv> // concrete
    {
    private:
        variable<expenv>& variable;
        rvalue<dataflow_type::INT,expenv> index;
    };


    /////////////////////////////// SYSTEM SECTION SPECIFIC NODES //////////////////

    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_abstract : public ast_node {}; // abstract class for feeder elements
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract : public ast_node {}; // abstract class for eater elements

    class linkable{}; // interface
    class support{}; // interface
    class interface{}; // is an interface for interface elements of models (not the regular def of interface in programming languages) // work in progress, do not use
    class implementer{}; // abstract // work in progress, do not use

    class node_variable_expression : public ast_node{}; // abstract
    

    template<block_type bt>
    struct ChipsBlockTypeToAstBlockVariable;

    template<>
    struct ChipsBlockTypeToAstBlockVariable<block_type::LOGICAL>{
        using type = block_variable<block_type::LOGICAL>;
    };

    template<>
    struct ChipsBlockTypeToAstBlockVariable<block_type::PHYSICAL>{
        using type = block_variable<block_type::PHYSICAL>;
    };

    template<>
    struct ChipsBlockTypeToAstBlockVariable<block_type::OBJECT>{
        using type = block_variable<block_type::OBJECT>;
    };

    /**
     * Base tamplate class for system block variable elements 
     */
    template<block_type bt>
    class system_variable_block_expression : public ast_node, public system_iterable
    {
    private:
        using block_type = typename ChipsBlockTypeToAstBlockVariable<bt>::type;
        block_type& m_variable;
        rvalue<dataflow_type::INT,expression_env::SYSTEM> m_index;
    };

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing LOGICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::LOGICAL> : public linkable{};

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing PHYSICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::PHYSICAL> : public support, public node_variable_expression, implementer {};

    /**
     * Template specialization of system_variable_block_expression 
     * for implementing OBJECT specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::OBJECT> 
    : public linkable, public support, public node_variable_expression, public interface, public implementer {};


    template<dataflow_type dft, dataflow_kind dfk>
    struct BlockTypeToSystemFunctionalBlockVar;

    template<dataflow_type dft>
    struct BlockTypeToSystemFunctionalBlockVar<dft, dataflow_kind::LOGICAL> {
        using type = system_variable_block_expression<block_type::LOGICAL>;
    };

    template<dataflow_type dft>
    struct BlockTypeToSystemFunctionalBlockVar<dft, dataflow_kind::PHYSICAL> {
        using type = system_variable_block_expression<block_type::PHYSICAL>;
    };


    /**
     * Expression that can eat a dataflow produced by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater // concrete
    {
    private:
        using sys_variable_expression = typename BlockTypeToSystemFunctionalBlockVar<dft,dfk>::type;
        sys_variable_expression m_variable_expression;
        function_parameter<dfk,dft>& m_parameter;
    }; 

    /**
     * Expression that can produce a dataflow eaten by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>, public ast_node // concrete (see feeder definition in system specific statements section)
    {
    private:
        using sys_variable_expression = typename BlockTypeToSystemFunctionalBlockVar<dft,dfk>::type;
        sys_variable_expression m_variable_expression;
        function_output<dfk,dft>& m_output;
    };


    class channel_eater : public ast_node // concrete
    {
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_eating_channel;
    };

    class channel_feeder : public ast_node // concrete
    {
        node_variable_expression m_node;
        node_element_declaration<node_element::CHANNEL>& m_eating_channel;
    };

    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft> {
    private:
        collective_function_definition& variable_expression;
        feeder m_feeder;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    class program_node : public ast_node
    {
        std::string m_filename;
        preamble_section_node& m_preamble;
        system_section_node& m_system;

    public:
        program_node(std::string filename, preamble_section_node &preamble, system_section_node &system);
    };
}

#endif