#ifndef __chips_lrxvalues__
#define __chips_lrxvalues__

#include "forward_declarations.hpp"
#include "meta_type_conversions.hpp"
#include "ast_base.hpp"
#include "ast_system_specific.hpp"
#include <vector>

namespace chips{


    template<dataflow_type dft, expression_env sttenv>
    class lvalue : public ast_node{};


    template<dataflow_type dft, expression_env expenv>
    class rvalue : public ast_node{
        private:
            bool parenthesage = false;

        public:
            void set_parenthesage(bool b){
                parenthesage = b;
            }

            bool is_parenthesage() const{
                return parenthesage;
            }
    };

    template<dataflow_type dft>
    class rvalue<dft, expression_env::SYSTEM> : public feeder<dataflow_kind::LOGICAL,dft> {};

    template<dataflow_type dft, expression_env expenv>
    class direct: public rvalue<dft,expenv>
    {
    private:
        using value_type = typename DfTypeToCppType<dft>::type;
        value_type m_value;

        public:
            direct(value_type value) : m_value(value){};

            value_type get_value() { return m_value; }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class function : public rvalue<dft,expenv>, system_iterable
    {
    private:
        std::string m_name;
        std::vector<rvalue_variant<expenv>> m_parameters;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class plus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            plus(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() const { return m_left_operand.get(); }
            operand_type* get_rhs() const { return m_right_operand.get(); }


            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            minus(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return m_left_operand.get(); }
            operand_type* get_rhs() { return m_right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            mult(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return m_left_operand.get(); }
            operand_type* get_rhs() { return m_right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            div(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return m_left_operand.get(); }
            operand_type* get_rhs() { return m_right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv>
    class mod : public rvalue<dataflow_type::INT, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dataflow_type::INT,expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            mod(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return m_left_operand.get(); }
            operand_type* get_rhs() { return m_right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> numeric;

        public:
            cast_as(std::shared_ptr<operand_type> numeric)
                : numeric(std::move(numeric)){}

            operand_type* get_cast() { return numeric.get(); }
            
            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv, dataflow_type dft>
    class gt : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        std::shared_ptr<operand_type> m_left_operand;
        std::shared_ptr<operand_type> m_right_operand;

        public:
            gt(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : m_left_operand(std::move(left_operand)), m_right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return m_left_operand.get(); }
            operand_type* get_rhs() { return m_right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv, dataflow_type dft>
    class lt : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

        public:
            lt(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return left_operand.get(); }
            operand_type* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv, dataflow_type dft>
    class geq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

        public:
            geq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return left_operand.get(); }
            operand_type* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv, dataflow_type dft>
    class leq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft,expenv>::type;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

        public:
            leq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return left_operand.get(); }
            operand_type* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand;
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand;

        public:
            or_operator(std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand, std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            rvalue<dataflow_type::BOOL, expenv>* get_lhs() { return left_operand.get(); }
            rvalue<dataflow_type::BOOL, expenv>* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand;
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand;

        public:
            and_operator(std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> left_operand, std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            rvalue<dataflow_type::BOOL, expenv>* get_lhs() { return left_operand.get(); }
            rvalue<dataflow_type::BOOL, expenv>* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> operand;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft,expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL ,expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

        public:
            eq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return left_operand.get(); }
            operand_type* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<dataflow_type dft,expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL , expenv>
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type ;
        std::shared_ptr<operand_type> left_operand;
        std::shared_ptr<operand_type> right_operand;

        public:
            neq(std::shared_ptr<operand_type> left_operand, std::shared_ptr<operand_type> right_operand)
                : left_operand(std::move(left_operand)), right_operand(std::move(right_operand)){}

            operand_type* get_lhs() { return left_operand.get(); }
            operand_type* get_rhs() { return right_operand.get(); }

            void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };


    template<dataflow_type dft, expression_env expenv>
    class variable_expression : rvalue<dft,expenv>, lvalue<dft,expenv>
    {
    private:
        variable<expenv>& m_variable;
        std::shared_ptr<rvalue<dataflow_type::INT, expenv>> index;
        
        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
}


#endif