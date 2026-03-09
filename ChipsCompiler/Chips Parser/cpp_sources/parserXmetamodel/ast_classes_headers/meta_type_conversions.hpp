#ifndef __meta_type_conversions__
#define __meta_type_conversions__
#include<variant>
#include<string>

#include "forward_declarations.hpp"

namespace chips {

    using definition_variant = std::variant<
        object_definition*,
        logical_definition*,
        physical_definition*,
        implementation_defintion*,
        collective_function_definition*>;


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
        using type = dataflow_primitive_variable<dft>;
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
    struct SttEnvToSttVariant<statement_env::NODE>{
        using type = node_statement_variant;
    };

    using primitive_statement_variant = std::variant<
        primitive_statement<recurring_statement::IF>*,
        primitive_statement<recurring_statement::FOREACH>*,
        primitive_statement<recurring_statement::DECLARATION>*,
        primitive_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::DEFINITION>{
        using type = primitive_statement_variant;
    };

    using collective_statement_variant = std::variant<
        collective_statement<recurring_statement::IF>*,
        collective_statement<recurring_statement::FOREACH>*,
        collective_statement<recurring_statement::DECLARATION>*,
        collective_statement<recurring_statement::ASSIGNMENT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::COLLECTIVE>{
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
    struct SttEnvToSttVariant<statement_env::SYSTEM>{
        using type = system_statement_variant;
    };

    // do not use, work in progress
    using implementation_statement_variant = std::variant<
        aliasing_statement<node_element::CHANNEL>*,
        aliasing_statement<node_element::CONTEXTUAL_BOOL>*,
        aliasing_statement<node_element::CONTEXTUAL_INT>*,
        aliasing_statement<node_element::CONTEXTUAL_FLOAT>*>;

    template<>
    struct SttEnvToSttVariant<statement_env::IMPLEMENTATION>{
        using type = implementation_statement_variant;
    };

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

    using functional_block_variant = std::variant<
        block_variable<block_type::LOGICAL>,
        block_variable<block_type::PHYSICAL>>;

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

    using collective_parameter_variant = std::variant<
        collective_parameter<dataflow_type::INT>*,
        collective_parameter<dataflow_type::FLOAT>*,
        collective_parameter<dataflow_type::BOOL>*>;

    using function_parameter_variant = std::variant<
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::INT>*,
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,
        function_parameter<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;

    using function_output_variant = std::variant<
        function_output<dataflow_kind::LOGICAL, dataflow_type::INT>*,
        function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*,
        function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>;

    using physical_parameter_variant = std::variant<
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;
    
    using physical_output_variant = std::variant<
        function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*,
        function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>;


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
    using rvalue_variant = std::variant<
        rvalue<dataflow_type::INT,expenv>*,
        rvalue<dataflow_type::FLOAT,expenv>*,
        rvalue<dataflow_type::BOOL,expenv>*>;


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
}

#endif