#ifndef __chips_lrxvalues__
#define __chips_lrxvalues__

#include <vector>
#include <memory>

#include "meta_type_conversions.hpp"
#include "ast_base.hpp"

namespace chips
{

    /**
     * Abstract class
     * Node of the AST that represents something to
     * be put on the left side of an assignment
     */
    template <dataflow_type dft, expression_env expenv>
    class lvalue : public virtual ast_node
    {
    };

    /**
     * Abstract class
     * Node of the AST that represents something to
     * that can be evaluated as a chips primitive value
     */
    template <dataflow_type dft, expression_env expenv>
    class rvalue : public virtual ast_node
    {
    public:
        inline void hello() { std::cout << "I am interpreted as an rvalue" << std::endl; }
    };

    /**
     * Concrete class
     * Node of the AST that represents a hard coded
     * value (any type or code section)
     */
    template <dataflow_type dft, expression_env expenv>
    class direct : public rvalue<dft, expenv>
    {
    private:
        using value_type = typename DfTypeToCppType<dft>::type;
        value_type m_value;

    public:
        direct(value_type value) : m_value(value) {};

        inline value_type get_value() { return m_value; }

        inline void accept(visitor &v) { v.visit(*this); }

        inline void hello()
        {
            if constexpr (dft == dataflow_type::FLOAT)
            {
                printf("%f", m_value);
            }
            else if constexpr (dft == dataflow_type::BOOL)
            {
                std::cout << (m_value ? "true" : "false");
            }
            else
            {
                std::cout << m_value;
            }
        }
    };

    /**
     * Interface
     * Node of the AST that represents something
     * that can be iterated on in the system section
     */
    class system_iterable
    {
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
     * - float random()
     * - bool is_fresh(dataflow_variable)
     */
    template <dataflow_type dft, expression_env expenv>
    class function : public rvalue<dft, expenv>, system_iterable
    {
    private:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;

    public:
        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello() {};
    };

    /**
     * Concret class
     * Node of the AST that represents + (plus) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class plus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        plus(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() const { return m_left_operand.get(); }
        operand_type *get_rhs() const { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " + ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents - (minus) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        minus(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return m_left_operand.get(); }
        operand_type *get_rhs() { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " - ";
            if (get_rhs())
                get_rhs()->hello();
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents * (multiplication) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        mult(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return m_left_operand.get(); }
        operand_type *get_rhs() { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " * ";
            if (get_rhs())
                get_rhs()->hello();
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents / (division) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        div(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return m_left_operand.get(); }
        operand_type *get_rhs() { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " / ";
            if (get_rhs())
                get_rhs()->hello();
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents % (modulo) operator
     */
    template <expression_env expenv>
    class mod : public rvalue<dataflow_type::INT, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dataflow_type::INT, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        mod(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return m_left_operand.get(); }
        operand_type *get_rhs() { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello() {};
    };

    /**
     * Concrete class
     * Node of the AST that represents the type casting operation
     */
    template <dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> numeric;

    public:
        cast_as(std::shared_ptr<operand_type> numeric)
            : numeric(std::move(numeric)) {}

        operand_type *get_cast() { return numeric.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            if (get_cast())
            {
                std::cout << "(";
                // std::cout << "cast";
                if constexpr (dft == dataflow_type::INT)
                {
                    std::cout << "int";
                }
                else if constexpr (dft == dataflow_type::FLOAT)
                {
                    std::cout << "float";
                }
                else if constexpr (dft == dataflow_type::BOOL)
                {
                    std::cout << "bool";
                }
                std::cout << ")";
                get_cast()->hello();
            }
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents > (greater than) operator
     */
    template <expression_env expenv, dataflow_type dft>
    class gt : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

    public:
        gt(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return m_left_operand.get(); }
        operand_type *get_rhs() { return m_right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " > ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents < (lower than) operator
     */
    template <expression_env expenv, dataflow_type dft>
    class lt : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

    public:
        lt(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return left_operand.get(); }
        operand_type *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " < ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the >= (greater or equal) operator
     */
    template <expression_env expenv, dataflow_type dft>
    class geq : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

    public:
        geq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return left_operand.get(); }
        operand_type *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " >= ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents <= (lower or equal) operator
     */
    template <expression_env expenv, dataflow_type dft>
    class leq : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

    public:
        leq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return left_operand.get(); }
        operand_type *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " <= ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents || (or) operator
     */
    template <expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand;
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand;

    public:
        or_operator(std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand, std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand.get(); }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " || ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents && (and) operator
     */
    template <expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand;
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand;

    public:
        and_operator(std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand, std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand.get(); }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " && ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents ! (not) operator
     */
    template <expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> operand;

    public:
        not_operator(std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> operand)
            : operand(std::move(operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            std::cout << "!";
            if (get_lhs())
                get_lhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the unary minus operator
     */
    template <dataflow_type dft, expression_env expenv>
    class uminus_operator : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> operand;

    public:
        uminus_operator(std::shared_ptr<operand_type> operand)
            : operand(std::move(operand)) {}

        operand_type *get_rhs() { return operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            std::cout << " -";
            if (get_rhs())
                get_rhs()->hello();
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents ==
     */
    template <dataflow_type dft, expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

    public:
        eq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return left_operand.get(); }
        operand_type *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " == ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents != (not equal) operator
     */
    template <dataflow_type dft, expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

    public:
        neq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
            : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)) {}

        operand_type *get_lhs() { return left_operand.get(); }
        operand_type *get_rhs() { return right_operand.get(); }

        inline void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            // if(this->is_parenthesage()) std::cout << "(";
            if (get_lhs())
                get_lhs()->hello();
            std::cout << " != ";
            if (get_rhs())
                get_rhs()->hello();
            // if(this->is_parenthesage()) std::cout << ")";
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents an expression
     * referencing a dataflow variable
     */
    template <dataflow_type dft, expression_env expenv>
    class variable_expression : public rvalue<dft, expenv>, public lvalue<dft, expenv>
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

        void accept(visitor &v) { v.visit(*this); }
        inline void hello()
        {
            std::cout << "VARIABLE EXPRESSION" << std::endl;
            get_variable()->hello();
        }
    };

    template <dataflow_type dft, expression_env expenv>
    class variable_contextual_expression : public variable_expression<dft, expenv>
    {
    public:
        variable_contextual_expression(variable<expenv> *variable, std::vector<int_rvalue_expression_variant<expenv>> index)
            : variable_expression<dft, expenv>(variable, index) {}

        variable_contextual_expression(variable<expenv> *variable)
            : variable_expression<dft, expenv>(variable) {}

        inline void accept(visitor &v) { v.visit(*this); }
    };
}

#endif