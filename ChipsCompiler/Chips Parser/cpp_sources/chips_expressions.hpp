#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "./chips_ast_classes.hpp"
#include "./chips_overall.hpp"
/*
    EXPRESSION NODES
*/
class suffixable_node : public expression_node {};

class binary_expression_node : public expression_node {
private:
    std::unique_ptr<expression_node> lhs;
    const EXPRESSION_TYPE type;
    std::unique_ptr<expression_node> rhs;
public:
    binary_expression_node(std::unique_ptr<expression_node> lhs, EXPRESSION_TYPE type, std::unique_ptr<expression_node> rhs)
        : lhs(std::move(lhs)), type(type), rhs(std::move(rhs)) {}

    expression_node* get_lhs() { return lhs.get(); }
    EXPRESSION_TYPE get_type() { return type; }
    expression_node* get_rhs() { return rhs.get(); }
    
    void accept(chips_visitor& visitor) ;
    virtual void hello() override; /* {
        if(lhs){
            lhs.get()->hello();
        }
        switch(type){
            case LT_EXP: std::cout << " < "; break;
            case GT_EXP: std::cout << " > "; break;
            case LEQ_EXP: std::cout << " <= "; break;
            case GEQ_EXP: std::cout << " >= "; break;
            case NEQ_EXP: std::cout << " != "; break;
            case EQ_EXP: std::cout << " == "; break;
            case PLUS_EXP: std::cout << " + "; break;
            case MINUS_EXP: std::cout << " - "; break;
            case TIMES_EXP: std::cout << " * "; break;
            case DIV_EXP: std::cout << " / "; break;
            case MOD_EXP: std::cout << " % "; break; 
        }
        if(rhs){
            rhs.get()->hello();
        }
    }*/
};

class unary_expression_node : public expression_node {
private:
    const EXPRESSION_TYPE type;
    std::unique_ptr<expression_node> operand;
public:
    unary_expression_node( EXPRESSION_TYPE type, std::unique_ptr<expression_node> operand)
        : type(type), operand(std::move(operand)) {}

    EXPRESSION_TYPE get_type() { return type; }
    expression_node* get_rhs() { return operand.get(); }
    
    void accept(chips_visitor& visitor) ;
    virtual void hello() override; /* {
        switch(type){
            case U_MINUS_EXP: std::cout << "-"; break;
            case NOT_EXP: std::cout << "!"; break;
        }
        if(operand){
            operand.get()->hello();
        }
    }*/
};

class paren_expression_node : public expression_node {
    private:
        std::unique_ptr<expression_node> expr;
    public:
        paren_expression_node(std::unique_ptr<expression_node> expr) : expr(std::move(expr)) {}

        expression_node* get_expr() { return expr.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;/* {
            std::cout << "(";
            if(expr){
                expr.get()->hello();
            }
            std::cout << ")";
        }*/
};

class number_literal_node : public expression_node {
private:
    union{
        double d;
        int i;
        bool b;
    }value;
    const EXPRESSION_TYPE type;
public:
    inline number_literal_node(double value) : type (FLOAT_EXP) {this->value.d = value;};
    inline number_literal_node(int value) : type(INT_EXP) {this->value.i = value;};
    inline number_literal_node(bool value) : type(BOOL_EXP) {this->value.b = value;};
    
    constexpr EXPRESSION_TYPE get_type() { return type; }
    int get_int() { return value.i; }
    double get_float() { return value.d; }
    bool get_bool() { return value.b; }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;/* {
        switch(type){
            case INT_EXP: std::cout << "int"; break;
            case FLOAT_EXP: std::cout << "float"; break;
            case BOOL_EXP: std::cout << "bool"; break;
        }
    }*/
};

class function_call_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = FCALL_EXP;
    std::string ident;
    std::unique_ptr<expressions_node> operands;
public:
    function_call_node(std::string ident, std::unique_ptr<expressions_node> operands)
        :ident(ident),operands(std::move(operands)){}
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from function_call_node\n";}
};

class suffixised_node : public expression_node {
private:
    std::string identifier;
    std::unique_ptr<suffixes_node> suffixes;
public:
    suffixised_node(std::string identifier, std::unique_ptr<suffixes_node> suffixes)
    : identifier(identifier), suffixes(std::move(suffixes)) {}

    std::string get_identifier() { return identifier; }
    suffixes_node* get_suffixes() { return suffixes.get(); }

    void accept(chips_visitor& visitor);
    virtual void hello() override;/* {
        std::cout << identifier << " ";
        if(suffixes){
            suffixes.get()->hello();
        }
    }*/
    
};

class variable_node : public suffixised_node {
public:
    variable_node(std::string ident, std::unique_ptr<suffixes_node> suff)
        : suffixised_node(std::move(ident), std::move(suff)) {}

    std::string get_identifier() { return suffixised_node::get_identifier(); }
    suffixes_node* get_suffixes() { return suffixised_node::get_suffixes(); }

    void accept(chips_visitor& visitor);

    virtual void hello() override;// {std::cout << "hello from variable_node\n";}
};


class object_virtual_output_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = OBJ_VIRT_OUT_EXP;
    std::string ident;
public:
    object_virtual_output_node(std::string ident) : ident(ident){}
    void accept(chips_visitor& visitor);
    virtual void hello() override; // {std::cout << "hello from object_virtual_output_node\n";}
};

class object_physical_attribute_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = OBJ_PHY_ATTR_EXP;
    std::string attribute;
    std::string element;
public:
    object_physical_attribute_node(std::string attr, std::string& elem) : attribute(attr), element(std::move(elem)){}
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from object_physical_attribute_node\n";}
};

// class suffix_node : public ast_node {
// private:
//     std::unique_ptr<expression_node> expression;
// public:
//     suffix_node(std::unique_ptr<expression_node>& expression)
//     : expression(std::move(expression)) {}
    
//     suffix_node() : expression(nullptr) {}

//     void accept(chips_visitor& visitor);
//     virtual void hello() override;// {std::cout << "hello from suffix_node\n";}
// };

class cast_node : public expression_node {
private:
    std::unique_ptr<dataflow_type_node> type;
    std::unique_ptr<expression_node> expr;
public:
    cast_node(std::unique_ptr<dataflow_type_node> type, std::unique_ptr<expression_node> expr) 
        : expr(std::move(expr)), type(std::move(type)) {}

    dataflow_type_node* get_type() { return type.get(); }
    expression_node* get_expr() { return expr.get(); }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;/* {
        std::cout << "(";
        if(type){
            type.get()->hello();
        }
        std::cout << ")";
        if(expr){
            expr.get()->hello();
        }
    }*/
};

class suffixes_node : public ast_node {
private:
    std::vector<std::unique_ptr<expression_node>> suffixes;
public:
    suffixes_node(std::unique_ptr<suffixes_node> suffixes)
        : suffixes(std::move(suffixes->suffixes)) {}
    
    suffixes_node()
        : suffixes(std::move(std::vector<std::unique_ptr<expression_node>>())) {}

    suffixes_node(const suffixes_node&) = delete;
    suffixes_node& operator=(const suffixes_node&) = delete;
    
    suffixes_node(suffixes_node&&) = default;
    suffixes_node& operator=(suffixes_node&&) = default;

    std::vector<std::unique_ptr<expression_node>>& get_suffixes() { return suffixes; }
    
    void append(std::unique_ptr<expression_node> suf){
        suffixes.insert(suffixes.begin(), std::move(suf));
    }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;/* {
        for(const auto& suf : suffixes) {
            std::cout << "[";
            if(suf){
                suf.get()->hello();
            }
            std::cout << "]";
        }
    }*/
};

#endif