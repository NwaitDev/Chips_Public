#ifndef CHIPS_SYMBOL_TABLE_HPP
#define CHIPS_SYMBOL_TABLE_HPP

#include <any>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <stdexcept>
#include <iostream>

#include "metamodel_enums.hpp"
#include "ast_builder_details.hpp"

namespace chips {
    class SymbolTable {
        public:


            static SymbolTable& getInstance() {
                static SymbolTable instance;
                return instance;
            }

            SymbolTable(const SymbolTable&) = delete;
            SymbolTable& operator=(const SymbolTable&) = delete;


            void enterScope(){
                scopes.emplace_back();
            }

            void exitScope(){
                if(scopes.empty()){
                    throw std::runtime_error("No scope to exit");
                }
                scopes.pop_back();
            }

            bool declareVariable(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::VARIABLE);
            }

            bool declareContextualVariable(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::VARIABLE_CONTEXTUAL);
            }

            bool declareSensorVariable(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::VARIABLE_SENSOR);
            }

            bool declareChannel(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::CHANNEL);
            }

            bool declareFunctionLogical(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::FUNCTION_LOGICAL);
            }

            bool declareFunctionPhysical(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::FUNCTION_PHYSICAL);
            }

            bool declareObject(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::OBJECT);
            }

            bool declareFunctionSpread(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::FUNCTION_SPREAD);
            }

            bool declareFunctionCollect(const std::string& name, const std::any& value){
                return declare(name, value, SymbolKind::FUNCTION_COLLECT);
            }

            bool declareBlock(const std::string& type, const std::string& name, const std::any& value){
                bool res = declare(name, value, SymbolKind::BLOCK);
                if(!res) return res;
                declarated_block_system[name] = type;
                return res;
            }

            void declareTypeOfDeclaratedBlock(const std::string& type, const std::string& variable){
                declarated_block_system[variable] = type;
            }

            bool declareFunctionOutput(const std::string& fname, const std::string& output, const std::any& value){
                for(const auto& [k1, v1] : function_outputs){
                    for(const auto& [k2, v2]: v1){
                        if(fname == k1 && output == k2) return false;
                    }
                }
                function_outputs[fname][output] = value;
                return true;
            }

            bool declareFunctionParameter(const std::string& fname, const std::string& parameter, const std::any& value){
                for(const auto& [k1, v1] : function_parameters){
                    for(const auto& [k2, v2] : v1){
                        if(fname == k1 && parameter == k2){
                            std::cout << fname << " " << parameter << "already in scope" << std::endl;
                            return false;
                        }
                        // } return false;
                    }
                }
                function_parameters[fname][parameter] = value;
                return true;
            }

            std::optional<std::any> lookupVariable(const std::string& name) const{
                return lookup(name, SymbolKind::VARIABLE);
            }

            std::optional<std::any> lookupContextualVariable(const std::string& name) const {
                return lookup(name, SymbolKind::VARIABLE_CONTEXTUAL);
            }

            std::optional<std::any> lookupSensorVariable(const std::string& name){
                return lookup(name, SymbolKind::VARIABLE_SENSOR);
            }

            std::optional<std::any> lookupChannel(const std::string& name){
                return lookup(name, SymbolKind::CHANNEL);
            }

            std::optional<std::any> lookupFunctionLogical(const std::string& name) const{
                return lookup(name, SymbolKind::FUNCTION_LOGICAL);
            }

            // std::optional<std::any> lookupFunctionPhysical(const std::string& name) const{
            //     return lookup(name, SymbolKind::FUNCTION_PHYSICAL);
            // }

            /**
             * Retourne un noeud de type node qui est soit:
             * - physical
             * - object
             */
            std::optional<std::any> lookupNodeDefinition(const std::string& name){
                std::optional<std::any> res = lookup(name, SymbolKind::FUNCTION_PHYSICAL);
                if(res.has_value()) return res;
                return lookup(name, SymbolKind::OBJECT);
            }

            std::optional<std::any> lookupFunctionSpread(const std::string& name) const{
                return lookup(name, SymbolKind::FUNCTION_SPREAD);
            }

            std::optional<std::any> lookupFunctionCollect(const std::string& name) const{
                return lookup(name, SymbolKind::FUNCTION_COLLECT);
            }

            std::optional<std::any> lookupBlock(const std::string& name) const{
                return lookup(name, SymbolKind::BLOCK);
            }

            std::optional<std::any> lookupOutput(const std::string& fname, const std::string& output) const{
                for(auto it = function_outputs.cbegin(); it != function_outputs.cend(); it++){
                    if(it->first == fname){
                        auto second = it->second;
                        for(auto it2 = second.cbegin(); it2 != second.cend(); it2++){
                            if(it2->first == output){
                                return it2->second;
                            }
                        }
                    }
                }
                return std::nullopt;
            }

            std::optional<std::any> lookupParameter(const std::string& fname, const std::string& parameter) const{
                for(auto it = function_parameters.cbegin(); it != function_parameters.cend(); it++){
                    if(it->first == fname){
                        auto second = it->second;
                        for(auto it2 = second.cbegin(); it2 != second.cend(); it2++){
                            if(it2->first == parameter){
                                return it2->second;
                            }
                        }
                    }
                }
                return std::nullopt;
            }

            std::string getTypeOfDeclaratedBlock(const std::string& variable){
                return declarated_block_system[variable];
            }

            void dump() const {
                std::cout << "===== Symbol Table =====\n";
                int level = scopes.size();
                for (const auto& scope : scopes) {
                    std::cout << "Scope " << level-- << ":\n";
                    for (const auto& [k, v] : scope) {
                        std::cout << "  " << k << " (" << SymbolKindToString(v.kind) << " " << ast_builder_detail::type_name(v.value.type()) <<")\n";
                    }
                }
                std::cout << "===== Symbol Table Output =====\n";
                for(const auto& [fname, v] : function_outputs){
                    for(const auto& [output, value] : v){
                        std::cout << fname << " " << output << " (" << ast_builder_detail::type_name(value.type()) << ")\n";
                    }
                }
                std::cout << "===== Symbol Table Parameter =====\n";
                for(const auto& [fname, v] : function_parameters){
                    for(const auto& [param, value]: v){
                        std::cout << fname << " " << param << "(" << ast_builder_detail::type_name(value.type()) << ")\n";
                    }
                }
                std::cout << "===== Symbol Table Declared Block =====\n";
                for(const auto& [k, v] : declarated_block_system){
                    std::cout << k << " " << v << std::endl;
                }
                std::cout << "========================\n";
            }

        private:
            

            enum SymbolKind{
                VARIABLE,
                VARIABLE_SENSOR,
                VARIABLE_CONTEXTUAL,
                FUNCTION_LOGICAL,
                FUNCTION_PHYSICAL,
                FUNCTION_SPREAD,
                FUNCTION_COLLECT,
                OBJECT,
                CHANNEL,
                BLOCK,
            };

            std::string SymbolKindToString(SymbolKind kind) const{
                switch(kind){
                    case VARIABLE: return "variable";
                    case VARIABLE_SENSOR: return "variable sensor";
                    case VARIABLE_CONTEXTUAL: return "variable contextual";
                    case FUNCTION_LOGICAL: return "function logical";
                    case FUNCTION_PHYSICAL: return "function physical";
                    case FUNCTION_SPREAD: return "function spread";
                    case FUNCTION_COLLECT: return "function collect";
                    case OBJECT: return "object";
                    case CHANNEL: return "channel";
                    case BLOCK: return "block";
                }
                return "NOTHING FOUND HERE";
            }

            struct Symbol{
                std::any value;
                std::string name;
                SymbolKind kind;

                bool operator<(const Symbol& other) const {
                    return name < other.name && kind < other.kind;
                }

                bool operator==(const Symbol& other) const {
                    return name == other.name && kind == other.kind;
                }
            };

            SymbolTable() = default;

            void printScope(std::unordered_map<std::string, Symbol> scope){
                std::cout << "SCOPE:\n";
                for(const auto& [k, v] : scope){
                    std::cout << "  " << k << "(" << SymbolKindToString(v.kind) << " " << ast_builder_detail::type_name(v.value.type()) <<")\n";
                }
            }

            bool declare(const std::string& name, const std::any& value, const SymbolKind kind){
                if(scopes.empty()) enterScope();

                
                
                auto& current = scopes.back();

                // dump();
                // printScope(current);

                Symbol sym;
                sym.value = value;
                sym.name = name;
                sym.kind = kind;

                for(const auto& [k, v] : current){
                    if(k == name && v.kind == kind) return false;
                }

                current[name] = sym;
                return true;
            }

            std::optional<std::any> lookup(const std::string& name, const SymbolKind kind) const{
                for(auto it = scopes.rbegin(); it != scopes.rend(); ++it){
                    auto found = it->find(name);
                    if(found != it->end() && found->second.kind == kind){
                        return found->second.value;
                    }
                }
                return std::nullopt;
            }

            std::vector<std::unordered_map<std::string, Symbol>> scopes;
            // std::vector<std::unordered_map<std::string, std::any>> scopes;

            // to get the function output of a function
            std::unordered_map<std::string, std::unordered_map<std::string, std::any>> function_outputs;
            std::unordered_map<std::string, std::unordered_map<std::string, std::any>> function_parameters;

            std::unordered_map<std::string, std::string> declarated_block_system;
    };
}

#endif