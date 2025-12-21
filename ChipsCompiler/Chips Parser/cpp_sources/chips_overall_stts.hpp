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

        class statements_node : public ast_node {

            private:
                std::vector<std::unique_ptr<statement_node>> statements;

            public:
                statements_node() : statements(std::vector<std::unique_ptr<statement_node>>()){};
                statements_node(std::unique_ptr<statements_node>& stts)
                    : statements(std::move(stts->statements)) {}
                
                inline void append(std::unique_ptr<statement_node>& sttmt) {statements.push_back(std::move(sttmt));}
                void accept(chips_visitor& visitor);
                void node_print() override {
                    // std::cout << "statements_node: ";
                    for(const auto& sttmt : statements){
                        sttmt->node_print();
                        std::cout << ";\n";
                    }
                }
        };

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
                        std::cout << " = ";
                        value->node_print();
                        
                    }
                }
        };

        class paren_expression_node : public expression_node {
            private:
                std::unique_ptr<expression_node> expr;
            public:
                paren_expression_node(std::unique_ptr<expression_node> expr)
                    : expr(std::move(expr)) {}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    std::cout << "(";
                    expr->node_print();
                    std::cout << ")";
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
                }
        };

        class function_call_statement_node : public statement_node {
            private:
                std::unique_ptr<function_call_node> fcall;
            public:
                function_call_statement_node(std::unique_ptr<function_call_node> fcall)
                    : fcall(std::move(fcall)) {}
                
                void accept(chips_visitor& visitor) ;

                void node_print() override {
                    // std::cout << "function_call_statement_node: \n";
                    fcall->node_print();
                }
        };


        // class if_node : public statement_node {
        //     private:
        //         const STATEMENT_TYPE type = IF_ST;
        //         std::unique_ptr<expression_node> cond;
        //         std::unique_ptr<statements_node> stts;
        //     public:
        //         if_node(std::unique_ptr<expression_node>& cond, std::unique_ptr<statements_node>& stts)
        //             : cond(std::move(cond)), stts(std::move(stts)) {} 
        //         void accept(chips_visitor& visitor) ;

        //         inline void hello() override {std::cout << "hello from if_node\n";}
        // };

        // class if_else_node : public statement_node {
        //     private:
        //         const STATEMENT_TYPE type = IFELSE_ST;
        //         std::unique_ptr<if_node> ifnode;
        //         std::unique_ptr<statements_node> elsestts;
        //     public:
        //         if_else_node(std::unique_ptr<if_node>& ifnode, std::unique_ptr<statements_node>& elsestts)
        //             : ifnode(std::move(ifnode)) , elsestts(std::move(elsestts)){} 
        //         void accept(chips_visitor& visitor) ;

        //         inline void hello() override {std::cout << "hello from if_else_node\n";}
        // };

        // class loop_node : public statement_node {
        //     private:
        //         const STATEMENT_TYPE type = LOOP_ST;
        //         std::string ident;
        //         std::unique_ptr<suffixable_node> iterable;
        //         std::unique_ptr<statements_node> stts;
        //     public:
        //         loop_node(std::string ident, std::unique_ptr<suffixable_node>& iterable, std::unique_ptr<statements_node>& stts)
        //             : ident(std::move(ident)), iterable(std::move(iterable)), stts(std::move(stts)) {} 
        //         void accept(chips_visitor& visitor);

        //         inline void hello() override {std::cout << "hello from loop_node\n";}
        // };

        // class assignment_node : public statement_node {
        //     private:
        //         std::unique_ptr<suffixised_node> lhs;
        //         const STATEMENT_TYPE type = ASSI_ST;
        //         std::unique_ptr<rhs_assignment_node> rhs;
        //     public:
        //         assignment_node(std::unique_ptr<suffixised_node> lhs, std::unique_ptr<rhs_assignment_node> rhs)
        //         : lhs(std::move(lhs)), rhs(std::move(rhs))  {};
        //         void accept(chips_visitor& visitor);

        //         void node_print() override {

        //         } 
        // };

        class assignment_node : public statement_node {};

        class variable_assignment_node : public assignment_node {
            private:
                std::string ident;
                std::unique_ptr<suffixes_node> suff;
                std::unique_ptr<rhs_assignment_node> rhs;

            public:

                variable_assignment_node(std::string ident, std::unique_ptr<suffixes_node> suff, std::unique_ptr<rhs_assignment_node> rhs)
                    : ident(std::move(ident)), suff(std::move(suff)), rhs(std::move(rhs)) {}

                void node_print() override {
                    std::cout << ident;
                    suff->node_print();
                    rhs->node_print();
                }

        };

        class this_assignment_node : public assignment_node {
            private:
                std::string attr;
                std::string elem;
                std::unique_ptr<suffixes_node> suff;
                std::unique_ptr<rhs_assignment_node> rhs;
            public:
                this_assignment_node(std::string attr, std::string elem, std::unique_ptr<suffixes_node> suff, std::unique_ptr<rhs_assignment_node> rhs)
                : attr(std::move(attr)), elem(std::move(elem)), suff(std::move(suff)), rhs(std::move(rhs)) {}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    std::cout << "this." << attr << "." << elem;
                    suff->node_print();
                    rhs->node_print();
                }
        };
    }
}


















#endif