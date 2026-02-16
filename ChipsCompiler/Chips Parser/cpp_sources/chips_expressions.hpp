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
    virtual void hello() override;
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
    virtual void hello() override; 
};

class paren_expression_node : public expression_node {
    private:
        std::unique_ptr<expression_node> expr;
    public:
        paren_expression_node(std::unique_ptr<expression_node> expr) : expr(std::move(expr)) {}

        expression_node* get_expr() { return expr.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
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
    virtual void hello() override;
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
    virtual void hello() override;

    std::string get_identifier() { return ident; }
    expressions_node* get_expressions() { return operands.get(); }
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
        virtual void hello() override;    
};

class variable_node : public suffixised_node {
public:
    variable_node(std::string ident)
        : suffixised_node(std::move(ident), nullptr) {}

    variable_node(std::string ident, std::unique_ptr<suffixes_node> suff)
        : suffixised_node(std::move(ident), std::move(suff)) {}

    std::string get_identifier() { return suffixised_node::get_identifier(); }
    suffixes_node* get_suffixes() { return suffixised_node::get_suffixes(); }

    void accept(chips_visitor& visitor);

    virtual void hello() override;
};

class plugging_expr_node : public suffixised_node {
    private:
        std::unique_ptr<block_node> block;

    public:
        plugging_expr_node(std::unique_ptr<block_node> block, std::string identifier)
            : suffixised_node(identifier, nullptr), block(std::move(block)) {}

        block_node* get_block() { return block.get(); }
        std::string get_identifier() { return suffixised_node::get_identifier(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class collective_cast_node : public expression_node {
    private:
        std::unique_ptr<collective_operation_node> c_op;
        std::unique_ptr<block_node> block;
        std::string identifier;

    public:
        collective_cast_node(std::unique_ptr<collective_operation_node> c_op, std::unique_ptr<block_node> block, std::string identifier)
            : c_op(std::move(c_op)), block(std::move(block)), identifier(identifier) {}

        collective_operation_node* get_collective_operation() { return c_op.get(); }
        block_node* get_block() { return block.get(); }
        std::string get_identifier() { return identifier; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class collective_operation_node : public ast_node {
    private:
        std::string identifier;

    public:
        collective_operation_node(std::string identifier)
            : identifier(identifier) {}

        std::string get_identifier() { return identifier; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
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

class cast_node : public expression_node {
private:
    std::unique_ptr<dataflow_type_node> type;
    std::unique_ptr<expression_node> expr;
    EXPRESSION_TYPE cast_type;
public:
    cast_node(std::unique_ptr<dataflow_type_node> type, std::unique_ptr<expression_node> expr) 
        : expr(std::move(expr)), type(std::move(type)) {
            switch(this->type->get_type()){
                case INT_DF: cast_type = CAST_TO_INT_EXP; break;
                case FLOAT_DF: cast_type = CAST_TO_FLOAT_EXP; break;
                case BOOL_DF: cast_type = CAST_TO_BOOL_EXP; break;
            }
        }

    dataflow_type_node* get_df_type() { return type.get(); }
    expression_node* get_expr() { return expr.get(); }
    EXPRESSION_TYPE get_type() { return cast_type; }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;
};

class stop_node : public expression_node {
    private:
        static constexpr COLLECTIVE_KW kw = STOP;

    public:
        stop_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class input_node : public expression_node {
    private:
        static constexpr COLLECTIVE_KW kw = INPUT;
        
    public:
        input_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_cast_node : public expression_node {
    private:
        std::unique_ptr<dataflow_type_node> type;
        std::unique_ptr<expression_node> expr;
        EXPRESSION_TYPE cast_type;
    public:
        c_cast_node(std::unique_ptr<dataflow_type_node> type, std::unique_ptr<expression_node> expr)
            : type(std::move(type)), expr(std::move(expr)) {
                switch(this->type->get_type()){
                    case INT_DF: cast_type = CAST_TO_INT_EXP; break;
                    case FLOAT_DF: cast_type = CAST_TO_FLOAT_EXP; break;
                    case BOOL_DF: cast_type = CAST_TO_BOOL_EXP; break;
                }
            }

        dataflow_type_node* get_df_type() { return type.get(); }
        expression_node* get_expr() { return expr.get(); }
        EXPRESSION_TYPE get_type() { return cast_type; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class context_expression_node : public expression_node {
    private:
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;

    public:
        context_expression_node(std::string identifier, std::unique_ptr<suffixes_node> suff)
            : identifier(identifier), suff(std::move(suff)) {}

        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class integrated_function_node : public expression_node {
    private:
        std::string identifier;
        std::unique_ptr<expressions_node> exprs;

    public:
        integrated_function_node(std::string identifier, std::unique_ptr<expressions_node> exprs)
            : identifier(identifier), exprs(std::move(exprs)) {}

        std::string get_identifier() { return identifier; }
        expressions_node* get_expressions() { return exprs.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class context_decl_node : public expression_node {
    private:
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;

    public:
        context_decl_node(std::string identifier, std::unique_ptr<suffixes_node> suff)
            : identifier(identifier), suff(std::move(suff)) {}

        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
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
    virtual void hello() override;
};

#endif