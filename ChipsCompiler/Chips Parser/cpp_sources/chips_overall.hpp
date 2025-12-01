#ifndef OVERALL_USAGE_H
#define OVERALL_USAGE_H

#include "./chips_ast_classes.hpp"
#include "./chips_expressions.hpp"
#include <iostream>
#include <memory>
#include <vector>

namespace chips {

    inline namespace v1 {

        class dataflow_type_node : public ast_node {
            private:
                const DATAFLOW_TYPE type;
                std::unique_ptr<suffixes_node> suff;
            public:

                dataflow_type_node (const DATAFLOW_TYPE type, std::unique_ptr<suffixes_node> suff)
                    : type(type), suff(std::move(suff)) {}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    // std::cout << "dataflow_type_node: ";
                    switch(type){
                        case INT_DF:
                            std::cout << "int ";
                            break;
                        case FLOAT_DF:
                            std::cout << "float ";
                            break;
                        case BOOL_DF:
                            std::cout << "bool ";
                            break;
                    }
                    if(suff != nullptr){
                        // std::cout << "suffixes_node (dataflow_type_node): ";
                        suff->node_print();
                    }
                    // std::cout << std::endl;
                }
        };

        class dataflow_declaration_node : public ast_node {
            private:
                std::string name;
                std::unique_ptr<dataflow_type_node> type;
            public:

                dataflow_declaration_node() = default;

                dataflow_declaration_node (std::unique_ptr<dataflow_type_node> type, std::string name) 
                    : name(name), type(std::move(type)) {}

                void accept(chips_visitor& visitor); //TODO
                
                void node_print() override {
                    if(type != nullptr){
                        type->node_print();
                    } else {
                        std::cout << "(no type) ";
                    }
                    std::cout << name;
                }
        };  
        
        // class dataflow_declarations_node : public ast_node {
        //     private:
        //         std::vector<std::unique_ptr<dataflow_declaration_node>> decls;
        //     public:

        //         dataflow_declarations_node(){}

        //         dataflow_declarations_node(dataflow_declarations_node& decls)
        //             : decls(std::move(decls.decls)) {}

        //         inline void append(std::unique_ptr<dataflow_declaration_node>& dfDecl){decls.push_back(std::move(dfDecl));};
                
                
        //         void accept(chips_visitor& visitor);

        //         inline void hello() override {std::cout << "hello from ArgDeclarationsNode\n";}
        // };

        class expressions_node : public ast_node {
            private:
                std::vector<std::unique_ptr<expression_node>> exprs;
                friend class output_node;
            public:

                expressions_node(): exprs{} {}

                expressions_node(expressions_node& exprs) : exprs(std::move(exprs.exprs)) {}
                
                inline void append(std::unique_ptr<expression_node>& expr){
                    exprs.insert(exprs.begin(), std::move(expr));
                };

                void accept(chips_visitor& visitor);

                void node_print() override {
                    for(const auto& expr : exprs){
                        expr->node_print();
                        if(exprs.back() == expr) break;
                        std::cout << ", ";
                    }
                }
        };

        inline void function_call_node::node_print() {
            std::cout << ident << "(";
            if (operands) operands->node_print();
            std::cout << ")";
        }

    }
}















#endif