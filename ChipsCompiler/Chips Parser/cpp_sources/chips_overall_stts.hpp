#ifndef OVERALL_STTS_H
#define OVERALL_STTS_H

#include "./chips_config_stts.hpp"
#include "./chips_expressions.hpp"
#include "chips_overall_system.hpp"
/*
        (NOT CONFIGURATION) STATEMENTS NODES
*/


class statement_node : public s_statement_node {};

class statements_node : public ast_node {

private:
    std::vector<std::unique_ptr<statement_node>> statements;

public:
    statements_node() = default;

    explicit statements_node(std::vector<std::unique_ptr<statement_node>>&& sttmt) noexcept
        : statements(std::move(sttmt)) {}

    statements_node(const statements_node&) = delete;
    statements_node& operator=(const statements_node&) = delete;
    
    statements_node(statements_node&&) = default;
    statements_node& operator=(statements_node&&) = default;
        
    std::vector<std::unique_ptr<statement_node>>& get_statements() { return statements; }
    
    void append(std::unique_ptr<statement_node> sttmt) {
        statements.insert(statements.begin(), std::move(sttmt));
    }
    void accept(chips_visitor& visitor);
    virtual void hello() override; /* {
        for(const auto& sttmt : statements){
            sttmt.get()->hello();
            auto type = sttmt.get()->get_type();
            if(type == IF_ST || type == IFELSE_ST || type == LOOP_ST){
                std::cout << std::endl;
            }else{
                std::cout << ";" << std::endl;
            }
        }
    }*/
};

class rhs_assignment_node : public ast_node {
private:
    std::unique_ptr<expression_node> value = nullptr;

public:
    rhs_assignment_node(std::unique_ptr<expression_node> value)
        : value(std::move(value)) {}

    rhs_assignment_node() {}
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from rhs_assignment_node\n";}
};


class assignment_node : public statement_node {
private:
    std::unique_ptr<suffixised_node> lhs;
    const STATEMENT_TYPE type = ASSI_ST;
    std::unique_ptr<rhs_assignment_node> rhs;
public:
    assignment_node(std::unique_ptr<suffixised_node> lhs, std::unique_ptr<rhs_assignment_node> rhs)
    : lhs(std::move(lhs)), rhs(std::move(rhs))  {};
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from assignment_node\n";}
};

class this_attribute_node : public suffixised_node {
private:
    std::string attr;
    std::string elem;
public:
    this_attribute_node(std::string attr, std::string elem, std::unique_ptr<suffixes_node> suff)
    : attr(attr), elem(elem), suffixised_node(attr, std::move(suff)) {}

    std::string get_attribut() { return attr;}
    std::string get_element() { return elem; }
    
    void accept(chips_visitor& visitor);
    virtual void hello() override;// {std::cout << "hello from this_attribute_node\n";}
};




class dataflow_full_declaration_node : public statement_node {
    private:
        std::unique_ptr<dataflow_type_node> type;
        std::string identifier;
        std::unique_ptr<rhs_assignment_node> assign;
        
    public:
        dataflow_full_declaration_node(std::unique_ptr<dataflow_type_node> type, std::string identifier, std::unique_ptr<rhs_assignment_node> assign)
            : type(std::move(type)), identifier(identifier), assign(std::move(assign)) {}
        
        dataflow_type_node* get_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        rhs_assignment_node* get_rhs() { return assign.get(); }

        void accept(chips_visitor& visitor) ;
        virtual void hello() override; /* {
            if(type){
                type.get()->hello();
            }
            std::cout << " " << identifier << " ";
            if(assign){
                assign.get()->hello();
            }
        }*/
};

class variable_assignment_node : public statement_node {
    private:
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;
        std::unique_ptr<expression_node> expr;
    public:
        variable_assignment_node(std::string identifier, std::unique_ptr<suffixes_node> suff, std::unique_ptr<expression_node> expr)
            : identifier(identifier), suff(std::move(suff)), expr(std::move(expr)) {}

        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }
        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override; /* {
            std::cout << identifier << " ";
            if(suff){
                suff.get()->hello();
            }
            std::cout << " = ";
            if(expr){
                expr.get()->hello();
            }
            std::cout << ";\n";
        }*/
};

class function_call_statement_node : public statement_node {
    private:
        std::unique_ptr<function_call_node> fcall;
    public:
        function_call_statement_node(std::unique_ptr<function_call_node> fcall)
            : fcall(std::move(fcall)) {}
        
        void accept(chips_visitor& visitor) ;
        virtual void hello() override;// {std::cout << "hello from function_call_statement_node\n";}
};


class if_node : public statement_node {
private:
    static constexpr STATEMENT_TYPE type = IF_ST;
    std::unique_ptr<expression_node> cond;
    std::unique_ptr<statements_node> stts;
public:
    if_node(std::unique_ptr<expression_node> cond, std::unique_ptr<statements_node> stts)
        : cond(std::move(cond)), stts(std::move(stts)) {}
        
    constexpr STATEMENT_TYPE get_type() { return type; }
    expression_node* get_condition() { return cond.get(); }
    statements_node* get_statements() { return stts.get(); }

    void accept(chips_visitor& visitor) ;

    virtual void hello() override; /* {
        std::cout << "if (";
        if(cond){
            cond.get()->hello();
        }
        std::cout << "){\n";
        if(stts){
            stts.get()->hello();
        }
        std::cout << "}";
    }*/
};

class if_else_node : public statement_node {
private:
    static constexpr STATEMENT_TYPE type = IFELSE_ST;
    std::unique_ptr<if_node> ifnode;
    std::unique_ptr<statements_node> elsestts;
public:
    if_else_node(std::unique_ptr<if_node> ifnode, std::unique_ptr<statements_node> elsestts)
        : ifnode(std::move(ifnode)) , elsestts(std::move(elsestts)){} 

    constexpr STATEMENT_TYPE get_type() { return type; }
    if_node* get_if_node() { return ifnode.get(); }
    statements_node* get_else_node() { return elsestts.get(); }

    void accept(chips_visitor& visitor) ;

    virtual void hello() override; /* {
        if(ifnode){
            ifnode.get()->hello();
        }
        std::cout << "else {\n";
        if(elsestts){
            elsestts.get()->hello();
        }
        std::cout << "}\n";
    }*/
};

class loop_node : public statement_node {
private:
    static constexpr STATEMENT_TYPE type = LOOP_ST;
    std::string ident1;
    std::string ident2;
    std::unique_ptr<statements_node> stts;
public:
    loop_node(std::string ident1, std::string ident2, std::unique_ptr<statements_node> stts)
        : ident1(ident1), ident2(ident2), stts(std::move(stts)) {} 

    constexpr STATEMENT_TYPE get_type() { return type; }
    std::string get_ident1() { return ident1; }
    std::string get_ident2() { return ident2; }
    statements_node* get_statements() { return stts.get(); }

    void accept(chips_visitor& visitor);

    virtual void hello() override;/* {
        std::cout << "foreach " << ident1 << "in " << ident2 << "{\n";
        if(stts){
            stts.get()->hello();
        }
        std::cout << "}\n";
    }*/
};

class block_node : public ast_node {
    private:
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;

    public:
        block_node(std::string identifier, std::unique_ptr<suffixes_node> suff)
            : identifier(identifier), suff(std::move(suff)) {}

        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

#endif