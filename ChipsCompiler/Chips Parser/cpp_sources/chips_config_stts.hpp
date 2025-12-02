#ifndef CONFIG_STTS_H
#define CONFIG_STTS_H



#include "./chips_ast_classes.hpp"
#include <iostream>
#include <memory>
#include <vector>

/*
    CONFIGURATION STATEMENTS NODES
*/

namespace chips {

    inline namespace v1 {

        class c_statement_node : public ast_node {

        public:
            virtual ~c_statement_node() = default;
            //virtual void accept(chips_visitor& visitor) = 0;
            virtual void node_print() = 0;

        };

        class c_statements_node : ast_node {
            private:
                std::vector<std::unique_ptr<c_statement_node>> sstatements;
            public:

                c_statements_node() 
                    : sstatements(std::vector<std::unique_ptr<c_statement_node>>()){};

                c_statements_node(std::unique_ptr<c_statements_node> sstatements)
                    : sstatements(std::move(sstatements->sstatements)){}
                
                inline void append(std::unique_ptr<c_statement_node> sttmt){
                    sstatements.insert(sstatements.begin(), std::move(sttmt));
                }

                void accept(chips_visitor& visitor);

                void node_print() override {
                    // std::cout << "c_statements_node" << std::endl;
                    // if(sstatements.empty()){
                    //     std::cout << "  (empty)" << std::endl;
                    // }else{
                    //     std::cout << sstatements.size() << " statements:" << std::endl;
                    // }
                    for(auto& sttmt : sstatements){
                        if(sttmt == nullptr) {  // AJOUTEZ les accolades ici
                            // std::cout << "null\n"; 
                            continue;
                        }
                        sttmt->node_print();
                        std::cout << ";" << std::endl;
                    }
                }
        };

        

        class c_assignment_node : public c_statement_node{
            private:
                std::string ofname;
                std::unique_ptr<suffixes_node> qty;
                std::unique_ptr<expressions_node> exprs;

            public:

                c_assignment_node() = default;

                c_assignment_node(std::string ofname, std::unique_ptr<suffixes_node> qty, std::unique_ptr<expressions_node> exprs)
                    : ofname(std::move(ofname)), qty(std::move(qty)), exprs(std::move(exprs)){}

                void accept(chips_visitor& visitor); // TODO
                

                void node_print() override {
                    std::cout << ofname;
                    qty->node_print();
                    std::cout << ".in(";
                    exprs->node_print();
                    std::cout << ")";
                }

        };

        
        class c_if_node : public c_statement_node {
            private:
                std::unique_ptr<expression_node> expr;
                std::unique_ptr<c_statements_node> sstatements;
            public:
                c_if_node(std::unique_ptr<expression_node> expr, std::unique_ptr<c_statements_node> sstatements)
                    : expr(std::move(expr)), sstatements(std::move(sstatements)){}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    std::cout << "if(";
                    expr->node_print();
                    std::cout << "){\n";
                    sstatements->node_print();
                    std::cout << "}\n";
                }
        };

        class c_loop_node : public c_statement_node {
            private:
                std::string ident;
                std::unique_ptr<suffixable_node> expr;
                std::unique_ptr<c_statements_node> ssttmts;
            public:
                c_loop_node(std::string ident, std::unique_ptr<suffixable_node> expr, std::unique_ptr<c_statements_node> ssttmts)
                    : ident(std::move(ident)), expr(std::move(expr)), ssttmts(std::move(ssttmts)) {}

                void accept(chips_visitor& visitor);
                
                void node_print() override {
                    std::cout << "foreach " << ident << " in ";
                    expr->node_print();
                    std::cout << "{\n";
                    ssttmts->node_print();
                    std::cout << "}\n";
                }
        };


        class c_if_else_node : public c_statement_node {
            private:
                std::unique_ptr<c_if_node> sifnode;
                std::unique_ptr<c_statements_node> elsestts;
            public:
                c_if_else_node(std::unique_ptr<c_if_node> sifnode, std::unique_ptr<c_statements_node> elsestts)
                    : sifnode(std::move(sifnode)), elsestts(std::move(elsestts)){}
                
                void accept(chips_visitor& visitor);
                
                void node_print() override {
                    sifnode->node_print();
                    std::cout << "else {\n";
                    elsestts->node_print();
                    std::cout << "}\n";
                }
        };

        class function_declaration_node : public c_statement_node {
            private:
                std::string oftype;
                std::unique_ptr<suffixes_node> qty;
                std::string ofname;
            public:
                function_declaration_node (std::string oftype, std::unique_ptr<suffixes_node> qty, std::string ofname)
                    : oftype(std::move(oftype)), qty(std::move(qty)), ofname(std::move(ofname)){}
                
            void accept(chips_visitor& visitor);

            void node_print() override {
                std::cout << oftype;
                qty->node_print();
                std::cout << ofname;
            }
            
        };

        class at_node : public c_statement_node{
            private:
                std::string ofname;
                std::unique_ptr<expressions_node> exprs;

            public:
                at_node(std::string ofname, std::unique_ptr<expressions_node> exprs)
                    : ofname(std::move(ofname)), exprs(std::move(exprs)){}

                void accept(chips_visitor& visitor);
                
                void node_print() override {
                    std::cout << ofname << " at (";
                    exprs->node_print();
                    std::cout << ")";
                }

        };


        class link_node : public c_statement_node{
            private:
                std::string lk_src;
                std::string lk_target;
            
            public:
                link_node(std::string lk_src, std::string lk_target)
                    : lk_src(std::move(lk_src)), lk_target(std::move(lk_target)){}
            
                void accept(chips_visitor& visitor);

                void node_print() override {
                    std::cout << "link " << lk_src << " to " << lk_target;
                }
        
        };

    }

}













#endif