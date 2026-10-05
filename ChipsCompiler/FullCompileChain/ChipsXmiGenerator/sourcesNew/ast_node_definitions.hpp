#ifndef __chips_ast_node_definitions__
#define __chips_ast_node_definitions__

#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

#include "meta_type_conversions.hpp"
#include "metamodel_enums.hpp"
#include "forward_declarations.hpp"

namespace chips
{
    class visitor;

    /**
     * Base abstract class for a node in the Chips 
     * Abstract Syntax Tree
     */
    class ast_node
    {
        public:
        int m_line;
        int m_column;

        ast_node(int line, int column) : m_line(line), m_column(column) {}
        virtual ~ast_node() = default;

        int get_line() const { return m_line; }
        int get_column() const { return m_column; }

        virtual void accept(visitor& v) = 0;
    };

    template<dataflow_kind dfk, dataflow_type dft> class function_parameter;
    template<dataflow_kind dfk, dataflow_type dft> class function_output;

    /**
     * Abstract class
     * Node of the AST that represents an element of
     * the preamble section of a Chips program
     */
    class definition
    {
        public:
        std::string m_name;

        definition(std::string id) : m_name(id) {}

        std::string& get_name() { return m_name; }
    };

    /**
     * Abstract class
     * let the child class inherit the 
     * add_statement(typename SttEnvToSttVariant<env>::type) 
     * method
    */
    template<statement_env env>
    class statement_fillable {

        statement_fillable<env>() = delete;
        public:
        std::vector<typename SttEnvToSttVariant<env>::type> m_statements;
        inline void add_statement(const typename SttEnvToSttVariant<env>::type& stt){
            m_statements.push_back(stt);
        }

