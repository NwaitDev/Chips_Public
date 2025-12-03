
#ifndef DECLARATION_CTX_H
#define DECLARATION_CTX_H

#include "./chips_ast_classes.hpp"
#include "./chips_expressions.hpp"
#include <iostream>
#include <memory>
#include <vector>


/*
    Declaration context stuff
*/
namespace chips {

    inline namespace v1 {

        class preamble_node : public ast_node {
        };

        class preambles_node : public ast_node {
        private:
            std::vector<std::unique_ptr<preamble_node>> preambleList;
        public:
            preambles_node() : preambleList(std::vector<std::unique_ptr<preamble_node>>()){}
            

            preambles_node(const std::unique_ptr<preambles_node> preambles) : preambleList(std::move(preambles->preambleList)){};

            inline void append(std::unique_ptr<preamble_node> preamble){
                preambleList.insert(preambleList.begin(), std::move(preamble));
            };
            void accept(chips_visitor& visitor);

            void node_print() override {
                for (const auto& preamble : preambleList) {
                    preamble->node_print();
                    std::cout << std::endl;
                }
            }
        };

        class import_node : public preamble_node {
            private:
                const std::string name;
                const std::string path;
            public:
                import_node(std::string name, std::string path) : name(std::move(name)), path(std::move(path)) {}
                void accept(chips_visitor& visitor);
                void node_print() override {
                    std::cout << "import " << path << " as " << name << ";";
                }
        };



        class signature_node : public ast_node {
            const FUNCTION_TYPE type;
            const std::string name;
            std::unique_ptr<dataflow_declarations_node> args;
        public:
            signature_node(FUNCTION_TYPE type, std::string name, std::unique_ptr<dataflow_declarations_node> args)
                : type(std::move(type)), name(std::move(name)), args(std::move(args)) {}
            void accept(chips_visitor& visitor);
            
            void node_print() override {
                switch(type){
                    case VIRTUAL:
                        std::cout << "virtual ";
                        break;
                    case PHYSICAL:
                        std::cout << "physical ";
                        break;
                    case PURE:
                        std::cout << "pure ";
                        break;
                }
                std::cout << name << "(";
                if(args){
                    args->node_print();
                }
                std::cout << ")";
            }
        };


        class output_node : public ast_node {
        private:
            std::vector<std::unique_ptr<expression_node>> outputs;
        public:
            output_node(){}

            output_node(std::unique_ptr<expressions_node> exprs)
            : outputs(std::move(exprs->exprs)) {}

            output_node(std::unique_ptr<output_node> out)
            : outputs(std::move(out->outputs)) {}

            void accept(chips_visitor& visitor);

            void node_print() override {
                std::cout << " -> (";
                for(const auto& output : outputs){
                    output->node_print();
                    if(outputs.back() == output) break;
                    std::cout << ", ";
                }
                std::cout << ") ";
            }
        };

        class function_definition_node : public preamble_node {
            private:
                std::unique_ptr<signature_node> signature;
                std::unique_ptr<output_node> output;
                std::unique_ptr<statements_node> init;
                std::unique_ptr<statements_node> then;
            public:
                function_definition_node(std::unique_ptr<signature_node> signature, std::unique_ptr<output_node> output)
                    : signature(std::move(signature)), output(std::move(output)) {}

                function_definition_node(std::unique_ptr<signature_node> signature,
                    std::unique_ptr<statements_node> init,
                    std::unique_ptr<statements_node> then,
                    std::unique_ptr<output_node> output)
                : signature(std::move(signature)), init(std::move(init)), then(std::move(then)), output(std::move(output)) {}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    signature->node_print();
                    output->node_print();
                }

        };
    }
}

#endif