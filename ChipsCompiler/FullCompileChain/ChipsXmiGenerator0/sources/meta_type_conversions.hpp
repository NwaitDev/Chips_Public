#ifndef __meta_type_conversions__
#define __meta_type_conversions__
#include<variant>
#include<string>

#include "forward_declarations.hpp"

namespace chips {

    using definition_variant = std::variant<object_definition*,logical_definition*,physical_definition*,implementation_defintion*,collective_function_definition*>;

    template<dataflow_type>
    struct DfTypeToContextualDeclType;

    template<>
    struct DfTypeToContextualDeclType<dataflow_type::INT>{
        using type = node_element_declaration<node_element::CONTEXTUAL_INT>;
    };

    template<>
    struct DfTypeToContextualDeclType<dataflow_type::FLOAT>{
        using type = node_element_declaration<node_element::CONTEXTUAL_FLOAT>;
    };

    template<>
    struct DfTypeToContextualDeclType<dataflow_type::BOOL>{
        using type = node_element_declaration<node_element::CONTEXTUAL_BOOL>;
    };


    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    template<dataflow_type, statement_env>
    struct SttEnvToVariableKind;

    template<dataflow_type dft>
    struct SttEnvToVariableKind<dft,statement_env::DEFINITION>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct SttEnvToVariableKind<dft,statement_env::COLLECTIVE>{
        using type = dataflow_collective_variable<dft>;
    };

    template<dataflow_type dft>
    struct SttEnvToVariableKind<dft,statement_env::IMPLEMENTATION>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct SttEnvToVariableKind<dft,statement_env::NODE>{
        using type = dataflow_primitive_variable<dft>;
    };

    template<dataflow_type dft>
    struct SttEnvToVariableKind<dft,statement_env::SYSTEM>{
        using type = dataflow_system_variable<dft>;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////


    template<statement_env sttenv>
    struct SttEnvToExpEnv;

    template<>
    struct SttEnvToExpEnv<statement_env::DEFINITION>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct SttEnvToExpEnv<statement_env::COLLECTIVE>{
        static constexpr expression_env value = expression_env::COLLECTIVE;
    };

    template<>
    struct SttEnvToExpEnv<statement_env::IMPLEMENTATION>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct SttEnvToExpEnv<statement_env::NODE>{
        static constexpr expression_env value = expression_env::PRIMITIVE;
    };

    template<>
    struct SttEnvToExpEnv<statement_env::SYSTEM>{
        static constexpr expression_env value = expression_env::SYSTEM;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    template<statement_env>
    struct SttEnvToSttVariant{};

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

    using node_statement_variant = std::variant<node_statement<recurring_statement::IF>*,node_statement<recurring_statement::FOREACH>*,node_element_declaration<node_element::CHANNEL>*,node_element_declaration<node_element::CONTEXTUAL_INT>*,node_element_declaration<node_element::CONTEXTUAL_FLOAT>*,node_element_declaration<node_element::CONTEXTUAL_BOOL>*,node_statement<recurring_statement::DECLARATION>*,node_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::NODE>{
        using type = node_statement_variant;
    };

    using primitive_statement_variant = std::variant<primitive_statement<recurring_statement::IF>*,primitive_statement<recurring_statement::FOREACH>*,primitive_statement<recurring_statement::DECLARATION>*,primitive_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::DEFINITION>{
        using type = primitive_statement_variant;
    };

    using collective_statement_variant = std::variant<collective_statement<recurring_statement::IF>*,collective_statement<recurring_statement::FOREACH>*,collective_statement<recurring_statement::DECLARATION>*,collective_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::COLLECTIVE>{
        using type = collective_statement_variant;
    };

    using system_statement_variant = std::variant<system_statement<recurring_statement::IF>*,system_statement<recurring_statement::FOREACH>*,system_statement<recurring_statement::DECLARATION>*,system_statement<recurring_statement::IMPLEMENTS>*,system_statement<recurring_statement::FEEDING>*,system_statement<recurring_statement::LINKING>*,system_statement<recurring_statement::PLUGGING>*,system_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::SYSTEM>{
        using type = system_statement_variant;
    };

    // do not use, work in progress
    using implementation_statement_variant = std::variant<aliasing_statement<node_element::CHANNEL>*,aliasing_statement<node_element::CONTEXTUAL_BOOL>*,aliasing_statement<node_element::CONTEXTUAL_INT>*,aliasing_statement<node_element::CONTEXTUAL_FLOAT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::IMPLEMENTATION>{
        using type = implementation_statement_variant;
    };

    template<expression_env>
    struct StatementVariantTypeAlias;

    template<>
    struct StatementVariantTypeAlias<expression_env::PRIMITIVE>{ using type = primitive_statement_variant; };
    template<>
    struct StatementVariantTypeAlias<expression_env::COLLECTIVE>{ using type = collective_statement_variant; };
    template<>
    struct StatementVariantTypeAlias<expression_env::SYSTEM>{ using type = system_statement_variant; };