        inline std::vector<typename SttEnvToSttVariant<env>::type>& get_statements() { return m_statements; }
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define node specific informations
     * (contextual variables and channels)
     */
    class with_section : public ast_node, public statement_fillable<statement_env::NODE> {
        public:
        void accept(visitor& v){
            throw std::runtime_error("unimplemented with_section.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to define and initialize a functional 
     * block stateful information (mainly inner variables)
     */
    class init_section : public ast_node,  public statement_fillable<statement_env::DEFINITION> {
        public:
        void accept(visitor& v){
            throw std::runtime_error("unimplemented init_section.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of statements
     * that can be used to make a functional block state evolve 
     * according to its current state and its input parameters.
     */
    class then_section : public ast_node,  public statement_fillable<statement_env::DEFINITION>{
        public:
        void accept(visitor& v){
            throw std::runtime_error("unimplemented then_section.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Node of the AST that represents the list of
     * statements that can be used define how an accumulated 
     * data can be propagated/aggregated among a set of
     * interconnected components
     */
     class collectiveops_section : public ast_node, public statement_fillable<statement_env::COLLECTIVE>{
        public:
        void accept(visitor& v){
            throw std::runtime_error("unimplemented collectiveops_section.accept(visitor&) error.");
        };
     };

    /**
     * Concrete class
     * Node of the AST that represents the set of collective parameters
     * that compose the data accumulated by the associate collective
     * primitive.
     */
    class accumulator_definition : public ast_node
    {
        public:
        std::vector<collective_parameter_variant> m_accumulator;

        accumulator_definition(int line, int column, std::vector<collective_parameter_variant> accumulator)
                : ast_node(line, column), m_accumulator(accumulator){}

        std::vector<collective_parameter_variant>& get_accumulators() { return m_accumulator; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented accumulator_definition.accept(visitor&) error.");
        };

    };

    /**
     * Abstract class
     * Node of the AST that represents a Chips Node
     * (i.e. an Object or a Physical function)
     */
    class node_definition : public virtual definition
    {
        public:
        with_section m_with;
        node_definition(std::string id, with_section with) : definition(id), m_with(with) {}
    };

    /**
     * Concrete class
     * Node of the AST that represents an Node with no
     * additional features
     * (a location in space that can be connected 
     * to other spaces thank to channels)
     */
    class object_definition : public node_definition, public ast_node
    {
        public:
        object_definition(int line, int column, std::string identifier, with_section with)
            : ast_node(line,column), definition(identifier), node_definition(identifier, with){}

        void accept(visitor& v) {
            throw std::runtime_error("unimplemented object_definition.accept(visitor&) method.");
        }

    };


    /**
     * Abstract class
     * Node of the AST that represents a functional
     * block (i.e. something that has an "init" and a "then" section)
     */
    class function_definition : public virtual definition
    {
        public:
        init_section m_init;
        then_section m_then;

        std::vector<function_parameter_variant> m_parameters;
        std::vector<function_output_variant> m_outputs;
 
        function_definition(
            std::string identifier, 
            std::vector<function_parameter_variant> parameters, 
            init_section init,
            then_section then, 
            std::vector<function_output_variant> outputs)
        : definition(identifier), 
        m_init(init), 
        m_then(then), 
        m_parameters(parameters), 
        m_outputs(outputs) {}

        std::vector<function_output_variant>& get_outputs() { return m_outputs; }
        std::vector<function_parameter_variant>& get_parameters() { return m_parameters; }
        init_section& get_init_section() { return m_init; }
        then_section& get_then_section() { return m_then; }

    };

    /**
     * Concrete class
     * Node of the AST that represents a functional 
     * block with no additional features
     */
    class logical_definition : public function_definition, public ast_node {
        public:

        logical_definition(int line, int column, std::string id,
            std::vector<function_parameter_variant> parameters, 
            init_section init,
            then_section then, 
            std::vector<function_output_variant> outputs):
        ast_node(line,column), definition(id), function_definition(id,parameters, init,then, outputs) {}

        void accept(visitor& v) { 
            throw std::runtime_error("unimplemented accept method for logical_definition");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a Chips model element
     * that acts both as a Node (a location in space that can be connected 
     * to other spaces thank to channels) and as a Functional block 
     * (i.e. something that has an "init" and a "then" section)
     */
    class physical_definition : public function_definition, public ast_node , public node_definition {
        public:
        std::vector<physical_parameter_variant> m_sensors;
        std::vector<physical_output_variant> m_actuators;
 
        physical_definition(
            int line, int column, 
            std::string identifier, 
            std::vector<function_parameter_variant> parameters,
            std::vector<physical_parameter_variant> sensors,
            with_section with,
            init_section init,
            then_section then, 
            std::vector<function_output_variant> outputs,
            std::vector<physical_output_variant> actuators
        )
        : ast_node(line, column),
        definition(identifier),
        node_definition(identifier,with),
        function_definition(
            identifier, 
            parameters, 
            init, 
            then, 
            outputs
        ), m_sensors(sensors), m_actuators(actuators) {}

        void accept(visitor& v) { 
            throw std::runtime_error("unimplemented accept method for physical_definition");
        }


    };

    /**
     * Abstract class
     * Node of the AST that represents one output 
     * of a collective primitive defintion.
     */
     template<enum collective_output_kind>
     class collective_output {};
 
 
     /**
      * Concrete class
      * Node of the AST that represents the output of
      * a collective primitive associated channel
      */
     class channeled_output : public collective_output<collective_output_kind::CHANNELED>, public ast_node
     {
         public:
         node_element_declaration<node_element::CHANNEL>* m_channel;
         std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;
 
         channeled_output(int line, int column, node_element_declaration<node_element::CHANNEL>* channel,
                          std::vector<rvalue_variant<expression_env::COLLECTIVE>> accumulator_exprs)
             :ast_node(line,column), m_channel(channel), m_accumulator_expressions(accumulator_exprs){}
 
         node_element_declaration<node_element::CHANNEL>* get_channel() { return m_channel; }
         std::vector<rvalue_variant<expression_env::COLLECTIVE>> get_expressions() { return m_accumulator_expressions; }
 
         void accept(visitor& v){
             throw std::runtime_error("unimplemented channeled_output.accept(visitor&) error.");
         };
     };
 
     /**
      * Concrete class
      * Node of the AST that represents the output of
      * a collective primitive that has no associated channel
      */
     class default_output : public collective_output<collective_output_kind::DEFAULTED>, public ast_node {
         public:
         std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_accumulator_expressions;
 
         default_output(int line, int column, std::vector<rvalue_variant<expression_env::COLLECTIVE>> accumulator_exprs)
             : ast_node(line,column), m_accumulator_expressions(accumulator_exprs){}
 
         std::vector<rvalue_variant<expression_env::COLLECTIVE>> get_expressions() { return m_accumulator_expressions; }
 
         void accept(visitor& v){
             throw std::runtime_error("unimplemented default_output.accept(visitor&) error.");
         };
     };
 
     /**
      * Concrete class
      * Node of the AST that represents the output of
      * a collective primitive associated to the parameter
      * of the functional block that is hosting the partial 
      * collective primitive. 
      */
     class target_output : public collective_output<collective_output_kind::TARGET>, public ast_node
     {
         public:
         // you should only allow stopless expressions for this member attribute
         std::vector<rvalue_variant<expression_env::COLLECTIVE>> m_expressions;
 
         target_output(int line, int column, std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions)
             : ast_node(line,column), m_expressions(expressions){}
 
         std::vector<rvalue_variant<expression_env::COLLECTIVE>>& get_expressions() { return m_expressions; }
 
         void accept(visitor& v){
             throw std::runtime_error("unimplemented target_output.accept(visitor&) error.");
         };
     };

    /**
     * Concrete class
     * Node of the AST that represents the definition of a collective
     * primitive, it can be refered to in the system section using the
     * collective_cast node
     */
     class collective_function_definition : public definition, public ast_node
     {
         public:
         collective_function_type m_collective_function_type;
         accumulator_definition m_accumulator;
         node_definition* m_support_object;
         collectiveops_section m_operations;
         target_output m_target_output;
         default_output m_default_output;
         std::vector<channeled_output> m_channeled_outputs;
 
         collective_function_definition(int line, int column, std::string identifier,
                                        collective_function_type type,
                                        accumulator_definition accumulator,
                                        node_definition* support,
                                        collectiveops_section operations,
                                        target_output target,
                                        default_output default_output,
                                        std::vector<channeled_output> channeled_output)
             : ast_node(line,column), definition(identifier), m_collective_function_type(type), m_accumulator(accumulator), 
               m_support_object(support), m_operations(operations), m_target_output(target), 
               m_default_output(default_output), m_channeled_outputs(channeled_output){}
 
         collective_function_type& get_type() { return m_collective_function_type; }
         accumulator_definition& get_accumulator() { return m_accumulator; }
         node_definition* get_node_definition() { return m_support_object; }
         collectiveops_section& get_operations() { return m_operations; }
         target_output& get_target_output() { return m_target_output; }
         default_output& get_default_output() { return m_default_output; }
         std::vector<channeled_output>& get_channeled_outputs() { return m_channeled_outputs; }
 
         void accept(visitor& v) {
            throw std::runtime_error("unimplemented collective_function_definition.accept(visitor&) method.");
         }
     };

    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * functional block definition.
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class function_parameter : public ast_node
    {
    public:
        std::optional<rvalue<dft,expression_env::PRIMITIVE>> m_default_value;
        dataflow_declaration<dft,statement_env::DEFINITION> m_declaration;
        std::string m_name;

        function_parameter(
            std::string name,
            dataflow_declaration<dft,statement_env::DEFINITION> declaration,
            std::optional<rvalue<dft,expression_env::PRIMITIVE>> default_value
        )
        : m_name(name), m_declaration(declaration), m_default_value(default_value){};
        
        function_parameter(
            std::string name, 
            dataflow_declaration<dft,statement_env::DEFINITION> declaration
        )
        : m_name(name), m_declaration(declaration), m_default_value(std::nullopt){};

        const std::string& get_name() const { return m_name; }
        std::string& get_name() { return m_name; }

        std::optional<rvalue<dft,expression_env::PRIMITIVE>>& get_default_value() { return m_default_value; }

        dataflow_declaration<dft,statement_env::DEFINITION>& get_declaration() { return m_declaration; }

        void accept(visitor& v) { 
            throw std::runtime_error("unimplmeented function_parameter.accept(visitor&) method.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the definition
     * of a parameter in the parameter list of a
     * collective primitive definition.
     */
    template<dataflow_type dft>
    class collective_parameter : public ast_node
    {
        public:
        rvalue<dft,expression_env::COLLECTIVE> m_default_value;
        dataflow_declaration<dft,statement_env::COLLECTIVE> m_declaration;
        std::string m_name;

        collective_parameter(
            std::string name, 
            dataflow_declaration<dft, statement_env::COLLECTIVE> declaration,
            rvalue<dft, expression_env::COLLECTIVE>* default_value)
            : m_name(name), m_declaration(declaration), m_default_value(default_value){}

        rvalue<dft,expression_env::COLLECTIVE>& get_default_value() { return m_default_value; }
        dataflow_declaration<dft,statement_env::COLLECTIVE>& get_declaration() { return m_declaration; }
        std::string& get_name() { return m_name; }
        
        void accept(visitor& v){
            throw std::runtime_error("unimplemented collective_parameter.accept(visitor&) error.");
        };
    };
    
    /**
     * Concrete class
     * Node of the AST that represents one output 
     * of a functional block.
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class function_output : public ast_node
    {
        public:
        std::string m_name;
        // Note to the model to model transformations developer:
        // Chips 1.1 metamodel didn't cope with multiple 
        // expressions outputs though the grammar allows it... Here, we allow it too
        std::vector<rvalue_variant<expression_env::PRIMITIVE>> m_expressions = {};
        function_output(std::string name,rvalue<dft,expression_env::PRIMITIVE>* expr) : m_name(name){ m_expressions.push_back(expr);};
        
        std::string& get_name() { return m_name; }
        std::vector<rvalue_variant<expression_env::PRIMITIVE>>& get_expressions() { return m_expressions; }
        
        void accept(visitor& v){
            throw std::runtime_error("unimplemented collective_parameter.accept(visitor&) error.");
        };
    };


    /**
     * Abstract class 
     * Node of the AST modeling an element that produces a dataflow that 
     * can be eaten by another component in system section
     */
    template<dataflow_kind dfk, dataflow_type dft> class feeder {};

    /**
     * Interface
     * Node of the AST that represents something that
     * can be linked to another Chips Node
     */
    class linkable {};

    /**
     * Interface
     * Node of the AST that represents something that
     * can support another Chips Object
     */
    class support {};

    /**
     * Interface
     * Node of the AST that represents something
     * that can be iterated on in the system section
     */
    class system_iterable {};

    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can provide a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft> class feeder_abstract : public ast_node {
        public:
        feeder_abstract(int line, int column) : ast_node(line, column) {}
    };

    /**
     * Abstract class
     * Node of the AST that represents some syntactical 
     * elements that can consume a dataflow
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater_abstract : public ast_node {
        public:
        eater_abstract(int line, int column) : ast_node(line, column) {}
    };


    /**
     * Abstract class
     * Node of the AST that represents a reference 
     * to a Chips Node (Physical or Object)
     */
    class node_variable_expression {};


    /**
     * Abstract class
     * Base tamplate class for system component variable elements
     * logical, physical or object
     */
    template<block_type bt>
    class system_variable_block_expression : public system_iterable {};
    
        /**
     * Template specialization of system_variable_block_expression 
     * for implementing LOGICAL specific interfaces
     */
    template<>
    class system_variable_block_expression<block_type::LOGICAL> : public ast_node, public system_iterable, public linkable{
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::LOGICAL>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            int line, int column,
            block_variable<block_type::LOGICAL>* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            : ast_node(line, column), m_variable(var), m_index(index){}

        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>& get_index() { return m_index; }
        
        void accept(visitor& v){
            throw std::runtime_error("unimplemented logical_variable_expression.accept(visitor&) error.");
        };
    };
 
     /**
      * Template specialization of system_variable_block_expression 
      * for implementing PHYSICAL specific interfaces
      */
    template<>
    class system_variable_block_expression<block_type::PHYSICAL> : public ast_node, public system_iterable, public linkable, public support, public node_variable_expression {
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::PHYSICAL>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            int line, int column,
            block_variable_type* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            : ast_node(line, column), m_variable(var), m_index(index){}

        block_variable_type* get_variable() { return m_variable; }
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>& get_index() { return m_index; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented physical_variable_expression.accept(visitor&) error.");
        };
    };
 
     /**
      * Template specialization of system_variable_block_expression 
      * for implementing OBJECT specific interfaces
      */
    template<>
    class system_variable_block_expression<block_type::OBJECT> 
    :  public ast_node, public system_iterable, public linkable, public support, public node_variable_expression {
        public:
        using block_variable_type = typename BlockTypeToBlockVariable<block_type::OBJECT>::type;
        block_variable_type* m_variable;
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> m_index;

        system_variable_block_expression(
            int line, int column,
            block_variable<block_type::OBJECT>* var,
            std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index)
            :ast_node(line, column), m_variable(var), m_index(index){}

        block_variable_type* get_variable() { return m_variable; }
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>& get_index() { return m_index; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented object_variable_expression.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Node of the AST that represents a component that
     * can eat a dataflow produced by something else
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class eater : public ast_node
    {
        public:
        functional_block_variant m_variable_expression;
        function_parameter<dfk,dft>* m_parameter;

        eater(int line, int column, functional_block_variant variable, function_parameter<dfk,dft>* parameter)
            : ast_node(line, column), m_variable_expression(variable), m_parameter(parameter){}

        functional_block_variant& get_functional_block() { return m_variable_expression; }
        function_parameter<dfk,dft>* get_parameter() { return m_parameter;}

        void accept(visitor& v){
            throw std::runtime_error("unimplemented eater.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Expression that can produce a dataflow eaten by another component
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeder_block_expression : public feeder<dfk,dft>, public ast_node
    {
        public:
        functional_block_variant m_variable_expression;
        function_output<dfk,dft>* m_output;
        
        feeder_block_expression(int line, int column, functional_block_variant variable, function_output<dfk,dft>* output)
            : ast_node(line,column), m_variable_expression(variable), m_output(output){}
        
        void set_variable_expression(functional_block_variant variable){
            m_variable_expression = variable;
        }

        void set_output(function_output<dfk,dft>* output){
            m_output = output;
        }

        functional_block_variant& get_functional_block() { return m_variable_expression; }
        function_output<dfk,dft>* get_output() { return m_output; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented feeder_blocj_expression.accept(visitor&) error.");
        };
    };

    /**
     * Concrete class
     * Node of the AST that represents a channel input
     * of a Chips Node (Physical of Object)
     */
    class channel_eater : public ast_node
    {
        public:
        node_variable_expression* m_node;
        node_element_declaration<node_element::CHANNEL>* m_eating_channel;

        channel_eater(int line, int column, node_variable_expression* node, node_element_declaration<node_element::CHANNEL>* eating_channel)
            : ast_node(line, column), m_node(node), m_eating_channel(eating_channel){}

        node_variable_expression* get_node() { return m_node; }
        node_element_declaration<node_element::CHANNEL>* get_eating_channel() { return m_eating_channel; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented channel_eater.accept(visitor&) error.");
        };
    };
 
     /**
      * Concrete class
      * Node of the AST that represents a channel output
      * of a Chips Node (Physical of Object)
      */
    class channel_feeder : public ast_node
    {
        public:
        node_variable_expression* m_node;
        node_element_declaration<node_element::CHANNEL>* m_feeding_channel;

        channel_feeder(int line, int column, node_variable_expression* node, 
                    node_element_declaration<node_element::CHANNEL>* feeding_channel)
            : ast_node(line, column), m_node(node), m_feeding_channel(feeding_channel){}

        node_variable_expression* get_node() { return m_node; }
        node_element_declaration<node_element::CHANNEL>* get_feeding_channel() { return m_feeding_channel; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented channel_feeder.accept(visitor&) error.");
        };
    };


    /**
     * Concrete class
     * Node of the AST that represents dataflow to
     * be spread or collected among many Chips Nodes
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class collective_cast : public feeder<dfk,dft>, public ast_node {
        public:
        collective_function_definition* variable_expression;
        feeder_variant m_feeder;

        explicit collective_cast(int line, int column, collective_function_definition* variable, feeder<dfk, dataflow_type::INT>& feed)
            : ast_node(line,column), variable_expression(variable), m_feeder(&feed){}

        explicit collective_cast(int line, int column, collective_function_definition* variable, feeder<dfk, dataflow_type::FLOAT>& feed)
            : ast_node(line,column), variable_expression(variable), m_feeder(&feed){}

        explicit collective_cast(int line, int column, collective_function_definition* variable, feeder<dfk, dataflow_type::BOOL>& feed)
            : ast_node(line,column), variable_expression(variable), m_feeder(&feed){}

        collective_function_definition* get_collective_function() { return variable_expression; }

        feeder_variant& get_feeder_variant() { return m_feeder; }
        const feeder_variant& get_feeder_variant() const { return m_feeder; }

        void accept(visitor& v){
            throw std::runtime_error("unimplemented channel_feeder.accept(visitor&) error.");
        };
    };

    /**
     * Abstract class
     * Node of the AST that represents something to
     * be put on the left side of an assignment
     */
    template<dataflow_type dft, expression_env expenv> class lvalue {};

    /**
     * Abstract class
     * Node of the AST that represents something to
     * that can be evaluated as a chips primitive value
     */
    template<dataflow_type dft, expression_env expenv> class rvalue {};

    template<dataflow_type dft> class rvalue<dft, expression_env::SYSTEM> : public feeder<dataflow_kind::LOGICAL, dft> {};

    /**
     * Concrete class
     * Node of the AST that represents a hard coded
     * value (any type or code section)
     */
    template<dataflow_type dft, expression_env expenv> class direct : public rvalue<dft, expenv>, public ast_node {
        public:
        using value_type = typename DfTypeToCppType<dft>::type;
        value_type m_value;

        direct(int line, int column, value_type value) : ast_node(line,column), m_value(value) {};

        inline value_type& get_value() { return m_value; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented direct.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a pure function call
     * As the language doesn't allow to define them yet, its
     * only purpose is to provide access to a limited set of
     * predefined functions with the following signatures :
     * - int[] range(int)
     * - int[] zeros(int)
     * - int[] ones(int)
     * - float randin01()
     * - bool is_fresh(dataflow_variable)
     */
    template<dataflow_type dft, expression_env expenv> class function 
    : public rvalue<dft, expenv>, public system_iterable, public ast_node {
        public:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;

        function(int line, int column, std::string name)
            :ast_node(line, column), m_name(name){}

        function(std::string name, std::vector<rvalue_variant<expenv>> param)
            : m_name(name), m_parameters(param){}

        std::string& get_name() { return m_name; }
        std::vector<rvalue_variant<expenv>>& get_parameters() { return m_parameters; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented function.accept(visitor&) error.");
        }
    };

    /**
     * Concret class
     * Node of the AST that represents + (plus) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class plus : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        plus(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() const { return m_left_operand; }
        operand_type get_rhs() const { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented plus.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents - (minus) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        minus(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() const { return m_left_operand; }
        operand_type get_rhs() const { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented minus.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents * (multiplication) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        mult(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented mult.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents / (division) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        div(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented div.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents % (modulo) operator
    */
    template <expression_env expenv>
    class mod : public rvalue<dataflow_type::INT, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dataflow_type::INT, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        mod(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented mod.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents the type casting operation
    */
    template <dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type numeric;

    public:
        cast_as(operand_type numeric)
            : numeric((numeric)) {}

        operand_type get_cast() { return numeric; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented cast_as.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents > (greater than) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class gt : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        gt(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented gt.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents < (lower than) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class lt : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        lt(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented lt.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents the >= (greater or equal) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class geq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        geq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented geq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents <= (lower or equal) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class leq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        leq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented leq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents || (or) operator
    */
    template <expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;

    public:
        or_operator(rvalue<dataflow_type::BOOL, expenv> left_operand, rvalue<dataflow_type::BOOL, expenv> right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand; }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented or_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents && (and) operator
    */
    template <expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;

    public:
        and_operator(rvalue<dataflow_type::BOOL, expenv> left_operand, rvalue<dataflow_type::BOOL, expenv> right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand; }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented and_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents ! (not) operator
    */
    template <expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> operand;

    public:
        not_operator(rvalue<dataflow_type::BOOL, expenv> operand)
            : operand(operand) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented not_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents the unary minus operator
    */
    template <dataflow_type dft, expression_env expenv>
    class uminus_operator : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type operand;

    public:
        uminus_operator(operand_type operand)
            : operand(operand) {}

        operand_type get_rhs() { return operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented uminus_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents ==
    */
    template <dataflow_type dft, expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        eq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented eq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents != (not equal) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        neq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented neq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents an expression
    * referencing a dataflow variable
    */
    template <dataflow_type dft, expression_env expenv>
    class variable_expression : public rvalue<dft, expenv>, public lvalue<dft, expenv>, public ast_node
    {
    private:
        variable<expenv> *m_variable;
        std::vector<int_rvalue_expression_variant<expenv>> m_index = {};

    public:
        variable_expression(variable<expenv> *variable, std::vector<int_rvalue_expression_variant<expenv>> index)
            : m_variable(variable), m_index(index) {}

        variable_expression(variable<expenv> *variable)
            : m_variable(variable) {}

        variable<expenv> *get_variable() { return m_variable; }
        std::vector<int_rvalue_expression_variant<expenv>>& get_index() { return m_index; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented variable_expression.accept(visitor&) error.");
        }

    };

    template <dataflow_type dft, expression_env expenv>
    class variable_contextual_expression : public variable_expression<dft, expenv>, public ast_node
    {
    public:
        variable_contextual_expression(variable<expenv> *variable, std::vector<int_rvalue_expression_variant<expenv>> index)
            : variable_expression<dft, expenv>(variable, index) {}

        variable_contextual_expression(variable<expenv> *variable)
            : variable_expression<dft, expenv>(variable) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented variable_contextual_expression.accept(visitor&) error.");
        }
    };

    class input : public rvalue<dataflow_type::INT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>,
          public ast_node {
        
    public:
        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented input.accept(visitor&) error.");
        }
    };

    class stop
        : public rvalue<dataflow_type::INT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>,
          public ast_node {

    public:
        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented stop.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds all the definitions
     * of Chips components (Logical, Physical and Objects)
     */
    class preamble_section_node : public ast_node
    {
        public:
        std::vector<definition_variant> m_definitions;

        preamble_section_node(int line, int column, const std::vector<definition_variant>& defs): 
        m_definitions(defs), ast_node(line, column){}

        inline std::vector<definition_variant>& get_definitions(){
            return m_definitions;
        }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented preamble_section_node.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds the description
     * of a complete system (an assembly of Chips components)
     */
    class system_section_node : public ast_node {
        public:
        std::vector<system_statement_variant> m_statements;

        system_section_node(int line, int column, const std::vector<system_statement_variant>& stts): 
        m_statements(stts), ast_node(line, column){}

        inline std::vector<system_statement_variant>& get_statements(){
            return m_statements;
        }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented system_section_node.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Root node for a Chips program in Chips AST
     */
    class program_node : public ast_node {
        public:
        std::string m_filename;
        preamble_section_node m_preamble;
        system_section_node m_system;

        program_node(int line, int column, const std::string& filename, preamble_section_node preamble, system_section_node system) :
        ast_node(line, column), m_filename(filename),m_preamble(preamble), m_system(system) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented program_node.accept(visitor&) error.");
        }

        inline const preamble_section_node &get_preamble() {return m_preamble;};
        inline const system_section_node& get_system() {return m_system;};
    };

    /**
     * Abstract class
     * Node of the AST that represents a statement in any
     * Chips code environment.
     */
    template<statement_env stenv, recurring_statement recstt> class statement : public virtual ast_node {
        public:
        statement(int line, int column) : ast_node(line, column){}
    };

    
    // what is this?
    // template<recurring_statement recstt> 
    // class statement<statement_env::DEFINITION, recstt> : public statement<statement_env::NODE, recstt> {};
    
    /**
     * Concrete class
     * Node of the AST representing a dataflow declarations in any context.
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv> class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION> {
        public:
        using df_variable_type = typename SttEnvToVariableKind<dft, stenv>::type;
        df_variable_type m_variable;

        dataflow_declaration(df_variable_type variable) : 
        m_variable(variable) {};

        inline df_variable_type get_variable() { return m_variable; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_declaration.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the AST representing a dataflow assignements in any context
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv> 
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT> {
        public:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        lvalue<dft, expr_env> *m_lvalue;
        rvalue<dft, expr_env> *m_rvalue;

        dataflow_assignment(lvalue<dft, expr_env> *lhs, rvalue<dft, expr_env> *rhs)
            : m_lvalue(lhs), m_rvalue(rhs) {}

        lvalue<dft, expr_env> *get_lhs() { return m_lvalue; }
        rvalue<dft, expr_env> *get_rhs() { return m_rvalue; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_assignment.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_statement
     * is evaluated as true
     */
    template<statement_env stenv> 
    class if_section : public ast_node {
        public:
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        std::vector<statement_type> m_if_statements;
        
        if_section(int line, int column, const std::vector<statement_type>& stts):
        ast_node(line, column), m_if_statements(stts){};

        std::vector<statement_type>& get_statements() { return m_if_statements; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented if_section.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_else_statement
     * is evaluated as false
     */
    template<statement_env stenv> class else_section : public ast_node {};
    template<statement_env stenv> class if_statement : public statement<stenv, recurring_statement::IF> {};
    template<statement_env stenv> class if_else_statement : public if_statement<stenv> {};
    template<statement_env stenv, dataflow_type dft> class foreach_statement : public statement<stenv, recurring_statement::FOREACH> {};
    template<block_type bt> class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH> {};
    template<block_type bt> class block_declaration : public statement<statement_env::SYSTEM, recurring_statement::DECLARATION> {};
    class channel_plugging : public statement<statement_env::SYSTEM, recurring_statement::PLUGGING> {};
    template<dataflow_kind dfk, dataflow_type dft> class feeding_statement : public statement<statement_env::SYSTEM, recurring_statement::FEEDING> {};
    class linking_statement : public statement<statement_env::SYSTEM, recurring_statement::LINKING> {};
    template<node_element ne> class node_element_declaration : public statement<statement_env::NODE, recurring_statement::DECLARATION> {};

    template<expression_env expenv> class array : public ast_node {};
    template<expression_env expenv> class variable : public array<expenv> {};
    class primitive_variable : public variable<expression_env::PRIMITIVE> {};
    template<dataflow_type dft> class dataflow_primitive_variable : public primitive_variable {};
    class node_variable : public variable<expression_env::PRIMITIVE> {};
    template<dataflow_type dft> class contextual_variable : public node_variable {};
    class collective_variable : public variable<expression_env::COLLECTIVE> {};
    template<dataflow_type dft> class dataflow_collective_variable : public collective_variable {};
    class system_variable : public variable<expression_env::SYSTEM> {};
    template<block_type bt> class block_variable : public system_variable {};
    template<dataflow_type dft> class dataflow_system_variable : public system_variable {};
}

#endif