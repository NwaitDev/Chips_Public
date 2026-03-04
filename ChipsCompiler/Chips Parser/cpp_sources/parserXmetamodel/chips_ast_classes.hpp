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
#include <vector>
#include <memory>
#include <variant>

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
        private:
            int line;
            int column;

        public:
            virtual ~ast_node() = default;
            virtual void accept(visitor& v) = 0;
            virtual void hello() = 0;

            int get_line() { return line; }
            int get_column() { return column; }
            void set_line(int l) { line = l; }
            void set_column(int c) { column = c; }
    };
    


    //////////////// VERY BROAD CONCEPTS FOR CHIPS SPECIFIC AST //////////////
    class program_node;// : public ast_node{}; // concrete
    class preamble_section_node;// : public ast_node{}; // concrete
    class system_section_node;// : public ast_node{}; // concrete


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

    class primitive_variable : public variable<chips::expression_env::PRIMITIVE>{}; // abstract
    template<dataflow_type dft> 
    class dataflow_primitive_variable : public primitive_variable{}; // concrete

    class node_variable : public variable<chips::expression_env::PRIMITIVE>{}; // abstract
    template<dataflow_type dft> 
    class contextual_variable : public node_variable{}; // concrete

    class collective_variable : public variable<chips::expression_env::COLLECTIVE>{}; // abstract
    template<dataflow_type dft> 
    class dataflow_collective_variable{}; // concrete


    class system_variable : public variable<chips::expression_env::SYSTEM>{}; // abstract
    template<block_type bt> 
    class block_variable : public system_variable{}; // concrete
    template<dataflow_type dft> 
    class dataflow_system_variable : public system_variable{}; // concrete

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
    using system_statement = statement<statement_env::SYSTEM, recstt>; // abstract (by definition)

    // Variant to hold any system statement type (needed because system_statement is a template alias)
    using system_statement_variant = std::variant<
        system_statement<recurring_statement::IF>*,
        system_statement<recurring_statement::FOREACH>*,
        system_statement<recurring_statement::DECLARATION>*,
        system_statement<recurring_statement::ASSIGNMENT>*,
        system_statement<recurring_statement::IMPLEMENTS>*,
        system_statement<recurring_statement::PLUGGING>*,
        system_statement<recurring_statement::FEEDING>*,
        system_statement<recurring_statement::LINKING>*
    >;

    template<recurring_statement recstt>
    using node_statement = statement<statement_env::NODE, recstt>; // abstract (by definition)
    template<recurring_statement recstt>
    using implementation_statement = statement<statement_env::IMPLEMENTATION, recstt>; // abstract (by definition)
    template<recurring_statement recstt>
    using primitive_statement = statement<statement_env::DEFINITION, recstt>; // abstract (by definition)
    template<recurring_statement recstt>
    using collective_statement = statement<statement_env::COLLECTIVE, recstt>; // abstract (by definition)


    ////// Generic statements
    template<dataflow_type dft, statement_env stenv>
    class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION>{}; // concrete
    template<dataflow_type dft, statement_env stenv>
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT>{}; // concrete

    template<statement_env stenv>
    class if_statement : public statement<stenv,recurring_statement::IF>{}; // concrete
    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv>{}; // concrete
    template<statement_env stenv>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH>{}; // concrete
    template<statement_env stenv>
    class if_section{}; // concrete
    template<statement_env stenv>
    class else_section{}; // concrete

    ////// System specific statements
    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM , recurring_statement::DECLARATION>{}; // concrete

    class implements_statement : public system_statement<recurring_statement::IMPLEMENTS>{}; // concrete (work in progress, do not use)

    class channel_plugging : public system_statement<recurring_statement::PLUGGING>{}; // concrete

    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public system_statement<recurring_statement::FEEDING>{}; // concrete

    class linking_statement : public system_statement<recurring_statement::LINKING>{}; // concrete

    ////// Implementation specific statements (work in progress, do not use)

    template <node_element ne>
    class aliasing_statement : public implementation_statement<recurring_statement::ALIASING>{}; // concrete

    ////// Node specific statements
    template<node_element ne>
    class node_element_declaration : public node_statement<recurring_statement::DECLARATION>{}; // concrete

    ////////////////////////// DEFINITION PARAMETERS MANAGEMENT ///////////////////////////////

    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter;// : public ast_node{}; // concrete
    
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
    class function_output;// : public ast_node{}; // concrete
    
    template<enum collective_output_kind>
    class collective_output;// : public ast_node{}; // concrete


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

    using node_statement_variant = std::variant<
        node_statement<recurring_statement::IF>*,
        node_statement<recurring_statement::FOREACH>*,
        node_element_declaration<node_element::CHANNEL>*,
        node_element_declaration<node_element::CONTEXTUAL_INT>*,
        node_element_declaration<node_element::CONTEXTUAL_FLOAT>*,
        node_element_declaration<node_element::CONTEXTUAL_BOOL>*,
        node_statement<recurring_statement::DECLARATION>*, // this one is for regular variable declarations
        node_statement<recurring_statement::ASSIGNMENT>*>;

    class with_section;/* : public ast_node // concrete
    {
    private:
        std::vector<node_statement_variant> m_statements;
    };*/

    using primitive_statement_variant = std::variant<
        primitive_statement<recurring_statement::IF>*,
        primitive_statement<recurring_statement::FOREACH>*,
        primitive_statement<recurring_statement::DECLARATION>*,
        primitive_statement<recurring_statement::ASSIGNMENT>*>;
    
    class init_section : public ast_node // concrete
    {
    private:
        std::vector<primitive_statement_variant> m_statements;

        public:
            init_section() = default;

            void accept(visitor& v) override;
            void hello() override {}
    };

    class then_section : public ast_node // concrete
    {
    private:
        std::vector<primitive_statement_variant> m_statements;

        public:
            then_section() = default;

            void accept(visitor& v) override;
            void hello() override {}
    };

    using collective_statement_variant = std::variant<
        collective_statement<recurring_statement::IF>*,
        collective_statement<recurring_statement::FOREACH>*,
        collective_statement<recurring_statement::DECLARATION>*,
        collective_statement<recurring_statement::ASSIGNMENT>*>;

    class collectiveops_section; /*: public ast_node //concrete
    {
    private:
        std::vector<collective_statement_variant> m_statements;
    };*/

    using collective_parameter_variant = std::variant<
        collective_parameter<dataflow_type::INT>*,
        collective_parameter<dataflow_type::FLOAT>*,
        collective_parameter<dataflow_type::BOOL>*>;

    class accumulator_definition;/* : public ast_node // concrete
    {
    private:
        std::vector<collective_parameter_variant> m_accumulator;
    };*/


    class node_definition;/* : public definition // abstract
    {
    private:
        with_section with;
    };*/

    class object_definition;// : public node_definition {}; // concrete



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
    protected:
        std::unique_ptr<init_section> m_init;
        std::unique_ptr<then_section> m_then;
        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;
    
    public:
        // Constructor to be called by child classes
        function_definition(std::vector<function_parameter_variant> parameters,
                           std::vector<function_output_variant> outputs,
                           std::unique_ptr<init_section> init,
                           std::unique_ptr<then_section> then)
            : m_parameters(std::move(parameters)),
              m_outputs(std::move(outputs)),
              m_init(std::move(init)),
              m_then(std::move(then)) {}

        // Default constructor
        function_definition() = default;

        // Accessors
        const std::vector<function_parameter_variant>& get_parameters() const { return m_parameters; }
        const std::vector<function_output_variant>& get_outputs() const { return m_outputs; }
        init_section* get_init() const { return m_init.get(); }
        then_section* get_then() const { return m_then.get(); }
    };
    
    class logical_definition;// : public function_definition{}; // concrete

    using physical_parameter_variant = std::variant<
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;
    
    using physical_output_variant = std::variant<
        function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;

    class physical_definition;/* : public function_definition, public node_definition // concrete
    {
    private:
        std::vector<physical_parameter_variant> m_sensor;
        std::vector<physical_output_variant> m_actuator;
    };*/

    using implementation_statement_variant = std::variant<
        aliasing_statement<node_element::CHANNEL>*,
        aliasing_statement<node_element::CONTEXTUAL_BOOL>*,
        aliasing_statement<node_element::CONTEXTUAL_INT>*,
        aliasing_statement<node_element::CONTEXTUAL_FLOAT>*>;
    
    class implementation_defintion;/* : public definition // concrete
    {
    private:
        object_definition& m_implemented_object;
        node_definition& m_implementing_node;
        std::vector<implementation_statement_variant> m_having_statements;
    };*/

    class collective_function_definition;/* : public definition // concrete
    {
    private:
        collective_function_type m_collective_function_type;
        accumulator_definition m_accumulator;
        node_definition& m_support_object;
        collectiveops_section m_operations;
        collective_output<collective_output_kind::TARGET> m_target_output;
        std::optional<collective_output<collective_output_kind::DEFAULTED>> m_default_output;
        std::vector<collective_output<collective_output_kind::CHANNELED>> m_channeled_outputs;
    };*/

    ///////////////////////// LVALUES MANAGEMENT ///////////////////////////////////

    template<dataflow_type dft, expression_env sttenv>
    class lvalue : public ast_node{}; // abstract

    ///////////////////////// RVALUES MANAGEMENT //////////////////////////////////

    template<dataflow_type dft, expression_env sttenv>
    class rvalue : public ast_node{}; // abstract

    // forward declaration // mainly used in system specific ast nodes
    class system_iterable;

    // Primary template for direct values
    template<dataflow_type DFT>
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
    class function;/* : public rvalue<dft,expenv>, system_iterable //concrete
    {
    private:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;
    };*/

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
    class gt;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };*/

    template<expression_env expenv>
    class lt;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };*/

    template<expression_env expenv>
    class geq;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };*/

    template<expression_env expenv>
    class leq;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };*/

    ////////////// Bool operands operator nodes

    template<expression_env expenv>
    class or_operator;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };*/

    template<expression_env expenv>
    class and_operator;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };*/

    template<expression_env expenv>
    class not_operator;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> operand;
    };*/

    ////////////// Any dataflow operator nodes

    template<dataflow_type dft,expression_env expenv>
    class eq;/* : public rvalue<dataflow_type::BOOL ,expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };*/

    template<dataflow_type dft,expression_env expenv>
    class neq;/* : public rvalue<dataflow_type::BOOL , expenv> // concrete
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };*/



    ///////////////////////////////// XVALUES MANAGEMENT ///////////////////////////

    template<dataflow_type dft, expression_env expenv>
    class variable_expression;/* : rvalue<dft,expenv>, lvalue<dft,expenv> // concrete
    {
    private:
        variable<expenv>& variable;
        rvalue<dataflow_type::INT,expenv> index;
    };*/



    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    class program_node : public ast_node
    {
        std::string m_filename;
        std::unique_ptr<preamble_section_node> m_preamble;
        std::unique_ptr<system_section_node> m_system;

    public:
        program_node(std::string filename, 
                     std::unique_ptr<preamble_section_node> preamble, 
                     std::unique_ptr<system_section_node> system)
            : m_filename(std::move(filename)), 
              m_preamble(std::move(preamble)), 
              m_system(std::move(system)) {}

        std::string get_filename() { return m_filename; }
        preamble_section_node* get_preamble() { return m_preamble.get(); }
        system_section_node* get_system() { return m_system.get(); }

        void accept(visitor& visitor) override;

        virtual void hello() override;
    };

    class preamble_section_node : public ast_node {
        private:
            std::vector<std::unique_ptr<definition>> definitions;

        public:
            preamble_section_node() = default;

            void append(std::unique_ptr<definition> def){
                definitions.insert(definitions.begin(), std::move(def));
            }            

            const std::vector<std::unique_ptr<definition>>& get_definitions() const { return definitions; }

            void accept(visitor& visitor) override; 

            virtual void hello() override;
    };

    class system_section_node : public ast_node {
        private:
            std::vector<system_statement_variant> statements;

        public:
            system_section_node() = default;

            template<recurring_statement recstt>
            void append(system_statement<recstt>& stmt){
                statements.insert(statements.begin(), &stmt);
            }

            std::vector<system_statement_variant> get_statements() { return statements; }

            void accept(visitor& visitor) override;

            virtual void hello() override;
    };

    class visitor{
    public:
        virtual void visit(ast_node &node) = 0;

        // === PROGRAM & CONTEXT ===
        virtual void visit(program_node& node) = 0;
        virtual void visit(preamble_section_node& node) = 0;
        virtual void visit(system_section_node& node) = 0;


        // === DEFINITIONS ===
        virtual void visit(definition& node) = 0;
        virtual void visit(function_definition& node) = 0;
        virtual void visit(logical_definition& node) = 0;


        // === WITH / SECTIONS ===
        virtual void visit(init_section& node) = 0;
        virtual void visit(then_section& node) = 0;

        virtual void visit(function_output_variant& node) = 0;

        // === DATAFLOW TYPES & PARAMETERS ===
        virtual void visit(function_parameter_variant& node) = 0;
    };
}

#endif