    using statement_variant = std::variant<node_statement_variant, primitive_statement_variant,collective_statement_variant,system_statement_variant,implementation_statement_variant>;
    
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    
    template<block_type>
    struct BlockTypeToBlockDef{};

    template<>
    struct BlockTypeToBlockDef<block_type::LOGICAL>{
        using type = logical_definition;
    };

    template<>
    struct BlockTypeToBlockDef<block_type::PHYSICAL>{
        using type = physical_definition;
    };

    template<>
    struct BlockTypeToBlockDef<block_type::OBJECT>{
        using type = object_definition;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    template<block_type bt>
    struct BlockTypeToBlockVariable;

    template<>
    struct BlockTypeToBlockVariable<block_type::LOGICAL>{
        using type = block_variable<block_type::LOGICAL>;
    };

    template<>
    struct BlockTypeToBlockVariable<block_type::PHYSICAL>{
        using type = block_variable<block_type::PHYSICAL>;
    };

    template<>
    struct BlockTypeToBlockVariable<block_type::OBJECT>{
        using type = block_variable<block_type::OBJECT>;
    };

    using functional_block_variant = std::variant<block_variable<block_type::LOGICAL>*,block_variable<block_type::PHYSICAL>*>;

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    template<node_element ne>
    struct NodeElemToNodeVariable;

    template<>
    struct NodeElemToNodeVariable<node_element::CHANNEL>{
        using type = std::string;
    };

    template<>
    struct NodeElemToNodeVariable<node_element::CONTEXTUAL_BOOL>{
        using type = contextual_variable<dataflow_type::BOOL>;
    };

    template<>
    struct NodeElemToNodeVariable<node_element::CONTEXTUAL_FLOAT>{
        using type = contextual_variable<dataflow_type::FLOAT>;
    };

    template<>
    struct NodeElemToNodeVariable<node_element::CONTEXTUAL_INT>{
        using type = contextual_variable<dataflow_type::INT>;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    using collective_parameter_variant = std::variant<collective_parameter<dataflow_type::INT>*,collective_parameter<dataflow_type::FLOAT>*,collective_parameter<dataflow_type::BOOL>*>;

    using function_parameter_variant = std::variant<function_parameter<dataflow_kind::LOGICAL, dataflow_type::INT>*,function_parameter<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,function_parameter<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;

    using function_output_variant = std::variant<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>*,function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;

    using physical_parameter_variant = std::variant<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*,function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;
    
    using physical_output_variant = std::variant<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>*,function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;


    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////


    template<dataflow_type dft>
    struct DfTypeToCppType;

    // Specializations

    template<>
    struct DfTypeToCppType<dataflow_type::INT> {
        using type = int;
    };

    template<>
    struct DfTypeToCppType<dataflow_type::FLOAT> {
        using type = double;
    };

    template<>
    struct DfTypeToCppType<dataflow_type::BOOL> {
        using type = bool;
    };

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////


    template<expression_env expenv>
    using rvalue_variant = std::variant<rvalue<dataflow_type::INT,expenv>*,rvalue<dataflow_type::FLOAT,expenv>*,rvalue<dataflow_type::BOOL,expenv>*>;

    using rvalue_primitive_variant = rvalue_variant<expression_env::PRIMITIVE>;

    using rvalue_collective_variant = rvalue_variant<expression_env::COLLECTIVE>;

    template<expression_env expenv>
    using primitive_iterable_variant = std::variant<
        function<dataflow_type::INT,expenv>*,
        function<dataflow_type::FLOAT,expenv>*,
        function<dataflow_type::BOOL,expenv>*,
        rvalue_variant<expenv>*
    >;

    template<expression_env expenv>
    using int_rvalue_expression_variant = std::variant<
        function<dataflow_type::INT,expenv>*,
        direct<dataflow_type::INT,expenv>*,
        plus<dataflow_type::INT,expenv>*,
        minus<dataflow_type::INT,expenv>*,
        mult<dataflow_type::INT,expenv>*,
        chips::div<dataflow_type::INT,expenv>*,
        mod<expenv>*,
        cast_as<dataflow_type::INT,expenv>*,
        uminus_operator<dataflow_type::INT,expenv>*,
        variable_expression<dataflow_type::INT,expenv>*,
        input*,
        stop*
    >;

    template<expression_env expenv>
    using float_rvalue_expression_variant = std::variant<
        function<dataflow_type::FLOAT,expenv>*,
        direct<dataflow_type::FLOAT,expenv>*,
        plus<dataflow_type::FLOAT,expenv>*,
        minus<dataflow_type::FLOAT,expenv>*,
        mult<dataflow_type::FLOAT,expenv>*,
        div<dataflow_type::FLOAT,expenv>*,
        cast_as<dataflow_type::FLOAT,expenv>*,
        uminus_operator<dataflow_type::FLOAT,expenv>*,
        variable_expression<dataflow_type::FLOAT,expenv>*,
        input*,
        stop*
    >;

