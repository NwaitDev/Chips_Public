
#ifndef AST_H_H
#define AST_H_H

//#include "./ChipsADS.hpp"
#include "./chips_ast_classes.hpp"
#include "./chips_expressions.hpp"
#include "./chips_overall.hpp"
#include "./chips_overall_system.hpp"
#include "./chips_config_stts.hpp"
#include "./chips_overall_stts.hpp"
#include "./chips_overall_collective.hpp"
#include "./chips_declaration_ctx.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>














/*
    Configuration stuff
*/

class system_node : public ast_node {
    std::unique_ptr<s_statements_node> sstatements;
public:
    system_node() {}

    system_node(std::unique_ptr<s_statements_node> sstatements)
        : sstatements(std::move(sstatements)) {}

    s_statements_node* get_system_statements() { return sstatements.get(); }
    
    void accept(chips_visitor& visitor);

    virtual void hello() override;
};

class chips_node : public ast_node{
private:
    std::unique_ptr<preambles_node> preambles;
    std::unique_ptr<system_node> system;
public:

    chips_node(){}

    chips_node(std::unique_ptr<preambles_node> preambles, std::unique_ptr<system_node> system)
        : preambles(std::move(preambles)), system(std::move(system)) {}

    preambles_node* get_preambles() const { return preambles.get(); }
    system_node* get_system() const { return system.get(); }

    void accept(chips_visitor& visitor){
        // TODO
    }

    virtual void hello() override;/* {
        if(preambles){
            preambles.get()->hello();
        }
        if(system){
            system.get()->hello();
        }
    }*/
};


#endif 
