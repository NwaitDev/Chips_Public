
#ifndef AST_H_H
#define AST_H_H

//#include "./ChipsADS.hpp"
#include "./chips_ast_classes.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>














/*
    Configuration stuff
*/

class dimension_node : public ast_node {
private:
    std::unique_ptr<number_literal_node> dimension;
public:
    dimension_node(std::unique_ptr<number_literal_node> dimension)
        : dimension(std::move(dimension)){}
    void accept(chips_visitor& visitor);

    inline void hello() override {std::cout << "hello from dimension_node\n";}
};

class system_node : public ast_node {
    std::unique_ptr<dimension_node> dimension = nullptr;
    std::unique_ptr<c_statements_node> sstatements;
public:
    system_node(std::unique_ptr<dimension_node>& dimension, std::unique_ptr<c_statements_node>& sstatements)
        : dimension(std::move(dimension)), sstatements(std::move(sstatements)) {}

    system_node(std::unique_ptr<c_statements_node>& sstatements)
        : sstatements(std::move(sstatements)) {}
    
    void accept(chips_visitor& visitor);

    inline void hello() override {std::cout << "hello from system_node\n";}
};

class chips_node : public ast_node{
private:
    preambles_node preambles;
    std::unique_ptr<system_node> system;
public:

    chips_node(){}

    chips_node(std::unique_ptr<preambles_node>& preambles, std::unique_ptr<system_node>& system)
        : preambles(std::move(preambles)), system(std::move(system)) {}

    void accept(chips_visitor& visitor){
        // TODO
    }

    inline void hello() override {std::cout << "hello from chips_node\n";}

};


#endif 