    template<expression_env expenv>
    using bool_rvalue_expression_variant = std::variant<
        gt<expenv,dataflow_type::INT>*,
        gt<expenv,dataflow_type::FLOAT>*,
        lt<expenv,dataflow_type::INT>*,
        lt<expenv,dataflow_type::FLOAT>*,
        geq<expenv,dataflow_type::INT>*,
        geq<expenv,dataflow_type::FLOAT>*,
        leq<expenv,dataflow_type::INT>*,
        leq<expenv,dataflow_type::FLOAT>*,
        eq<dataflow_type::INT,expenv>*,
        eq<dataflow_type::FLOAT,expenv>*,
        eq<dataflow_type::BOOL,expenv>*,
        neq<dataflow_type::INT,expenv>*,
        neq<dataflow_type::FLOAT,expenv>*,
        neq<dataflow_type::BOOL,expenv>*,
        or_operator<expenv>*,
        and_operator<expenv>*,
        not_operator<expenv>*,
        direct<dataflow_type::BOOL,expenv>*,
        variable_expression<dataflow_type::BOOL,expenv>*,
        input*,
        stop*    
    >;

    template<expression_env expenv, dataflow_type dft>
    struct RvalueExpressionVariantTypeAlias;

    template<expression_env expenv>
    struct RvalueExpressionVariantTypeAlias<expenv, dataflow_type::INT>{
        using type = int_rvalue_expression_variant<expenv>;
    };

    template<expression_env expenv>
    struct RvalueExpressionVariantTypeAlias<expenv, dataflow_type::FLOAT>{
        using type = float_rvalue_expression_variant<expenv>;
    };

    template<expression_env expenv>
    struct RvalueExpressionVariantTypeAlias<expenv, dataflow_type::BOOL>{
        using type = bool_rvalue_expression_variant<expenv>;
    };

    using feeder_variant = std::variant<
            feeder<dataflow_kind::LOGICAL, dataflow_type::INT>*,
            feeder<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,
            feeder<dataflow_kind::LOGICAL, dataflow_type::BOOL>*,
            feeder<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
            feeder<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
            feeder<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*
        >;

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    
    // Primary template for operand nodes
    template<dataflow_type, expression_env>
    struct ChipsOperandToAstType;

    template<dataflow_type, expression_env>
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

    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////

    /**
     * Struct needed to have a define time variablility for the 
     * acces of typenames and constructors of dataflow variables  
     * concrete classes within different contexts
     */
    template<expression_env expenv,dataflow_type dft>
    struct DataflowVariableAliasType;


    template<dataflow_type dft>
    struct DataflowVariableAliasType<expression_env::PRIMITIVE, dft>{
        using type = dataflow_primitive_variable<dft>;
    };


    template<dataflow_type dft>
    struct DataflowVariableAliasType<expression_env::COLLECTIVE, dft>{
        using type = dataflow_collective_variable<dft>;
    };

    template<dataflow_type dft>
    struct DataflowVariableAliasType<expression_env::SYSTEM, dft>{
        using type = dataflow_system_variable<dft>;
    };


    /**
     * Struct needed to have a define time variablility for the 
     * acces of typenames and constructors of dataflow variable declaration  
     * concrete classes within different contexts
     */
    template<expression_env expenv,dataflow_type dft>
    struct DataflowVariableDeclarationAliasType;

    template<dataflow_type dft>
    struct DataflowVariableDeclarationAliasType<expression_env::PRIMITIVE,dft>{
        using type = dataflow_declaration<dft, statement_env::DEFINITION>;
    };

    template<dataflow_type dft>
    struct DataflowVariableDeclarationAliasType<expression_env::COLLECTIVE,dft>{
        using type = dataflow_declaration<dft, statement_env::COLLECTIVE>;
    };

    template<dataflow_type dft>
    struct DataflowVariableDeclarationAliasType<expression_env::SYSTEM,dft>{
        using type = dataflow_declaration<dft, statement_env::SYSTEM>;
    };


    /**
     * Struct needed to have a define time variablility for the 
     * acces of typenames and constructors of dataflow assignment  
     * concrete classes within different contexts
     */
    template<expression_env env,dataflow_type dft>
    struct DataflowAssignmentAliasType;

    template<dataflow_type dft>
    struct DataflowAssignmentAliasType<expression_env::PRIMITIVE,dft>{
        using type = dataflow_assignment<dft, statement_env::DEFINITION>;
    };

    template<dataflow_type dft>
    struct DataflowAssignmentAliasType<expression_env::COLLECTIVE,dft>{
        using type = dataflow_assignment<dft, statement_env::COLLECTIVE>;
    };

    template<dataflow_type dft>
    struct DataflowAssignmentAliasType<expression_env::SYSTEM,dft>{
        using type = dataflow_assignment<dft, statement_env::SYSTEM>;
    };
}

#endif