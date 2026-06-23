#include "ChipsToXmiVisitor.hpp"
#include "ast_definitions.hpp"

#include "ast_builder_details.hpp"

#define UNUSED(x) (void)(x)



namespace chips {

    bool is_system_context(expression_env env){
        return env == expression_env::SYSTEM;
    } 

    std::string get_op_prefix(expression_env env){
        if(is_system_context(env)) return "chips.rvalues.datalow.operators.";
        return "chips.rvalues.primitive.operators.";
    }

    
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(mod<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(mod<" << expenv_to_string(expenv) << std::endl;
    handle_binary_expression(node.get_lhs(), node.get_rhs(), "mod");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(direct<dft, expenv>& node){
    writeAttribute("xsi:type","chips.rvalues."+expenv_to_string(expenv)+":direct_"+dft_to_string(dft));
    if constexpr(dft == dataflow_type::INT || dft == dataflow_type::FLOAT){
        if(node.get_value() > 0){
            out() << repeat("\t", nbTab) << "\n";
            writeAttribute("value", std::to_string(node.get_value()));
        }
    }else if constexpr(dft == dataflow_type::BOOL){
        if(node.get_value()){
            out() << repeat("\t", nbTab) << "\n";
            writeAttribute("value", std::to_string(node.get_value()));
        }
    }
    out() << "/>\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(variable_expression<dft,expenv>& node){

    std::string name = node.get_variable()->get_name();
    std::string path = get_ast_path_by_name(name);

    std::string type = (dynamic_cast<variable_contextual_expression<dft,expenv>*>(&node)) ? "contextual_"+dft_to_string(dft)+"_expression" :
                                                                                            dft_to_string(dft) + "_variable_expression";

    writeAttribute("xsi:type","chips.xvalues."+expenv_to_string(expenv)+":"+type);
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable",path);
    out() << "/>\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(chips::div<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(div<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_expression(node.get_lhs(), node.get_rhs(), "div");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(mult<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(mult<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_expression(node.get_lhs(), node.get_rhs(), "mult");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(minus<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(minus<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_expression(node.get_lhs(), node.get_rhs(), "minus");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(uminus_operator<dft, expenv>& node){
    out() << "<!-- UMINUS -->\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(plus<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(plus<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_expression(node.get_lhs(), node.get_rhs(), "plus");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(cast_as<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(cast_as<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    writeAttribute("xsi:type", get_op_prefix(expenv)+dft_to_string(dft)+":cast_as_"+dft_to_string(dft));
    
    
    auto numeric = node.get_cast();

    if(numeric){

        out() << ">\n" << repeat("\t", --nbTab) << "<numeric\n" << repeat("\t", ++nbTab);
        nbTab++;    

        std::cerr << "VISIT CHILDREN CAST AS " << ast_builder_detail::type_name(std::any{numeric}.type()) << std::endl;

        if constexpr(dft == dataflow_type::INT){
            void* raw = dynamic_cast<void*>(numeric); // pointe vers l'objet réel
            auto* n = static_cast<rvalue<dataflow_type::FLOAT, expenv>*>(
                dynamic_cast<rvalue<dataflow_type::FLOAT, expenv>*>(
                    reinterpret_cast<rvalue<dataflow_type::FLOAT, expenv>*>(raw)
                )
            );
            arithmetic_visit(*n);
            if(!only_one_child(*n)){
            // if(!(dynamic_cast<direct<dataflow_type::FLOAT,expenv>*>(numeric)) && !(dynamic_cast<variable_expression<dataflow_type::FLOAT,expenv>*>(numeric)) && !(dynamic_cast<function<dataflow_type::FLOAT,expenv>*>(numeric))){
                out() << repeat("\t", nbTab) << "</numeric>\n";
            }
        }else if constexpr(dft == dataflow_type::FLOAT){
            void* raw = dynamic_cast<void*>(numeric); // pointe vers l'objet réel
            auto* n = static_cast<rvalue<dataflow_type::INT, expenv>*>(
                dynamic_cast<rvalue<dataflow_type::INT, expenv>*>(
                    reinterpret_cast<rvalue<dataflow_type::INT, expenv>*>(raw)
                )
            );
            arithmetic_visit(*n);
            if(!only_one_child(*n)){
            // if(!(dynamic_cast<direct<dataflow_type::INT,expenv>*>(numeric)) && !(dynamic_cast<variable_expression<dataflow_type::INT,expenv>*>(numeric)) && !(dynamic_cast<function<dataflow_type::INT,expenv>*>(numeric))){
                out() << repeat("\t", nbTab) << "</numeric>\n";
            }
        }
    }
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(gt<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(gt<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "gt");
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(geq<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(geq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "geq");
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(lt<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(lt<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "lt");
}

template<expression_env expenv, dataflow_type dft>
void ChipsToXmiVisitor::visit(leq<expenv, dft>& node){
    std::cerr << "[DEBUG Visitor] visit(leq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "leq");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(eq<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(eq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "eq");
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(neq<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(neq<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "neq");
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(or_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(or_operator<" << expenv_to_string(expenv) << std::endl;
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "or");
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(and_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(and_operator<" << expenv_to_string(expenv) << std::endl; 
    handle_binary_boolean(node.get_lhs(), node.get_rhs(), "and");
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(not_operator<expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(not_operator<" << expenv_to_string(expenv) << std::endl;
    writeAttribute("            xsi:type", get_op_prefix(expenv)+"bool:not");
    out() << ">\n";

    auto operand = node.get_lhs();

    out() << "              <operand\n";

    if(operand){
        binary_boolean_visit(*operand);
    }

    if(dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(operand)){
        out() << "/>\n";
    }else{
        out() << "              </operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(function<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(function<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    
    std::string name = node.get_name();

    writeAttribute("xsi:type", "chips.rvalues."+expenv_to_string(expenv)+":function");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", name);
    out() << "/>\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(rvalue<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(rvalue<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    // out() << "          <rvalue\n";

    std::string rvalue_prefix = is_system_context(current_env) ? "chips.rvalues.system" : "chips.rvalues.primitive";
    std::string type = dft_to_string(dft);

    out() << repeat("\t", nbTab++) << "<rvalue\n" << repeat("\t", ++nbTab);

    if constexpr(dft != dataflow_type::BOOL){
        arithmetic_visit(node);
    }else{
        binary_boolean_visit(node);
    }
    
    // if constexpr(dft != dataflow_type::BOOL){
    //     arithmetic_visit(node);
    // }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::INT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<lt<expenv, dataflow_type::FLOAT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::INT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<gt<expenv, dataflow_type::FLOAT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::INT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<leq<expenv, dataflow_type::FLOAT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::INT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<geq<expenv, dataflow_type::FLOAT>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<eq<dataflow_type::INT, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<eq<dataflow_type::FLOAT, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<eq<dataflow_type::BOOL, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<neq<dataflow_type::INT, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<neq<dataflow_type::FLOAT, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<neq<dataflow_type::BOOL, expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<or_operator<expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<and_operator<expenv>*>(&node)){
    //     visit(*p);
    // }else if(auto* p = dynamic_cast<not_operator<expenv>*>(&node)){
    //     visit(*p);
    // }

    nbTab--; nbTab--;

    if(!only_one_child(node)){
        out() << repeat("\t", nbTab) << "</rvalue>\n";
    }
    // else if(auto* p = dynamic_cast<variable_expression<dft,expenv>*>(&node)){
    //     // visit(*p);
    //     out() << "/>\n";
    //     nbTab--; nbTab--;
    // }else{
    //     nbTab--;
    //     out() << repeat("\t", --nbTab) << "</rvalue>\n";
    // }

    
}

void ChipsToXmiVisitor::visit(ast_node& node){
    UNUSED(node);
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // out() << "    <!-- ast_node générique -->\n";

    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
        visit(*r);
    if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node))
        visit(*r);

    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    // if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node))
    //     visit(*dir);
    
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
    //     visit(*pl);
    // if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
    //     visit(*pl);
    //TODO: regarder pour regler ce probleme
}

void ChipsToXmiVisitor::visit(program_node& node){
    auto preamble = node.get_preamble();
    auto system = node.get_system();
    std::cerr << "PREAMBLE SIZE: " << preamble.get_definitions().size() << std::endl;
    std::cerr << "SYSTEM SIZE: " << system.get_statements().size() << std::endl;
    if(!preamble.get_definitions().empty()){
        push_ast_path("/@preamble");
        out() << repeat("\t", nbTab) << "<preamble>\n";
        nbTab++;
        preamble.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</preamble>\n";
        pop_ast_path("/@premble");
    }
    if(!system.get_statements().empty()){
        push_ast_path("/@system");
        out() << repeat("\t", nbTab) << "<system>\n";
        nbTab++;
        system.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</system>\n";
        pop_ast_path("/@system");
    }
}

void ChipsToXmiVisitor::visit(system_section_node& node){
    out() << "<!-- TODO -->\n";
}

void ChipsToXmiVisitor::visit(preamble_section_node& node){
    int index = 0;
    for(auto definition : node.get_definitions()){
        std::string segment = "/@definitions." + std::to_string(index++);
        push_ast_path(segment);
        out() << repeat("\t", nbTab) << "<definitions\n";
        if(auto* logical = std::get_if<logical_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "logical";
        }else if(auto* physical = std::get_if<physical_definition*>(&definition)){
            nbTab++;
            if(*physical){
                std::cout << ast_builder_detail::type_name(std::any{physical}.type()) << std::endl;
                (*physical)->accept(*this);
            }
            nbTab--;

        }else if(auto* object = std::get_if<object_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "object";
        }else if(auto* collective = std::get_if<collective_function_definition*>(&definition)){
            out() << repeat("\t", nbTab) << "collective";
        }
        out() << repeat("\t", nbTab) << "</definitions>\n";
        pop_ast_path(segment);
    }
}

void ChipsToXmiVisitor::visit(physical_definition& node){
    current_env = expression_env::PRIMITIVE;
    // Enregistrer la définition physique dans la table des symboles
    // Le chemin est : //@preamble/@definitions.X (déterminé par le contexte d'appel)
    register_variable(node.get_name(), get_ast_path(), "physical");

    // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
    int def_index = 0;
    std::string path = get_ast_path();
    size_t pos = path.rfind("@definitions.");
    if(pos != std::string::npos){
        try{
            def_index = std::stoi(path.substr(pos + 13));
        }catch(...){
            def_index = 0;
        }
    }

    // Register the definition in the definitions table
    register_definition(node.get_name(), "physical", get_ast_path(), def_index);
    m_current_definition = node.get_name();

    std::cerr << "[DEBUG] Physical definition '" << node.get_name() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    nbTab++;
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", "definitions:physical_definition");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", node.get_name());
    out() << ">\n";
    nbTab--;

    // Enregistrer les paramètres (sensors, actuators, etc.) dans la table des symboles
    int sensor_index = 0;
    for(auto& param : node.get_sensors()){
        if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::INT);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                // node_param->accept(*this);
                sensor_index++;
            }
        }else if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::FLOAT);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                // node_param->accept(*this);
                sensor_index++;
            }
        }else if(auto* p = std::get_if<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>(&param)){
            if(*p){
                auto node_param = *p;
                std::string param_name = node_param->get_name();
                std::string dft = dft_to_string(dataflow_type::BOOL);
                std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
                std::string param_path = sensor_base_path + "/@declaration/@variable";
                register_variable(param_name, param_path, "sensor:" + dft);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                // node_param->accept(*this);
                sensor_index++;
            }
        }
    }

    auto with = node.get_with_section();
    if(!with.get_statements().empty()){
        push_ast_path("/@with");
        out() << repeat("\t", nbTab) << "<with>\n";
        nbTab++;
        with.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</with>\n";
        pop_ast_path("/@with");
    }

    auto parameters = node.get_parameters();
    if(!parameters.empty()){
        param_index = 0;
        for(auto& parameter : parameters){
            std::visit([this](auto* param) {
                if(param){
                    out() << repeat("\t", nbTab) << "<parameters\n";


                    nbTab++;
                    std::string param_name = param->get_name();
                    dataflow_type param_type = get_dataflow_type(param);
                    std::string dft = dft_to_string(param_type);

                    std::string param_base_path = get_ast_path() + "/@parameters." + std::to_string(param_index);
                    std::string param_path = param_base_path + "/@declaration/@variable";

                    std::cerr << "[DEBUG] Paramètre logique '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;

                    std::cerr << "[DEBUG] Génération balise <parameters> pour '" << param_name << "'" << std::endl;
                    push_ast_path(param_path);
                    register_variable(param_name, param_path, "logical_parameter:" + dft);

                    nbTab++;
                    out() << repeat("\t", nbTab);
                    writeAttribute("xsi:type", "chips.parameters.logical:" + dft + "_logical_parameter");
                    out() << "\n" << repeat("\t", nbTab);
                    writeAttribute("name", param_name);
                    out() << ">\n";
                    nbTab--;

                    out() << repeat("\t", nbTab) << "<declaration>\n";
                    push_ast_path("/@declaration");
                    nbTab++;
                    out() << repeat("\t", nbTab) << "<variable\n";
                    nbTab++;
                    out() << repeat("\t", nbTab);
                    writeAttribute("name", param_name);
                    out() << "/>\n";
                    pop_ast_path("/@declaration");
                    nbTab--;
                    nbTab--;
                    out() << repeat("\t", nbTab) << "</declaration>\n";

                    if(param->get_default_value().has_value()){
                        out() << repeat("\t", nbTab) << ("<!-- TODO IF NODE XMI -->\n");
                        // auto default_value = param->get_default_value().value();
                        // out() << repeat("\t", nbTab) << "<default_value\n";
                        // nbTab++; nbTab++;
                        // out() << repeat("\t", nbTab);
                        // writeAttribute("xsi:type", "chips.rvalues.primitive:direct"+dft);
                        // out() << "\n" << repeat("\t", nbTab);
                        // writeAttribute("value", )
                    }   

                    std::cerr << "[DEBUG] Balise <parameters> terminée pour '" << param_name << "'" << std::endl;
                    pop_ast_path(param_path);
                    dumpSymbolTable();
                    param_index++;
                    nbTab--;
                    out() << repeat("\t", nbTab) << "</parameters>\n";
                }
            }, parameter);
        }
    }

    auto init = node.get_init_section();
    if(!init.get_statements().empty()){
        push_ast_path("/@init");
        out() << repeat("\t", nbTab) << "<init>\n";
        nbTab++;
        init.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</init>\n";
        pop_ast_path("/@init");
    }

    auto then = node.get_then_section();
    if(!then.get_statements().empty()){
        push_ast_path("/@then");
        out() << repeat("\t", nbTab) << "<then>\n";
        nbTab++;
        then.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</then>\n";
        pop_ast_path("/@then");
    }
}

template<node_element ne>
void ChipsToXmiVisitor::handle_node_element_declaration(node_element_declaration<ne>& node){
    if constexpr(ne != node_element::CHANNEL){
        std::string identifier = node.get_name();
        std::string segment = "/@variable";
        push_ast_path(segment);

        // Enregistrer le ctx dans la table des symboles
        // Le chemin du ctx est juste get_ast_path() car on est déjà dans /@with/@statements.X
        register_variable(identifier, get_ast_path(), "ctx");
        std::string type = statement_type("contextual_"+dft_to_string(ne_to_dft(ne))+"_declaration", StatementFamily::Node);

        // Also register in the current definition if we're in one
        if (!m_current_definition.empty()) {
            register_definition_variable(m_current_definition, identifier, get_ast_path(), "ctx");
        }

        nbTab++;
        out() << repeat("\t", nbTab);
        writeAttribute("xsi:type", type);
        out() << "\n" << repeat("\t", nbTab);
        writeAttribute("identifier", identifier);
        out() << ">\n";

        out() << repeat("\t", nbTab) << "<variable\n";
        nbTab++;
        out() << repeat("\t", nbTab);
        writeAttribute("name", identifier);
        out() << "/>\n"; 
        nbTab--;
        nbTab--;
        pop_ast_path(segment);
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::handle_binary_expression(rvalue<dft,expenv>* left, rvalue<dft,expenv>* right, const std::string& type){
    writeAttribute("xsi:type",get_op_prefix(expenv)+dft_to_string(dft)+":"+type);
    out() << ">\n";

    out() << repeat("\t", --nbTab) << "<left_operand\n";
    nbTab++;
    out() << repeat("\t", ++nbTab);

    if(left){
        std::cerr << "left->accept()" << std::endl;
        arithmetic_visit(*left);
    }

    if(!only_one_child(*left)){
        out() << repeat("\t", nbTab) << "</left_operand>\n";
    }

    out() << repeat("\t", nbTab) << "<right_operand\n";
    nbTab++;
    out() << repeat("\t", ++nbTab);

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(!only_one_child(*right)){
        out() << repeat("\t", nbTab) << "</right_operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::handle_binary_boolean(rvalue<dft,expenv>* left, rvalue<dft,expenv>* right, const std::string& type){
    if(type == "and" || type == "or"){
        writeAttribute("xsi:type", get_op_prefix(expenv)+"bool:"+type);
    }else{
        writeAttribute("xsi:type", get_op_prefix(expenv)+"bool:"+type+"_"+dft_to_string(dft));
    }
    
    
    out() << ">\n" << repeat("\t", nbTab) << "<left_operand\n" << repeat("\t", nbTab);

    if(left){
        std::cerr << "left->accept()" << std::endl;
        binary_boolean_visit(*left);
    }

    if(!only_one_child(*left)){
        out() << repeat("\t", nbTab) << "</left_operand>\n";
    }

    out() << repeat("\t", nbTab) << "<right_operand\n" << repeat("\t", nbTab);

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    }

    if(!only_one_child(*right)){
        out() << repeat("\t", nbTab) << "</right_operand>\n";
    }
}

void ChipsToXmiVisitor::visit(with_section& node){
    int index = 0;
    for(auto& statement : node.get_statements()){
        std::string segment = "/@statements."+std::to_string(index++);
        push_ast_path(segment);
        out() << repeat("\t", nbTab) << "<statements\n";
        if(auto* if_stt = std::get_if<node_statement<recurring_statement::IF>*>(&statement)){
            out() << ("<!-- TODO IF NODE XMI -->\n");
        }else if(auto* foreach = std::get_if<node_statement<recurring_statement::FOREACH>*>(&statement)){
            out() << ("<!-- TODO FOREACH NODE XMI-->\n");
        }else if(auto* channel = std::get_if<node_element_declaration<node_element::CHANNEL>*>(&statement)){

            auto node_channel = *channel;

            std::string type_id = node_channel->get_variable();
            std::string name = node_channel->get_name();
            std::string type = statement_type("channel_declaration", StatementFamily::Node);

            // Enregistrer le channel dans la table des symboles
            // Le chemin du channel est juste get_ast_path() car on est déjà dans /@with/@statements.X
            register_variable(name, get_ast_path(), "channel");

            // Also register in the current definition if we're in one
            if (!m_current_definition.empty()) {
                register_definition_variable(m_current_definition, name, get_ast_path(), "channel");
            }

            std::cerr << "[DEBUG] Channel '" << name << "' enregistré avec le chemin: " << get_ast_path() << std::endl;

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type", type);
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("name", name+"_"+toLower(m_current_definition));
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("type_identifier", type_id);
            out() << "/>\n";
            nbTab--;

        }else if(auto* ctx_int = std::get_if<node_element_declaration<node_element::CONTEXTUAL_INT>*>(&statement)){
            handle_node_element_declaration(*(*ctx_int));
        }else if(auto* ctx_float = std::get_if<node_element_declaration<node_element::CONTEXTUAL_FLOAT>*>(&statement)){
            handle_node_element_declaration(*(*ctx_float));
        }else if(auto* ctx_bool = std::get_if<node_element_declaration<node_element::CONTEXTUAL_BOOL>*>(&statement)){
            handle_node_element_declaration(*(*ctx_bool));
        }
        pop_ast_path(segment);
    }
    out() << repeat("\t", nbTab) << "</statements>\n";
}

template<dataflow_type dft, statement_env stenv>
void ChipsToXmiVisitor::handle_statement_declaration(dataflow_declaration<dft, stenv>& node){
    std::string type = dft_to_string(dft);
    std::string name = node.get_variable().get_name();
    out() << repeat("\t", ++nbTab);
    writeAttribute("xsi:type", statement_type(type+"_declaration"));
    out() << ">\n";
    nbTab--;

    std::string segment = "/@variable";
    push_ast_path(segment);
    std::string declarated_var_path = get_ast_path();
    register_variable(name, declarated_var_path, type);
    
    std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << declarated_var_path << std::endl;

    out() << repeat("\t", nbTab++) << "<variable\n" << repeat("\t", nbTab);
    writeAttribute("name", name);
    out() << "/>\n";
    nbTab--;
    pop_ast_path(segment);

    auto dims = node.get_variable().get_dimensions();

    if(!dims.empty()){
        out() << "<!-- TODO SUFFIXES -->\n";
    }
}

template<dataflow_type dft, statement_env stenv>
void ChipsToXmiVisitor::handle_statement_assignment(dataflow_assignment<dft, stenv>& node){

    std::string xvalue_prefix = is_system_context(current_env) ? "chips.xvalues.system" : "chips.xvalues.primitive";

    std::string type = dft_to_string(dft);
    std::string name = "";
    std::string value = "";

    if(auto* lvalue = dynamic_cast<variable_expression<dft, expression_env::PRIMITIVE>*>(node.get_lhs())){
        if(auto* clvalue = dynamic_cast<variable_contextual_expression<dft, expression_env::PRIMITIVE>*>(lvalue)){
            value = "contextual_"+type+"_expression";
        }else{
            value = type+"_variable_expression";
        }
        name = lvalue->get_variable()->get_name();
    }else if(auto* lvalue = dynamic_cast<variable_expression<dft, expression_env::COLLECTIVE>*>(node.get_lhs())){
        if(auto* clvalue = dynamic_cast<variable_contextual_expression<dft, expression_env::COLLECTIVE>*>(lvalue)){
            value = "contextual_"+type+"_expression";
        }else{
            value = type+"_variable_expression";
        }
        name = lvalue->get_variable()->get_name();
    }else if(auto* lvalue = dynamic_cast<variable_expression<dft, expression_env::SYSTEM>*>(node.get_lhs())){
        if(auto* clvalue = dynamic_cast<variable_contextual_expression<dft, expression_env::SYSTEM>*>(lvalue)){
            value = "contextual_"+type+"_expression";
        }else{
            value = type+"_variable_expression";
        }
        name = lvalue->get_variable()->get_name();
    }

    std::string path = get_ast_path_by_name(name);

    out() << repeat("\t", ++nbTab);
    writeAttribute("xsi:type", statement_type(type+"_assignment"));
    out() << ">\n";
    nbTab--;

    out() << repeat("\t", nbTab++) << "<lvalue\n" << repeat("\t", ++nbTab);
    writeAttribute("xsi:type", xvalue_prefix+":"+value);
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable", path);
    out() << "/>\n";
    nbTab--;
    nbTab--;

    node.get_rhs()->accept(*this);
}

void ChipsToXmiVisitor::visit(init_section& node){

    auto statements = node.get_statements();
    int index = 0;

    for(auto& statement : statements){

        std::string segment = "/@statements."+std::to_string(index++);
        push_ast_path(segment);
        std::cerr << "[XMI DEBUG] init_section statement variant index=" << statement.index() << std::endl;
        out() << repeat("\t", nbTab) << "<statements\n";
        nbTab++;
        if(auto* decl = std::get_if<primitive_statement<recurring_statement::DECLARATION>*>(&statement)){
            auto node_decl = *decl;
            if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }else if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }else if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }
        }else if(auto* assign = std::get_if<primitive_statement<recurring_statement::ASSIGNMENT>*>(&statement)){
            auto node_assign = *assign;
            if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else{
                std::cerr << "[XMI WARNING] ASSIGNMENT variant selected, but concrete assignment type could not be identified" << std::endl;
            }
        }
        nbTab--;
        pop_ast_path(segment);
        out() << repeat("\t", nbTab) << "</statements>\n";
    }
    
}

void ChipsToXmiVisitor::visit(then_section& node){

    auto statements = node.get_statements();
    int index = 0;

    for(auto& statement : statements){

        std::string segment = "/@statements."+std::to_string(index++);
        push_ast_path(segment);
        std::cerr << "[XMI DEBUG] then_section statement variant index=" << statement.index() << std::endl;
        out() << repeat("\t", nbTab) << "<statements\n";
        nbTab++;
        if(auto* decl = std::get_if<primitive_statement<recurring_statement::DECLARATION>*>(&statement)){
            auto node_decl = *decl;
            if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }else if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }else if(auto node = dynamic_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>*>(node_decl)){
                handle_statement_declaration(*node);
            }
        }else if(auto* assign = std::get_if<primitive_statement<recurring_statement::ASSIGNMENT>*>(&statement)){
            auto node_assign = *assign;
            if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else if(auto node = dynamic_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>*>(node_assign)){
                handle_statement_assignment(*node);
            }else{
                std::cerr << "[XMI WARNING] ASSIGNMENT variant selected, but concrete assignment type could not be identified" << std::endl;
            }
        }else{
            out() << "<!-- PROBLEME -->\n";
        }
        nbTab--;
        pop_ast_path(segment);
        out() << repeat("\t", nbTab) << "</statements>\n";
    }

}

void ChipsToXmiVisitor::visit(logical_definition& node){
    current_env = expression_env::PRIMITIVE;
    out() << "<!-- TODO logical -->\n";
}

void ChipsToXmiVisitor::writeAttribute(const std::string& name, const std::string& value){
    std::string normalized = name;
    while (!normalized.empty() && (normalized.front() == ' ' || normalized.front() == '\t')){
        normalized.erase(normalized.begin());
    }

    if(normalized == "xsi:type"){
        ensure_namespace_for_type(value);
    }
    out() << " " << name << "=\"" << value << "\"";
}

void ChipsToXmiVisitor::ensure_namespace_for_prefix(const std::string& ns_prefix){
    if (ns_prefix.empty()){
        return;
    }

    std::string suffix = ns_prefix;
    if (suffix.rfind("chips.", 0) == 0){
        suffix = suffix.substr(6);
    }

    size_t pos = 0;
    while ((pos = suffix.find('.', pos)) != std::string::npos){
        suffix.replace(pos, 1, "/");
        pos++;
    }

    std::string url = suffix.empty() || suffix[0] != '/'
                          ? "http://chips/" + suffix
                          : "http://chips" + suffix;
    m_writer.add_namespace_if_needed(ns_prefix, url);
}

void ChipsToXmiVisitor::ensure_namespace_for_type(const std::string& type_value){
    size_t colon_pos = type_value.find(':');
    if (colon_pos == std::string::npos){
        return;
    }
    ensure_namespace_for_prefix(type_value.substr(0, colon_pos));
}

ChipsToXmiVisitor::StatementFamily ChipsToXmiVisitor::detect_statement_family() const
{
    const std::string &path = m_current_ast_path;

    if (path.find("/@system") != std::string::npos)
    {
        return StatementFamily::System;
    }
    if (path.find("/@operations") != std::string::npos)
    {
        return StatementFamily::Collective;
    }
    if (path.find("/@having") != std::string::npos)
    {
        return StatementFamily::Implementation;
    }
    if (path.find("/@with") != std::string::npos)
    {
        return StatementFamily::Node;
    }
    if (path.find("/@init") != std::string::npos || path.find("/@then") != std::string::npos)
    {
        return StatementFamily::Primitive;
    }

    return StatementFamily::Primitive;
}

std::string ChipsToXmiVisitor::statement_prefix(StatementFamily family) const
{
    if (family == StatementFamily::Auto)
    {
        family = detect_statement_family();
    }

    switch (family)
    {
    case StatementFamily::System:
        return "chips.statements.system";
    case StatementFamily::Node:
        return "chips.statements.node";
    case StatementFamily::Collective:
        return "chips.statements.collective";
    case StatementFamily::Implementation:
        return "chips.statements.implementation";
    case StatementFamily::Primitive:
    case StatementFamily::Auto:
    default:
        return "chips.statements.primitive";
    }
}

std::string ChipsToXmiVisitor::statement_type(const std::string &suffix, StatementFamily family) const
{
    return statement_prefix(family) + ":" + suffix;
}

void ChipsToXmiVisitor::report_semantic_error(const std::string &message)
{
    m_semantic_errors.push_back(message);
    std::cerr << "[SEMANTIC ERROR] " << message << std::endl;
}

std::string ChipsToXmiVisitor::get_ast_path_by_name(const std::string &name)
{
    // Rechercher dans la table des symboles (case-sensitive)
    auto it = m_symbol_table.find(name);
    if (it != m_symbol_table.end())
    {
        std::cerr << ">>>>>>>>>[DEBUG PATH] Variable '" << name << "' trouvée dans la table des symboles: " << it->second.path << " (type: " << it->second.type << ")" << std::endl;
        return it->second.path;
    }

    // Si non trouvé, essayer une recherche case-insensitive
    std::string lower_name = name;
    std::transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);
    
    for (const auto &entry : m_symbol_table)
    {
        std::string lower_key = entry.first;
        std::transform(lower_key.begin(), lower_key.end(), lower_key.begin(), ::tolower);
        
        if (lower_key == lower_name)
        {
            std::cerr << ">>>>>>>>>[DEBUG PATH] Variable '" << name << "' trouvée (case-insensitive, clé: '" << entry.first << "'): " << entry.second.path << " (type: " << entry.second.type << ")" << std::endl;
            return entry.second.path;
        }
    }

    std::cerr << ">>>>>>>>>[WARNING] Variable '" << name << "' NON trouvée dans la table des symboles" << std::endl;
    report_semantic_error("Undefined variable: " + name);
    return name; // Fallback: retourner juste le nom
}