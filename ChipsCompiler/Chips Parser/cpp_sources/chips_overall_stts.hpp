#ifndef OVERALL_STTS_H
#define OVERALL_STTS_H

#include "./chips_config_stts.hpp"
#include "./chips_expressions.hpp"
#include "./chips_ast_classes.hpp"
/*
        (NOT CONFIGURATION) STATEMENTS NODES
*/

namespace chips {

    inline namespace v1 {

        class statement_node : public c_statement_node {};

        class rhs_assignment_node : public ast_node {
            private:
                std::unique_ptr<expression_node> value = nullptr;

            public:
                rhs_assignment_node(std::unique_ptr<expression_node>& value)
                    : value(std::move(value)) {}

                rhs_assignment_node() {}
                
                void accept(chips_visitor& visitor);
                void node_print() override {
                    if(value != nullptr){  // Ajoutez cette vérification
                        std::cout << "= ";
                        value->node_print();
                        std::cout << ";";
                    } else {
                        std::cout << "(value is null)";
                    }
                }
        };

        class dataflow_full_declaration_node : public statement_node {
            private:
                const STATEMENT_TYPE type = INST_ST;
                std::unique_ptr<rhs_assignment_node> assign;
                std::unique_ptr<dataflow_declaration_node> decl;
                
            public:
                dataflow_full_declaration_node(std::unique_ptr<dataflow_declaration_node> decl, std::unique_ptr<rhs_assignment_node> assign)
                    : decl(std::move(decl)), assign(std::move(assign)) {}

                dataflow_full_declaration_node(std::unique_ptr<dataflow_declaration_node> decl)
                    : decl(std::move(decl)), assign(nullptr) {}

                void accept(chips_visitor& visitor) ;

                void node_print() override {
                    // std::cout << "dataflow_full_declaration_node: ";
                    if(decl != nullptr){  // Ajoutez cette vérification
                        decl->node_print();
                    } else {
                        std::cout << "(decl is null) ";
                    }
                    if(assign != nullptr){
                        assign->node_print();
                    } else {
                        std::cout << "(no assignment)";
                    }
                    std::cout << std::endl;
                }
        };
    }
}



// class statements_node : public ast_node {

// private:
//     std::vector<std::unique_ptr<statement_node>> statements;

// public:
//     statements_node() : statements(std::vector<std::unique_ptr<statement_node>>()){};
//     statements_node(std::unique_ptr<statements_node>& stts)
//         : statements(std::move(stts->statements)) {}
    
//     inline void append(std::unique_ptr<statement_node>& sttmt) {statements.push_back(std::move(sttmt));}
//     void accept(chips_visitor& visitor);
//     inline void hello() override {std::cout << "hello from statements_node\n";}
// };




// class assignment_node : public statement_node {
// private:
//     std::unique_ptr<suffixised_node> lhs;
//     const STATEMENT_TYPE type = ASSI_ST;
//     std::unique_ptr<rhs_assignment_node> rhs;
// public:
//     assignment_node(std::unique_ptr<suffixised_node> lhs, std::unique_ptr<rhs_assignment_node> rhs)
//     : lhs(std::move(lhs)), rhs(std::move(rhs))  {};
//     void accept(chips_visitor& visitor);
//     inline void hello() override {std::cout << "hello from assignment_node\n";}
// };

// class this_attribute_node : public suffixised_node {
// private:
//     std::string attr;
//     std::string elem;
// public:
//     this_attribute_node(std::string attr, std::string elem, std::unique_ptr<suffixes_node>& suff)
//     : attr(attr), elem(elem), suffixised_node(suff) {}

//     void accept(chips_visitor& visitor);
//     inline void hello() override {std::cout << "hello from this_attribute_node\n";}
// };







// class function_call_statement_node : public statement_node {
// private:
//     std::unique_ptr<function_call_node> fcall;
// public:
//     function_call_statement_node(std::unique_ptr<function_call_node>& fcall)
//         : fcall(std::move(fcall)) {}
    
//     void accept(chips_visitor& visitor) ;
//     inline void hello() {std::cout << "hello from function_call_statement_node\n";}
// };


// class if_node : public statement_node {
// private:
//     const STATEMENT_TYPE type = IF_ST;
//     std::unique_ptr<expression_node> cond;
//     std::unique_ptr<statements_node> stts;
// public:
//     if_node(std::unique_ptr<expression_node>& cond, std::unique_ptr<statements_node>& stts)
//         : cond(std::move(cond)), stts(std::move(stts)) {} 
//     void accept(chips_visitor& visitor) ;

//     inline void hello() override {std::cout << "hello from if_node\n";}
// };

// class if_else_node : public statement_node {
// private:
//     const STATEMENT_TYPE type = IFELSE_ST;
//     std::unique_ptr<if_node> ifnode;
//     std::unique_ptr<statements_node> elsestts;
// public:
//     if_else_node(std::unique_ptr<if_node>& ifnode, std::unique_ptr<statements_node>& elsestts)
//         : ifnode(std::move(ifnode)) , elsestts(std::move(elsestts)){} 
//     void accept(chips_visitor& visitor) ;

//     inline void hello() override {std::cout << "hello from if_else_node\n";}
// };

// class loop_node : public statement_node {
// private:
//     const STATEMENT_TYPE type = LOOP_ST;
//     std::string ident;
//     std::unique_ptr<suffixable_node> iterable;
//     std::unique_ptr<statements_node> stts;
// public:
//     loop_node(std::string ident, std::unique_ptr<suffixable_node>& iterable, std::unique_ptr<statements_node>& stts)
//         : ident(std::move(ident)), iterable(std::move(iterable)), stts(std::move(stts)) {} 
//     void accept(chips_visitor& visitor);

//     inline void hello() override {std::cout << "hello from loop_node\n";}
// };

#endif