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
    EXPRESSION_TYPE return_type;
    bool implicit_cast;
public:
    binary_expression_node(std::unique_ptr<expression_node> lhs, EXPRESSION_TYPE type, std::unique_ptr<expression_node> rhs)
        : lhs(std::move(lhs)), type(type), rhs(std::move(rhs)) {
            if(this->lhs->have_implicit_cast() || this->rhs->have_implicit_cast()){
                implicit_cast = true;
                return_type = UNKNOWN_EXP;
                return;
            }

            if(this->lhs->get_return_type() == UNKNOWN_EXP || this->rhs->get_return_type() == UNKNOWN_EXP){
                implicit_cast = true;
                return_type = UNKNOWN_EXP;
                return;
            }

            if(this->lhs->get_return_type() == this->rhs->get_return_type()){
                this->return_type = this->lhs->get_return_type();
                implicit_cast = false;
            }else{
                implicit_cast = true;
                return_type = UNKNOWN_EXP;
            }
        }

    expression_node* get_lhs() { return lhs.get(); }
    EXPRESSION_TYPE get_type() { return type; }
    EXPRESSION_TYPE get_return_type() override { return return_type; }
    bool have_implicit_cast() { return implicit_cast; }
    expression_node* get_rhs() { return rhs.get(); }
    
    void accept(chips_visitor& visitor) ;
    virtual void hello() override;
};

class unary_expression_node : public expression_node {
private:
    const EXPRESSION_TYPE type;
    EXPRESSION_TYPE return_type;
    std::unique_ptr<expression_node> operand;
    bool implicit_cast;
public:
    unary_expression_node( EXPRESSION_TYPE type, std::unique_ptr<expression_node> operand)
        : type(type), operand(std::move(operand)) {
            if((this->type == NOT_EXP && this->operand->get_return_type() == BOOL_EXP) ||
                (this->type == U_MINUS_EXP && (this->operand->get_return_type() == INT_EXP || this->operand->get_return_type() == FLOAT_EXP))){
                implicit_cast = false;
                return_type = this->operand->get_return_type();
            }else{
                implicit_cast = true;
                return_type = UNKNOWN_EXP;
            }
        }

    EXPRESSION_TYPE get_type() { return type; }
    EXPRESSION_TYPE get_return_type() { return return_type; }
    expression_node* get_rhs() { return operand.get(); }
    bool have_implicit_cast() { return implicit_cast; }
    
    void accept(chips_visitor& visitor) ;
    virtual void hello() override; 
};

class paren_expression_node : public expression_node {
    private:
        std::unique_ptr<expression_node> expr;
        EXPRESSION_TYPE return_type;
        bool implicit_cast;
    public:
        paren_expression_node(std::unique_ptr<expression_node> expr) : expr(std::move(expr)) {}

        expression_node* get_expr() { return expr.get(); }
        EXPRESSION_TYPE get_return_type() { return expr.get()->get_return_type(); }
        bool have_implicit_cast() { return expr.get()->have_implicit_cast(); }

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
    EXPRESSION_TYPE get_return_type() { return type; }
    int get_int() { return value.i; }
    double get_float() { return value.d; }
    bool get_bool() { return value.b; }
    bool have_implicit_cast() { return false; }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;
};

class function_call_node : public suffixable_node {
private:
    const EXPRESSION_TYPE type = FCALL_EXP;
    EXPRESSION_TYPE return_type;
    std::string ident;
    std::unique_ptr<expressions_node> operands;
    bool implicit_cast;
public:
    function_call_node(std::string ident, std::unique_ptr<expressions_node> operands)
        :ident(ident),operands(std::move(operands)){}
    void accept(chips_visitor& visitor);
    virtual void hello() override;

    std::string get_identifier() { return ident; }
    EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
    expressions_node* get_expressions() { return operands.get(); }
    bool have_implicit_cast() { return false; }
};

class suffixised_node : public expression_node {
    private:
        std::string identifier;
        EXPRESSION_TYPE return_type;
        std::unique_ptr<suffixes_node> suffixes;
        bool implicit_cast;
    public:
        suffixised_node(std::string identifier, std::unique_ptr<suffixes_node> suffixes)
        : identifier(identifier), suffixes(std::move(suffixes)) {}

