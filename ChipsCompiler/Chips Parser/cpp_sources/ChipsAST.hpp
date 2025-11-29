
#ifndef AST_H_H
#define AST_H_H

//#include "./ChipsADS.hpp"
#include "./chips_ast_classes.hpp"
#include "./chips_expressions.hpp"
#include "./chips_overall_stts.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>

// /*
//     Configuration stuff
// */

namespace chips {

    inline namespace v1 {

        class dimension_node : public ast_node {
            private:
                std::unique_ptr<number_literal_node> dimension;
            public:
                dimension_node() = default;

                dimension_node(std::unique_ptr<number_literal_node> dimension)
                    : dimension(std::move(dimension)){}

                void accept(chips_visitor& visitor);

                void node_print() override {
                    std::cout << "dimensions(";
                    if (dimension) {
                        dimension->node_print();
                    };
                    std::cout << ") ";
                }
        };

        class system_node : ast_node {
        private:
            std::unique_ptr<dimension_node> dimension = nullptr;
            std::unique_ptr<c_statements_node> sstatements;

        public:
            system_node() = default;

            system_node(std::unique_ptr<dimension_node> dimension)
                : dimension(std::move(dimension)) {}

            system_node(std::unique_ptr<dimension_node> dimension, std::unique_ptr<c_statements_node> sstatements)
                : dimension(std::move(dimension)), sstatements(std::move(sstatements)) {}

            void accept(chips_visitor& visitor){
                // TODO
            }

            void node_print() override {
                std::cout << "SYSTEM ";
                if (dimension) {
                    dimension->node_print();
                }
                std::cout << "{\n";
                if(sstatements){
                    sstatements->node_print();
                }
                std::cout << "}" << std::endl;
            }
        };


        class chips_node : ast_node {
            private:
            // std::unique_ptr<preambles_node> preambles;
            std::unique_ptr<system_node> system;

            public:
            chips_node() = default;

            chips_node(std::unique_ptr<system_node> system)
                : system(std::move(system)) {}

            // chips_node(std::unique_ptr<preambles_node>& preambles, std::unique_ptr<system_node>& system)
            //     : preambles(std::move(preambles)), system(std::move(system)) {}

            void accept(chips_visitor& visitor){
                // TODO
            }

            void node_print() override {
                // TODO: print preambles if needed
                if (system) {  // Vérifie si system contient une valeur
                    system->node_print();
                }
            }

        };
    }

}

#endif 
