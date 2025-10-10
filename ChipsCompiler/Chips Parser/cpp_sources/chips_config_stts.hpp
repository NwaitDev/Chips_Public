#ifndef CONFIG_STTS_H
#define CONFIG_STTS_H



#include "./chips_ast_classes.hpp"
#include <iostream>
#include <memory>
#include <vector>

/*
    CONFIGURATION STATEMENTS NODES
*/

class c_statement_node : public ast_node {};


class c_assignment_node : public c_statement_node{
private:
    std::string ofname;
    std::unique_ptr<suffixes_node> qty;
    std::unique_ptr<expressions_node> exprs;

public:
    c_assignment_node(std::string ofname, std::unique_ptr<suffixes_node>& qty, std::unique_ptr<expressions_node>& exprs)
        : ofname(ofname), qty(std::move(qty)), exprs(std::move(exprs)){}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from c_assignment_node\n";}

};

class at_node : public c_statement_node{
private:
    std::string ofname;
    std::unique_ptr<expressions_node> exprs;

public:
    at_node(std::string ofname, std::unique_ptr<expressions_node>& exprs)
        : ofname(ofname), exprs(std::move(exprs)){}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from at_node\n";}

};


class link_node : public c_statement_node{
    private:
        std::string lk_src;
        std::string lk_target;
    
    public:
        link_node(std::string lk_src, std::string lk_target)
            : lk_src(lk_src), lk_target(lk_target){}
    
        void accept(chips_visitor& visitor);
        inline void hello() override {std::cout << "hello from link_node\n";}
    
    };

class c_statements_node : ast_node {
private:
    std::vector<std::unique_ptr<c_statement_node>> sstatements;
public:

    c_statements_node() 
        : sstatements(std::vector<std::unique_ptr<c_statement_node>>()){};

    c_statements_node(std::unique_ptr<c_statements_node>& sstatements)
        : sstatements(std::move(sstatements->sstatements)){}
    
    inline void append(std::unique_ptr<c_statement_node>& sttmt){sstatements.push_back(std::move(sttmt));}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from c_statements_node\n";}
};


class c_loop_node : public c_statement_node {
private:
    std::string ident;
    std::unique_ptr<suffixable_node> expr;
    std::unique_ptr<c_statements_node> ssttmts;
public:
    c_loop_node(const std::string& ident, std::unique_ptr<suffixable_node>& expr, std::unique_ptr<c_statements_node>& ssttmts)
        : ident(std::move(ident)), expr(std::move(expr)), ssttmts(std::move(ssttmts)) {}

    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from c_loop_node\n";}
};

class c_if_node : public c_statement_node {
private:
    std::unique_ptr<expression_node> expr;
    std::unique_ptr<c_statements_node> sstatements;
public:
    c_if_node(std::unique_ptr<expression_node>& expr, std::unique_ptr<c_statements_node>& sstatements)
        : expr(std::move(expr)), sstatements(std::move(sstatements)){}
    
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from c_if_node\n";}
};

class c_if_else_node : public c_statement_node {
private:
    std::unique_ptr<c_if_node> sifnode;
    std::unique_ptr<c_statements_node> elsestts;
public:
    c_if_else_node(std::unique_ptr<c_if_node>& sifnode, std::unique_ptr<c_statements_node>& elsestts)
        : sifnode(std::move(sifnode)), elsestts(std::move(elsestts)){}
    
    void accept(chips_visitor& visitor);
    inline void hello() override {std::cout << "hello from c_if_else_node\n";}
};

class function_declaration_node : public c_statement_node {
    private:
        std::string oftype;
        std::unique_ptr<suffixes_node> qty;
        std::string ofname;
    public:
        function_declaration_node (std::string oftype, std::unique_ptr<suffixes_node>& qty, std::string ofname)
            : oftype(oftype), qty(std::move(qty)), ofname(ofname){}
        
        void accept(chips_visitor& visitor);
        inline void hello() override {std::cout << "hello from dataflow_declaration_node\n";}
    
    };

#endif