        std::string get_identifier() { return identifier; }
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        suffixes_node* get_suffixes() { return suffixes.get(); }
        bool have_implicit_cast() { return false; }

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
    EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
    bool have_implicit_cast() { return false; }

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
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

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
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

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
    EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
    bool have_implicit_cast() { return false; }
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
    EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
    bool have_implicit_cast() { return false; }
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from object_physical_attribute_node\n";}
};

class cast_node : public expression_node {
private:
    std::unique_ptr<dataflow_type_node> type;
    std::unique_ptr<expression_node> expr;
    EXPRESSION_TYPE cast_type;
    EXPRESSION_TYPE return_type;
    bool implicit_cast;
public:
    cast_node(std::unique_ptr<dataflow_type_node> type, std::unique_ptr<expression_node> expr) 
        : expr(std::move(expr)), type(std::move(type)) {
            switch(this->type->get_type()){
                case INT_DF: 
                    cast_type = CAST_TO_INT_EXP; 
                    if(expr.get()->get_return_type() == BOOL_EXP){
                        implicit_cast = true;
                        return_type = UNKNOWN_EXP;
                    }else{
                        implicit_cast = false;
                        return_type = expr.get()->get_return_type();
                    }
                    break;
                case FLOAT_DF: 
                    cast_type = CAST_TO_FLOAT_EXP; 
                    if(expr.get()->get_return_type() == BOOL_EXP){
                        implicit_cast = true;
                        return_type = UNKNOWN_EXP;
                    }else{
                        implicit_cast = false;
                        return_type = expr.get()->get_return_type();
                    }
                    break;
                case BOOL_DF: 
                    cast_type = CAST_TO_BOOL_EXP; 
                    if(expr.get()->get_return_type() != BOOL_EXP){
                        implicit_cast = true;
                        return_type = UNKNOWN_EXP;
                    }else{
                        implicit_cast = false;
                        return_type = expr.get()->get_return_type();
                    }
                    break;
            }
        }

    dataflow_type_node* get_df_type() { return type.get(); }
    EXPRESSION_TYPE get_return_type() { return return_type; }
    expression_node* get_expr() { return expr.get(); }
    EXPRESSION_TYPE get_type() { return cast_type; }
    bool have_implicit_cast() { return implicit_cast; }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;
};

class stop_node : public expression_node {
    private:
        static constexpr COLLECTIVE_KW kw = STOP;

    public:
        stop_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class input_node : public expression_node {
    private:
        static constexpr COLLECTIVE_KW kw = INPUT;
        
    public:
        input_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_cast_node : public expression_node {
    private:
        std::unique_ptr<dataflow_type_node> type;
        std::unique_ptr<expression_node> expr;
        EXPRESSION_TYPE cast_type;
        EXPRESSION_TYPE return_type;
        bool implicit_cast;
    public:
        c_cast_node(std::unique_ptr<dataflow_type_node> type, std::unique_ptr<expression_node> expr)
            : type(std::move(type)), expr(std::move(expr)) {
                switch(this->type->get_type()){
                    case INT_DF: 
                        cast_type = CAST_TO_INT_EXP; 
                        if(expr.get()->get_return_type() == BOOL_EXP){
                            implicit_cast = true;
                            return_type = UNKNOWN_EXP;
                        }else{
                            implicit_cast = false;
                            return_type = expr.get()->get_return_type();
                        }
                        break;
                    case FLOAT_DF: 
                        cast_type = CAST_TO_FLOAT_EXP; 
                        if(expr.get()->get_return_type() == BOOL_EXP){
                            implicit_cast = true;
                            return_type = UNKNOWN_EXP;
                        }else{
                            implicit_cast = false;
                            return_type = expr.get()->get_return_type();
                        }
                        break;
                    case BOOL_DF: 
                        cast_type = CAST_TO_BOOL_EXP; 
                        if(expr.get()->get_return_type() != BOOL_EXP){
                            implicit_cast = true;
                            return_type = UNKNOWN_EXP;
                        }else{
                            implicit_cast = false;
                            return_type = expr.get()->get_return_type();
                        }
                        break;
                }
            }

        dataflow_type_node* get_df_type() { return type.get(); }
        EXPRESSION_TYPE get_return_type() { return return_type; }
        expression_node* get_expr() { return expr.get(); }
        EXPRESSION_TYPE get_type() { return cast_type; }
        bool have_implicit_cast() { return implicit_cast; }

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
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

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
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

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
        EXPRESSION_TYPE get_return_type() { return UNKNOWN_EXP; }
        bool have_implicit_cast() { return false; }

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