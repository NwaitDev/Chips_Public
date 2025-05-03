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
    binary_expression_node(std::unique_ptr<expression_node>& lhs, EXPRESSION_TYPE type, std::unique_ptr<expression_node>& rhs)
        : lhs(std::move(lhs)), type(type), rhs(std::move(rhs)) {}
    
    void accept(chips_visitor& visitor) ;
    inline void hello() override {std::cout << "hello from binary_expression_node\n";}
};

class unary_expression_node : public expression_node {
private:
    const EXPRESSION_TYPE type;
    std::unique_ptr<expression_node> operand;
public:
    unary_expression_node( EXPRESSION_TYPE type, std::unique_ptr<expression_node>& operand)
        : type(type), operand(std::move(operand)) {}
    
    void accept(chips_visitor& visitor) ;
    inline void hello() override {std::cout << "hello from unary_expression_node\n";}
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
    void accept(chips_visitor& visitor);
    void hello() override {std::cout << "hello from number_literal_node\n";}
};

class function_call_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = FCALL_EXP;
    std::string ident;
    std::unique_ptr<expressions_node> operands;
public:
    function_call_node(std::string ident, std::unique_ptr<expressions_node>& operands)
        :ident(ident),operands(std::move(operands)){}
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from function_call_node\n";}
};

class suffixised_node : public expression_node {
private:
    std::unique_ptr<suffixes_node> suffixes;
public:
    suffixised_node(std::unique_ptr<suffixes_node>& suffixes)
    : suffixes(std::move(suffixes)) {}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from suffixes_node\n";}
    
};

class variable_node : public suffixised_node {
private:
    std::string ident;
public:
    variable_node(std::string ident, std::unique_ptr<suffixes_node> suff)
        :ident(ident), suffixised_node(suff) {}

    void accept(chips_visitor& visitor);

    inline void hello() override {std::cout << "hello from variable_node\n";}
};


class object_virtual_output_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = OBJ_VIRT_OUT_EXP;
    std::string ident;
public:
    object_virtual_output_node(std::string ident) : ident(ident){}
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from object_virtual_output_node\n";}
};

class object_physical_attribute_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = OBJ_PHY_ATTR_EXP;
    std::string attribute;
    std::string element;
public:
    object_physical_attribute_node(std::string attr, std::string& elem) : attribute(attr), element(std::move(elem)){}
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from object_physical_attribute_node\n";}
};

class suffix_node : public ast_node {
private:
    std::unique_ptr<expression_node> expression;
public:
    suffix_node(std::unique_ptr<expression_node>& expression)
    : expression(std::move(expression)) {}
    
    suffix_node() : expression(nullptr) {}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from suffix_node\n";}
};

class cast_node : public expression_node {
private:
    std::unique_ptr<dataflow_type_node> type;
    std::unique_ptr<expression_node> expr;
public:
    cast_node(std::unique_ptr<dataflow_type_node>& type, std::unique_ptr<expression_node>& expr) 
        : expr(std::move(expr)), type(std::move(type)) {}
    
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from cast_node\n";}
};

class suffixes_node : public ast_node {
private:
    std::vector<std::unique_ptr<suffix_node>> suffixes;
public:
    suffixes_node(std::unique_ptr<suffixes_node>& suffixes)
        : suffixes(std::move(suffixes->suffixes)) {}
    
    suffixes_node()
        : suffixes(std::move(std::vector<std::unique_ptr<suffix_node>>())) {}
    
    inline void append(std::unique_ptr<suffix_node>& suf){suffixes.push_back(std::move(suf));}
    
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from suffixes_node\n";}
};

#endif