
#ifndef __chips_lrxvalues__
#define __chips_lrxvalues__
#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include <vector>

namespace chips{


    template<dataflow_type dft, expression_env sttenv>
    class lvalue : public ast_node{};


    template<dataflow_type dft, expression_env expenv>
    class rvalue : public ast_node{};

    template<dataflow_type dft>
    class rvalue<dft, expression_env::SYSTEM> : public feeder<dataflow_kind::LOGICAL,dft> {};

    template<dataflow_type dft, expression_env expenv>
    class direct: public rvalue<dft,expenv>
    {
    private:
        using value_type = typename ChipsDftToCppType<dft>::type;
        value_type m_value;
    };

    template<dataflow_type dft, expression_env expenv>
    class function : public rvalue<dft,expenv>, system_iterable
    {
    private:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;
    };

    template<dataflow_type dft, expression_env expenv>
    class plus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv>
    class mod : public rvalue<dataflow_type::INT, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dataflow_type::INT,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type numeric;
    };

    template<expression_env expenv, dataflow_type dft>
    class gt : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv, dataflow_type dft>
    class lt : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv, dataflow_type dft>
    class geq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv, dataflow_type dft>
    class leq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };

    template<expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;
    };

    template<expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> operand;
    };

    template<dataflow_type dft,expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };

    template<dataflow_type dft,expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL , expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        operand_type left_operand;
        operand_type right_operand;
    };


    template<dataflow_type dft, expression_env expenv>
    class variable_expression : rvalue<dft,expenv>, lvalue<dft,expenv>
    {
    private:
        variable<expenv>& variable;
        rvalue<dataflow_type::INT,expenv> index;
    };
}


#endif