#include "ChipsToXmiVisitor.hpp"
#include "ast_definitions.hpp"

#include "ast_builder_details.hpp"

#define UNUSED(x) (void)(x)



namespace chips {

    bool is_system_context(expression_env env){
        return env == expression_env::SYSTEM;
    } 

    std::string get_op_prefix(expression_env env){
        if(is_system_context(env)) return "chips.rvalues.dataflow.operators.";
        if(env == expression_env::COLLECTIVE) return "chips.rvalues.collective.operators.";
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
        out() << repeat("\t", nbTab) << "\n";
        writeAttribute("value", std::to_string(node.get_value()));
    }else if constexpr(dft == dataflow_type::BOOL){
        out() << repeat("\t", nbTab) << "\n";
        writeAttribute("value", node.get_value() ? "true" : "false");
    }
    out() << "/>\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(variable_expression<dft,expenv>& node){

    std::string name = node.get_variable()->get_name();
    dumpSymbolTable();
    std::cerr << "NAME VAIRABLE " << name << std::endl;
    std::string path = get_ast_path_by_name(name);
    std::vector<int_rvalue_expression_variant<expenv>>& index = node.get_index();

    std::string type = (dynamic_cast<variable_contextual_expression<dft,expenv>*>(&node)) ? "contextual_"+dft_to_string(dft)+"_expression" :
                                                                                            dft_to_string(dft) + "_variable_expression";

    writeAttribute("xsi:type","chips.xvalues."+expenv_to_string(expenv)+":"+type);
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable",path);
    
    if(!index.empty()){
        out() << ">\n";
        for(auto inde : index){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }

        
    }else{
        out() << "/>\n";
    }
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
    std::cerr << "[DEBUG Visitor] visit(uminus<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    direct<dft,expenv> zero(0);
    handle_binary_expression(&zero, node.get_rhs(), "minus");
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

    writeAttribute("xsi:type", get_op_prefix(expenv)+"bool:not");
    out() << ">\n";

    auto operand = node.get_lhs();

    out() << repeat("\t", nbTab) << "<operand\n" << repeat("\t", nbTab);

    if(operand){
        binary_boolean_visit(*operand);
    }

    if(!only_one_child(*operand)){
        out() << repeat("\t", nbTab) << "</operand>\n";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(function<dft,expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(function<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    
    std::string name = node.get_name();
    std::vector<rvalue_variant<expenv>>& parameters = node.get_parameters();

    writeAttribute("xsi:type", "chips.rvalues."+expenv_to_string(expenv)+":function");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", name);
    if(parameters.empty()){
        out() << "/>\n";
    }else{
        out() << ">\n";
    }
    
    if(!parameters.empty()){
        for(auto parameter : parameters){
            std::visit([&](auto param){
                out() << repeat("\t", nbTab) << "<parameters\n" << repeat("\t", nbTab);

                using ParamT = std::remove_cv_t<std::remove_pointer_t<decltype(param)>>;

                if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::BOOL, expenv>>){
                    std::cerr << "BINARY 2" << name << "\n";
                    binary_boolean_visit(*param);
                }else if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::INT, expenv>> || 
                                    std::is_same_v<ParamT, rvalue<dataflow_type::FLOAT, expenv>>){
                    std::cerr << "ARITH 2" << name << "\n";
                    arithmetic_visit(*param);
                }else{
                    out() << ast_builder_detail::type_name(std::any{param}.type()) << "\n";
                }

                if(!only_one_child(*param)){
                    out() << repeat("\t", nbTab) << "</parameters>\n";
                }
            }, parameter);
        }
    }
}

void ChipsToXmiVisitor::visit(input& node){
    writeAttribute("xsi:type","chips.rvalues.collective:input_kw");
    out() << "/>\n";
}

void ChipsToXmiVisitor::visit(stop& node){
    writeAttribute("xsi:type","chips.rvalues.collective:stop_kw");
    out() << "/>\n";
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(rvalue<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(rvalue<" << dft_to_string<dft>() << ", " << expenv_to_string(expenv) << std::endl;
    // out() << "          <rvalue\n";
    std::string rvalue_prefix;

    if(!is_system_context(current_env)){
        if(current_env == expression_env::COLLECTIVE){
            rvalue_prefix = "chips.rvalues.collective";
        }else{
            rvalue_prefix = "chips.rvalues.primitive";
        }
    }else{
        rvalue_prefix = "chips.rvalues.system";
    }

    std::string type = dft_to_string(dft);

    out() << repeat("\t", nbTab++) << "<rvalue\n" << repeat("\t", ++nbTab);

    // if(auto* in = dynamic_cast<input*>(&node)){
    //     (*in).accept(*this);
    //     nbTab--; nbTab--;
    //     return;
    // }else if(auto* st =dynamic_cast<stop*>(&node)){
    //     (*st).accept(*this);
    //     nbTab--; nbTab--;
    // }else{
        if constexpr(dft != dataflow_type::BOOL){
        arithmetic_visit(node);
        }else{
            binary_boolean_visit(node);
        }

        nbTab--; nbTab--;

        if(!only_one_child(node)){
            out() << repeat("\t", nbTab) << "</rvalue>\n";
        }   
    // }

    

     
}

void ChipsToXmiVisitor::visit(ast_node& node){
    UNUSED(node);
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // out() << "    <!-- ast_node générique -->\n";

    if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node)){
        visit(*r);
    }else if(auto* r = dynamic_cast<rvalue<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node)){
        visit(*r);
    }
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
        pop_ast_path("/@preamble");
    }
    if(!system.get_statements().empty()){
        current_env = expression_env::SYSTEM;
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
    int system_index = 0;

    for(auto stt : node.get_statements()){
        std::string segment = "/@system." + std::to_string(system_index++);
        push_ast_path(segment);
        out() << repeat("\t", nbTab) << "<system_statements\n";

        if(auto* if_stt = std::get_if<system_statement<recurring_statement::IF>*>(&stt)){
            if(auto* if_else_stt = dynamic_cast<if_else_statement<statement_env::SYSTEM>*>(*if_stt)){
                handle_statement_if_else(*if_else_stt);
            }else if(auto* if_st = dynamic_cast<if_statement<statement_env::SYSTEM>*>(*if_stt)){
                handle_statement_if(*if_st);
            }
        }else if(auto* foreach = std::get_if<system_statement<recurring_statement::FOREACH>*>(&stt)){
            if(auto* foreach_int = dynamic_cast<foreach_statement<statement_env::SYSTEM, dataflow_type::INT>*>(*foreach)){
                handle_foreach(*foreach_int);
            }else if(auto* foreach_float = dynamic_cast<foreach_statement<statement_env::SYSTEM, dataflow_type::FLOAT>*>(*foreach)){
                handle_foreach(*foreach_float);
            }else if(auto* foreach_bool = dynamic_cast<foreach_statement<statement_env::SYSTEM, dataflow_type::BOOL>*>(*foreach)){
                handle_foreach(*foreach_bool);
            } 
        }else if(auto* decl = std::get_if<system_statement<recurring_statement::DECLARATION>*>(&stt)){
            if(auto* decl_int = dynamic_cast<dataflow_declaration<dataflow_type::INT, statement_env::SYSTEM>*>(*decl)){
                handle_statement_declaration(*decl_int);
            }else if(auto* decl_float = dynamic_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::SYSTEM>*>(*decl)){
                handle_statement_declaration(*decl_float);
            }else if(auto* decl_bool = dynamic_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::SYSTEM>*>(*decl)){
                handle_statement_declaration(*decl_bool);
            }else if(auto* decl_block_p = dynamic_cast<block_declaration<block_type::PHYSICAL>*>(*decl)){
                handle_statement_declaration(*decl_block_p);
            }else if(auto* decl_block_l = dynamic_cast<block_declaration<block_type::LOGICAL>*>(*decl)){
                handle_statement_declaration(*decl_block_l);
            }else if(auto* decl_block_o = dynamic_cast<block_declaration<block_type::OBJECT>*>(*decl)){
                handle_statement_declaration(*decl_block_o);
            }
        }else if(auto* implements = std::get_if<system_statement<recurring_statement::IMPLEMENTS>*>(&stt)){
            out() << "<!-- TODO IMP-->\n";
        }else if(auto* feeding = std::get_if<system_statement<recurring_statement::FEEDING>*>(&stt)){
            if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT>*>(*feeding)){
                handle_feeding_statement(*f);
            }else if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*>(*feeding)){
                handle_feeding_statement(*f);
            }else if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>(*feeding)){
                handle_feeding_statement(*f);
            }else if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT>*>(*feeding)){
                handle_feeding_statement(*f);
            }else if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*>(*feeding)){
                handle_feeding_statement(*f);
            }else if(auto* f = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>(*feeding)){
                handle_feeding_statement(*f);
            }
        }else if(auto* link = std::get_if<system_statement<recurring_statement::LINKING>*>(&stt)){
            if(auto* l = dynamic_cast<linking_statement*>(*link)){
                (*l).accept(*this);
            }
        }else if(auto* plug = std::get_if<system_statement<recurring_statement::PLUGGING>*>(&stt)){
            if(auto* p = dynamic_cast<channel_plugging*>(*plug)){
                p->accept(*this);
            }
        }else if(auto* assign = std::get_if<system_statement<recurring_statement::ASSIGNMENT>*>(&stt)){
            if(auto* assign_int = dynamic_cast<dataflow_assignment<dataflow_type::INT, statement_env::SYSTEM>*>(*assign)){
                handle_statement_assignment(*assign_int);
            }else if(auto* assign_float = dynamic_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::SYSTEM>*>(*assign)){
                handle_statement_assignment(*assign_float);
            }else if(auto* assign_bool = dynamic_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::SYSTEM>*>(*assign)){
                handle_statement_assignment(*assign_bool);
            }
        }

        out() << repeat("\t", nbTab) << "</system_statements>\n";
        pop_ast_path(segment);
    }
}

void ChipsToXmiVisitor::visit(preamble_section_node& node){
    int def_index = 0;
    for(auto definition : node.get_definitions()){
        std::string segment = "/@definitions." + std::to_string(def_index++);
        push_ast_path(segment);
        out() << repeat("\t", nbTab) << "<definitions\n";
        if(auto* logical = std::get_if<logical_definition*>(&definition)){
            nbTab++;
            if(*logical){
                std::cout << ast_builder_detail::type_name(std::any{logical}.type()) << std::endl;
                (*logical)->accept(*this);
            }
            nbTab--;
        }else if(auto* physical = std::get_if<physical_definition*>(&definition)){
            nbTab++;
            if(*physical){
                std::cout << ast_builder_detail::type_name(std::any{physical}.type()) << std::endl;
                (*physical)->accept(*this);
            }
            nbTab--;

        }else if(auto* object = std::get_if<object_definition*>(&definition)){
            nbTab++;
            if(*object){
                std::cout << ast_builder_detail::type_name(std::any{object}.type()) << std::endl;
                (*object)->accept(*this);
            }
            nbTab--;
        }else if(auto* collective = std::get_if<collective_function_definition*>(&definition)){
            nbTab++;
            if(*collective){
                std::cout << ast_builder_detail::type_name(std::any{collective}.type()) << std::endl;
                (*collective)->accept(*this);
            }
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
    current_fname = node.get_name();

    // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
    std::string path = get_ast_path();

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

    auto sensors = node.get_sensors();
    if(!sensors.empty()){
        visit(sensors);
    }

    auto parameters = node.get_parameters();
    if(!parameters.empty()){
        visit(parameters);
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
    }else{
        out() << repeat("\t", nbTab) << "<with/>\n";
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
    }else{
        out() << repeat("\t", nbTab) << "<init/>\n";
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
    }else{
        out() << repeat("\t", nbTab) << "<then/>\n";
    }

    auto actuators = node.get_actuators();
    if(!actuators.empty()){
        int actuator_index = 0;
        std::vector<std::vector<std::string>> outputs_to_register;
        for(auto& actuator : actuators){
            std::visit([&](auto* act){
                out() << repeat("\t", nbTab) << "<actuator\n";

                nbTab++;

                std::string actuator_name = act->get_name();
                dataflow_type actuator_type = get_dataflow_type(act);
                std::string dft = dft_to_string(actuator_type);

                std::string actuator_path = get_ast_path() + "/@actuator." + std::to_string(actuator_index);

                register_output(current_fname, actuator_name, actuator_path);

                push_ast_path(actuator_path);

                nbTab++;
                out() << repeat("\t", nbTab);
                writeAttribute("xsi:type","chips.outputs.physical:"+dft+"_output");
                out() << "\n" << repeat("\t", nbTab);
                writeAttribute("name",actuator_name);
                out() << ">\n";
                nbTab--;

                out() << repeat("\t", nbTab) << "<expression\n";

                for(auto expression : act->get_expressions()){
                    std::visit([&](auto expr) {
                        using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

                        if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>>) {
                            binary_boolean_visit(*expr);
                        } else if constexpr(std::is_same_v<ExprT, rvalue<dataflow_type::INT, expression_env::PRIMITIVE>> || 
                                            std::is_same_v<ExprT, rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>){
                            arithmetic_visit(*expr);
                        }else{
                            out() << ast_builder_detail::type_name(std::any{expr}.type()) << "\n";
                        }

                        if(!only_one_child(*expr)){
                            out() << "</expression>\n";
                        }

                    }, expression);
                    break;
                }
                outputs_to_register.push_back({actuator_name, actuator_path, "actuator_output:"+dft});
                pop_ast_path(actuator_path);
                out() << repeat("\t", nbTab) << "</actuator>\n";
            }, actuator);
            
        }
    }

    auto outputs = node.get_outputs();
    if(!outputs.empty()){
        handle_outputs(outputs);
    }    
}

void ChipsToXmiVisitor::handle_outputs(std::vector<function_output_variant>& outputs, bool is_actuator){
    int output_index = 0;
    std::string name_balise = (is_actuator ? "actuator" : "outputs");

    std::vector<std::vector<std::string>> outputs_to_register;

    for(auto& output : outputs){
        std::visit([&](auto* outp){
            out() << repeat("\t", nbTab) << "<" << name_balise <<"\n";

            nbTab++;

            std::string output_name = outp->get_name();
            dataflow_type output_type = get_dataflow_type(outp);
            std::string dft = dft_to_string(output_type);

            std::string output_path = get_ast_path() + "/@"+ name_balise +"." + std::to_string(output_index++);

            register_output(current_fname, output_name, output_path);

            push_ast_path(output_path);

            nbTab++;
            out() << repeat("\t", nbTab);
            if(is_actuator){
                writeAttribute("xsi:type","chips.outputs.physical:"+dft+"_output");
            }else{
                writeAttribute("xsi:type","chips.outputs.logical:"+dft+"_output");
            }
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("name",output_name);
            out() << ">\n";
            nbTab--;

            out() << repeat("\t", nbTab) << "<expression\n";

            for(auto expression : outp->get_expressions()){
                std::visit([&](auto expr) {

                    using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

                    if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>>) {
                        std::cerr << "OUTPUT BOOL EXPR" << std::endl;
                        binary_boolean_visit(*expr);
                    } else {
                        std::cerr << "OUTPUT ARITH" << std::endl;
                        arithmetic_visit(*expr);
                    }

                    if(!only_one_child(*expr)){
                        out() << "</expression>\n";
                    }

                }, expression);
                break;
            }

            outputs_to_register.push_back({output_name, output_path, "output:"+dft});

            pop_ast_path(output_path);
            out() << repeat("\t", nbTab) << "</" << name_balise << ">\n";
        }, output);

        
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

    if(left && !only_one_child(*left)){
        out() << repeat("\t", nbTab) << "</left_operand>\n";
    }

    out() << repeat("\t", nbTab) << "<right_operand\n";
    nbTab++;
    out() << repeat("\t", ++nbTab);

    if(right){
        std::cerr << "right->accept()" << std::endl;
        arithmetic_visit(*right);
    } 

    if(right && !only_one_child(*right)){
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

    if(left && !only_one_child(*left)){
        out() << repeat("\t", nbTab) << "</left_operand>\n";
    }

    out() << repeat("\t", nbTab) << "<right_operand\n" << repeat("\t", nbTab);

    if(right){
        std::cerr << "right->accept()" << std::endl;
        binary_boolean_visit(*right);
    }

    if(right && !only_one_child(*right)){
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
            register_channel(current_fname, name, get_ast_path());

            // Also register in the current definition if we're in one
            if (!m_current_definition.empty()) {
                register_definition_variable(m_current_definition, name, get_ast_path(), "channel");
            }

            std::cerr << "[DEBUG] Channel '" << name << "' enregistré avec le chemin: " << get_ast_path() << std::endl;

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type", type);
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("name", name);
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("type_identifier", type_id);
            out() << "/>\n";
            nbTab--;

        }else if(auto* ctx_int = std::get_if<node_element_declaration<node_element::CONTEXTUAL_INT>*>(&statement)){
            handle_node_element_declaration(*(*ctx_int));
            out() << repeat("\t", nbTab) << "</statements>\n";
        }else if(auto* ctx_float = std::get_if<node_element_declaration<node_element::CONTEXTUAL_FLOAT>*>(&statement)){
            handle_node_element_declaration(*(*ctx_float));
            out() << repeat("\t", nbTab) << "</statements>\n";
        }else if(auto* ctx_bool = std::get_if<node_element_declaration<node_element::CONTEXTUAL_BOOL>*>(&statement)){
            handle_node_element_declaration(*(*ctx_bool));
            out() << repeat("\t", nbTab) << "</statements>\n";
        }
        pop_ast_path(segment);
    }
    
}

template<block_type bt>
void ChipsToXmiVisitor::handle_statement_declaration(block_declaration<bt>& node){
    auto definition = node.get_definition();
    auto variable = node.get_variable();

    std::string definition_name = definition->get_name();
    std::string variable_name = variable.get_name();
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dimensions = variable.get_dimensions();

    std::string path_definition = get_ast_path_by_name(definition_name);

    out() << repeat("\t", ++nbTab);
    writeAttribute("xsi:type","chips.statements.system:"+bt_to_string<bt>()+"_declaration");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("def", path_definition);
    out() << ">\n";
    nbTab--;

    std::string segment = "/@variable";
    push_ast_path(segment);
    std::string declarated_var_path = get_ast_path();
    register_variable(variable_name, declarated_var_path);
    register_block(definition_name, variable_name);

    out() << repeat("\t", nbTab++) << "<variable\n" << repeat("\t", nbTab);
    writeAttribute("name", variable_name);
    nbTab--;
    if(!dimensions.empty()){
        for(auto dimension : dimensions){
            out() << ">\n" << repeat("\t", nbTab) << "<dimensions\n";
            nbTab++; nbTab++;
            out() << repeat("\t", nbTab);

            std::visit([&](auto dim){
                // Null pointer safety check
                if(dim == nullptr){
                    std::cerr << "[WARNING] Null pointer in dimensions variant at line " << __LINE__ << std::endl;
                    return;
                }
                
                using dim_t = std::remove_pointer_t<std::decay_t<decltype(dim)>>;

                if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                    (*dim).accept(*this);
                }else{
                    arithmetic_visit(*dim);
                }
            }, dimension);

        }
        out() << "</variable>\n";
    }else{
        out() << "/>\n";
    }

    pop_ast_path(segment);
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
    auto dims = node.get_variable().get_dimensions();  // Now returns a copy, safe to use
    
    std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << declarated_var_path << std::endl;

    out() << repeat("\t", nbTab++) << "<variable\n" << repeat("\t", nbTab);
    writeAttribute("name", name);
    nbTab--;
    if(!dims.empty()){

        for(auto dimension : dims){
            out() << ">\n" << repeat("\t", nbTab) << "<dimensions\n";
            nbTab++; nbTab++;
            out() << repeat("\t", nbTab);

            std::visit([&](auto dim){
                // Null pointer safety check
                if(dim == nullptr){
                    std::cerr << "[WARNING] Null pointer in dimensions variant at line " << __LINE__ << std::endl;
                    return;
                }
                
                using dim_t = std::remove_pointer_t<std::decay_t<decltype(dim)>>;

                if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                    (*dim).accept(*this);
                }else{
                    arithmetic_visit(*dim);
                }
            }, dimension);

        }
        out() << "</variable>\n";
    }else{
        out() << "/>\n";
    }   
    
    
    pop_ast_path(segment);
    
}

template<dataflow_type dft, statement_env stenv>
void ChipsToXmiVisitor::handle_statement_assignment(dataflow_assignment<dft, stenv>& node){

    constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;

    std::string xvalue_prefix;
    
    if(!is_system_context(current_env)){
        if(current_env == expression_env::COLLECTIVE){
            xvalue_prefix = "chips.xvalues.collective";
        }else{
            xvalue_prefix = "chips.xvalues.primitive";
        }
    }else{
        xvalue_prefix = "chips.xvalues.system";
    }


    std::string type = dft_to_string(dft);
    std::string name = "";
    std::string value = "";
    std::vector<int_rvalue_expression_variant<expenv>>* lindex = nullptr;

    if(auto* lvalue = dynamic_cast<variable_expression<dft, expenv>*>(node.get_lhs())){
        if(auto* clvalue = dynamic_cast<variable_contextual_expression<dft, expenv>*>(lvalue)){
            value = "contextual_"+type+"_expression";
        }else{
            value = type+"_variable_expression";
        }
        name = lvalue->get_variable()->get_name();
        lindex = &lvalue->get_index();
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

    if(!lindex || lindex->empty()){
        out() << "/>\n";
        nbTab--;
        nbTab--;
    }else{
        out() << ">\n" << repeat("\t", nbTab);

        for(auto index : *lindex){
            out() << "<index\n" << repeat("\t", nbTab);
            std::visit([&](auto ind){
                using dim_t = std::remove_pointer_t<std::decay_t<decltype(ind)>>;

                // if(!ind){
                //     out() << "<!-- TODO DIMENSION -->\n";
                //     return;
                // }

                if constexpr(std::is_same_v<dim_t, input> || std::is_same_v<dim_t, stop>){
                    (*ind).accept(*this);
                }else{
                    arithmetic_visit(*ind);

                    if(!only_one_child(*ind)){
                        // out() << "ONE CHILD\n";
                        out() << "</index>\n";
                    }
                    
                }
                out() << "</lvalue>\n";
            }, index);
        }
    }
    

    node.get_rhs()->accept(*this);
}

template<expression_env expenv>
void ChipsToXmiVisitor::handle_condition(bool_rvalue_expression_variant<expenv>& node){
    out() << ">\n" << repeat("\t", nbTab) << "<condition\n" << repeat("\t", nbTab);

    std::visit([&](auto* value){
        if(auto* v = dynamic_cast<stop*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<input*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<gt<expenv,dataflow_type::INT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<gt<expenv,dataflow_type::FLOAT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<lt<expenv,dataflow_type::INT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<lt<expenv,dataflow_type::FLOAT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<geq<expenv,dataflow_type::INT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<geq<expenv,dataflow_type::FLOAT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<leq<expenv,dataflow_type::INT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<leq<expenv,dataflow_type::FLOAT>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<eq<dataflow_type::INT,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<eq<dataflow_type::FLOAT,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<eq<dataflow_type::BOOL,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<neq<dataflow_type::INT,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<neq<dataflow_type::FLOAT,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<neq<dataflow_type::BOOL,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<or_operator<expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<and_operator<expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<not_operator<expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<direct<dataflow_type::BOOL,expenv>*>(value)){
            visit(*v);
        }else if(auto* v = dynamic_cast<variable_expression<dataflow_type::BOOL,expenv>*>(value)){
            visit(*v);
        }else{
            out() << "<-- ERROR CONDITION -->\n";
        }

        using cond_t = std::remove_pointer_t<std::decay_t<decltype(value)>>;
        if constexpr(std::is_same_v<cond_t, input> || std::is_same_v<cond_t, stop>){
            // out() << "</condition>\n";
        }else{
            auto& bool_node = static_cast<rvalue<dataflow_type::BOOL, expenv>&>(*value);
            if(!only_one_child<dataflow_type::BOOL, expenv>(bool_node)){
                out() << "</condition>\n";
            }
        }

    }, node);
}

template<statement_env stenv>
void ChipsToXmiVisitor::handle_statement(typename SttEnvToSttVariant<stenv>::type& stt){
    std::visit([&](auto* ptr) {
        if (auto* if_else = dynamic_cast<if_else_statement<stenv>*>(ptr)) {
            handle_statement_if_else(*if_else);
        } else if (auto* if_simple = dynamic_cast<if_statement<stenv>*>(ptr)) {
            handle_statement_if(*if_simple);
        } else if (auto* decl_int = dynamic_cast<dataflow_declaration<dataflow_type::INT, stenv>*>(ptr)) {
            handle_statement_declaration(*decl_int);
        } else if (auto* decl_float = dynamic_cast<dataflow_declaration<dataflow_type::FLOAT, stenv>*>(ptr)) {
            handle_statement_declaration(*decl_float);
        } else if (auto* decl_bool = dynamic_cast<dataflow_declaration<dataflow_type::BOOL, stenv>*>(ptr)) {
            handle_statement_declaration(*decl_bool);
        } else if (auto* assign_int = dynamic_cast<dataflow_assignment<dataflow_type::INT, stenv>*>(ptr)) {
            handle_statement_assignment(*assign_int);
        } else if (auto* assign_float = dynamic_cast<dataflow_assignment<dataflow_type::FLOAT, stenv>*>(ptr)) {
            handle_statement_assignment(*assign_float);
        } else if (auto* assign_bool = dynamic_cast<dataflow_assignment<dataflow_type::BOOL, stenv>*>(ptr)) {
            handle_statement_assignment(*assign_bool);
        }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::INT>*>(ptr)){
            handle_foreach(*foreach);
        }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::FLOAT>*>(ptr)){
            handle_foreach(*foreach);
        }else if(auto* foreach = dynamic_cast<foreach_statement<stenv, dataflow_type::BOOL>*>(ptr)){
            handle_foreach(*foreach);
        }else if constexpr(stenv == statement_env::SYSTEM){
            if(auto* link = dynamic_cast<linking_statement*>(ptr)){
                (*link).accept(*this);
            }else if(auto* feeding_int_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT>*>(ptr)){
                handle_feeding_statement(*feeding_int_l);
            }else if(auto* feeding_float_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT>*>(ptr)){
                handle_feeding_statement(*feeding_float_l);
            }else if(auto* feeding_bool_l = dynamic_cast<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL>*>(ptr)){
                handle_feeding_statement(*feeding_bool_l);
            }else if(auto* feeding_int_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT>*>(ptr)){
                handle_feeding_statement(*feeding_int_p);
            }else if(auto* feeding_float_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>*>(ptr)){
                handle_feeding_statement(*feeding_float_p);
            }else if(auto* feeding_bool_p = dynamic_cast<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL>*>(ptr)){
                handle_feeding_statement(*feeding_bool_p);
            }else if(auto* plugging = dynamic_cast<channel_plugging*>(ptr)){
                (*plugging).accept(*this);
            } else {
                out() << "[WARNING] system statement type not handled\n";
            }
        } else {
            out() << "[WARNING] statement type not handled\n";
        }
    }, stt);
}

template<dataflow_kind dfk, dataflow_type dft>
void ChipsToXmiVisitor::handle_feeding_statement(feeding_statement<dfk, dft>& node){
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", statement_type("feeding_"+dfk_to_string<dfk>()+"_"+dft_to_string<dft>(), StatementFamily::System));

    eater<dfk, dft>& eat = node.get_eater();
    feeder<dfk, dft>* feed = node.get_feeder();

    visit(eat);
    visit(*feed);
}

template<dataflow_kind dfk, dataflow_type dft>
void ChipsToXmiVisitor::visit(eater<dfk,dft>& node){

    functional_block_variant& functional_block = node.get_functional_block();
    function_parameter<dfk,dft>* parameter = node.get_parameter();

    std::string block_name;
    std::string block_path;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dimensions;

    std::visit([&](auto* block){
        block_name = block->get_name();
        block_path = get_ast_path_by_name(block_name);
        dimensions = block->get_dimensions();
    }, functional_block);

    std::string param_name = parameter->get_name();
    std::string param_path = get_ast_path_by_name_parameter(get_type_of_declarated_block(block_name), param_name);
    // std::string param_path = get_ast_path_by_name(param_name);

    out() << ">\n" << repeat("\t", nbTab) << "<eater\n";

    out() << repeat("\t", nbTab);
    writeAttribute("parameter", param_path);
    out() << ">\n" << repeat("\t", nbTab) << "<variable_expression\n" << repeat("\t", nbTab);

    
    
    writeAttribute("variable", block_path);
    

    if(!dimensions.empty()){
        out() << ">\n";
        for(auto inde : dimensions){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</variable_expression>\n";
    }else{
        out() << "/>\n";
    }

    out() << repeat("\t", nbTab) << "</eater>\n";
}

template<dataflow_kind dfk, dataflow_type dft>
void ChipsToXmiVisitor::visit(feeder<dfk, dft>& node){
    out() << repeat("\t", nbTab) << "<feeder\n";
    if(auto* cast = dynamic_cast<collective_cast<dfk, dft>*>(&node)){
        visit(*cast);
        out() << repeat("\t", nbTab) << "</feeder>\n";
    }else if(auto* block = dynamic_cast<feeder_block_expression<dfk, dft>*>(&node)){
        visit(*block);
        out() << repeat("\t", nbTab) << "</feeder>\n";
    }else if(auto* expr = dynamic_cast<rvalue<dft,expression_env::SYSTEM>*>(&node)){
        if constexpr(dft == dataflow_type::BOOL){
            binary_boolean_visit(*expr);
        }else{
            arithmetic_visit(*expr);
        }

        if(!only_one_child(*expr)){
            out() << repeat("\t", nbTab) << "</feeder>\n";
        }
    }
    
}

template<dataflow_kind dfk, dataflow_type dft>
void ChipsToXmiVisitor::visit(feeder_block_expression<dfk, dft>& node){

    functional_block_variant& functional_block = node.get_functional_block();
    function_output<dfk,dft>* output = node.get_output();

    std::string type = dft_to_string<dft>();

    std::string output_name = output->get_name();
    
    // std::string output_path = get_ast_path_by_name(output_name);

    std::string block_name;
    std::string block_path;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dimensions;

    std::visit([&](auto* block){
        block_name = block->get_name();
        block_path = get_ast_path_by_name(block_name);
        dimensions = block->get_dimensions();
    }, functional_block);

    std::string output_path = get_ast_path_by_name_output(get_type_of_declarated_block(block_name), output_name);

    writeAttribute("xsi:type", "chips.systemspecific.expressions.feeder:"+dft_to_string<dft>()+"_"+dfk_to_string<dfk>()+"_output");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("output", output_path);

    out() << ">\n" << repeat("\t", nbTab) << "<variable_expression\n" << repeat("\t", nbTab);

    writeAttribute("variable", block_path);
    

    if(!dimensions.empty()){
        out() << ">\n";
        for(auto inde : dimensions){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</variable_expression>\n";
    }else{
        out() << "/>\n";
    }

}

template<dataflow_kind dfk, dataflow_type dft>
void ChipsToXmiVisitor::visit(collective_cast<dfk, dft>& node){

    std::string collective_name = node.get_collective_function()->get_name();
    std::string collective_path = get_ast_path_by_name(collective_name);
    feeder_variant& feeder_var = node.get_feeder_variant();

    

    writeAttribute("xsi:type","chips.systemspecific.expressions.feeder:"+dfk_to_string<dfk>()+"_collective_cast");
    out() << "\n";
    writeAttribute("collective_function", collective_path);
    out() << ">\n" << repeat("\t", nbTab) << "<"+dfk_to_string<dfk>()+"_feeder_expression\n" << repeat("\t", nbTab);

    std::visit([&](auto* feed){
        if(auto* block = dynamic_cast<feeder_block_expression<dfk, dataflow_type::INT>*>(feed)){
            visit(*block);
        }else if(auto* expr = dynamic_cast<rvalue<dataflow_type::INT,expression_env::SYSTEM>*>(feed)){
            arithmetic_visit(*expr);
        }else if(auto* block = dynamic_cast<feeder_block_expression<dfk, dataflow_type::BOOL>*>(feed)){
            visit(*block);
        }else if(auto* expr = dynamic_cast<rvalue<dataflow_type::BOOL,expression_env::SYSTEM>*>(feed)){
            binary_boolean_visit(*expr);
        }else if(auto* block = dynamic_cast<feeder_block_expression<dfk, dataflow_type::FLOAT>*>(feed)){
            visit(*block);
        }else if(auto* expr = dynamic_cast<rvalue<dataflow_type::FLOAT,expression_env::SYSTEM>*>(feed)){
            arithmetic_visit(*expr);
        }
    }, feeder_var);

    out() << "</"+dfk_to_string<dfk>()+"_feeder_expression>\n";
}

template<statement_env stenv>
void ChipsToXmiVisitor::handle_section_if(if_section<stenv>& node){
    out() << "<if_section>\n";
    std::string segment = "/@if_section";
    push_ast_path(segment);

    int if_index = 0;

    for(auto stt : node.get_statements()){
        out() << repeat("\t", nbTab) << "<if_statements\n";

        std::string if_segment = "/@if_statements." + std::to_string(if_index++);
        push_ast_path(if_segment);

        handle_statement<stenv>(stt);

        pop_ast_path(if_segment);

        out() << repeat("\t", nbTab) << "</if_statements>\n";
    }

    pop_ast_path(segment);
    out() << "</if_section>\n";
}

template<statement_env stenv>
void ChipsToXmiVisitor::handle_section_else(else_section<stenv>& node){
    out() << repeat("\t", nbTab) << "<else_section>\n";

    std::string segment = "/@else_section";
    push_ast_path(segment);

    int else_index = 0;

    for(auto stt : node.get_statements()){
        out() << repeat("\t", nbTab) << "<else_statements\n";

        std::string else_segment = "/@else_statements." + std::to_string(else_index++);
        push_ast_path(else_segment);

        handle_statement<stenv>(stt);

        pop_ast_path(else_segment);

        out() << repeat("\t", nbTab) << "</else_statements>\n";
    }

    pop_ast_path(segment);

    out() << repeat("\t", nbTab) << "</else_section>\n";
}

template<statement_env stenv>
void ChipsToXmiVisitor::handle_statement_if(if_statement<stenv>& node){
    writeAttribute("xsi:type",statement_type("if"));

    auto if_condition = node.get_condition();
    auto if_sect = node.get_if_section();

    handle_condition(if_condition);
    handle_section_if(if_sect);
}

template<statement_env stenv>
void ChipsToXmiVisitor::handle_statement_if_else(if_else_statement<stenv>& node){
    writeAttribute("xsi:type",statement_type("if_else"));
    
    auto if_condition = node.get_condition();
    auto if_sect = node.get_if_section();
    auto else_sect = node.get_else_section();

    handle_condition(if_condition);
    handle_section_if(if_sect);
    handle_section_else(else_sect);
}

template<statement_env stenv, dataflow_type dft>
void ChipsToXmiVisitor::handle_foreach(foreach_statement<stenv, dft>& node){
    constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;

    if constexpr(expenv == expression_env::SYSTEM){
        writeAttribute("xsi:type",statement_type("foreach", StatementFamily::System));
    }else{
        writeAttribute("xsi:type",statement_type("foreach"));
    }

    

    out() << ">\n" << repeat("\t", nbTab) << "<iterator\n" << repeat("\t", nbTab);

    auto iterator  = node.get_iterator();
    std::string iterator_name = iterator.get_variable().get_name();
    auto iterable = node.get_iterable();
    auto statements = node.get_statements();

    std::string iterator_path = get_ast_path() + "/@iterator/@variable";
    register_variable(iterator_name, iterator_path, "iterator");

    if constexpr(expenv == expression_env::SYSTEM){
        writeAttribute("xsi:type", statement_type(dft_to_string(dft)+"_declaration", StatementFamily::System));
    }else{
        writeAttribute("xsi:type", statement_type(dft_to_string(dft)+"_declaration"));
    }

    
    out() << ">\n" << repeat("\t", nbTab) << "<variable\n" << repeat("\t", nbTab);
    writeAttribute("name", iterator_name);
    out() << "/>\n" << repeat("\t", nbTab) << "</iterator>\n";

    out() << repeat("\t", nbTab) << "<iterable_expr\n" << repeat("\t", nbTab);

    std::visit([&](auto* itera){
        if(!itera){
            out() << "<!-- TODO ITERABLE -->\n";
            return;
        }

        using iterable_t = std::remove_pointer_t<decltype(itera)>;

        if constexpr(
            std::is_same_v<iterable_t, function<dataflow_type::INT, expenv>> ||
            std::is_same_v<iterable_t, function<dataflow_type::FLOAT, expenv>> ||
            std::is_same_v<iterable_t, function<dataflow_type::BOOL, expenv>>){
            visit(*itera);
        }else if constexpr(std::is_same_v<iterable_t, rvalue_variant<expenv>>){
            std::visit([&](auto* value){
                if(value){
                    visit(*value);
                }else{
                    out() << "<!-- TODO ITERABLE -->\n";
                }
            }, *itera);
        }else{
            out() << "<!-- TODO ITERABLE -->\n";
        }

    }, iterable);

    out() << repeat("\t", nbTab) << "</iterable_expr>\n";

    for(auto stt : statements){
        out() << repeat("\t", nbTab) << "<statements\n";
        handle_statement<stenv>(stt);
        out() << repeat("\t", nbTab) << "</statements>\n";
    }
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
        handle_statement<statement_env::DEFINITION>(statement);
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

        handle_statement<statement_env::DEFINITION>(statement);

        nbTab--;
        pop_ast_path(segment);
        out() << repeat("\t", nbTab) << "</statements>\n";
    }

}

void ChipsToXmiVisitor::visit(std::vector<physical_parameter_variant>& node){
    int sensor_index = 0;
    for(auto& sensor : node){
        std::visit([this, &sensor_index](auto* sen){
            out() << repeat("\t", nbTab) << "<sensor\n";
            
            nbTab++;

            std::string sensor_name = sen->get_name();
            dataflow_type sensor_type = get_dataflow_type(sen);
            std::string dft = dft_to_string(sensor_type);

            auto declaration_variable = sen->get_declaration().get_variable();
            auto index = declaration_variable.get_dimensions();

            std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
            std::string sensor_path = sensor_base_path + "/@declaration/@variable";

            push_ast_path(sensor_path);
            register_variable(sensor_name, sensor_path, "physical_parameter_"+dft);
            register_parameter(current_fname, sensor_name, sensor_path);

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type", "chips.parameters.physical:"+dft+"_physical_parameter");
            out() << "\n" << repeat("\t", nbTab);
            writeAttribute("name", sensor_name);
            out() << ">\n";
            nbTab--;

            out() << repeat("\t", nbTab) << "<declaration>\n";
            push_ast_path("/@declaration");
            nbTab++;
            out() << repeat("\t", nbTab) << "<variable\n";
            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("name", sensor_name);

            if(index.empty()){
                out() << "/>\n";
            }else{
                out() << ">\n";

                visit(index);
                out() << "</variable>\n";
            }

            pop_ast_path("/@declaration");
            nbTab--;
            nbTab--;
            out() << repeat("\t", nbTab) << "</declaration>\n";

            if(sen->get_default_value().has_value()){
                out() << repeat("\t", nbTab) << "<default_value\n";
                auto default_value = sen->get_default_value().value();

                std::visit([&](auto default_v){
                    using ParamT = std::remove_cv_t<std::remove_pointer_t<decltype(default_v)>>;

                    if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>>){
                        binary_boolean_visit(*default_v);
                    }else if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::INT, expression_env::PRIMITIVE>> ||
                                       std::is_same_v<ParamT, rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>){
                        arithmetic_visit(*default_v);
                        
                    }
                    if(!only_one_child(*default_v)){
                        out() << "</default_value>\n";
                    }
                }, default_value);
            }


            std::cerr << "[DEBUG] Balise <parameters> terminée pour '" << sensor_name << "'" << std::endl;
            pop_ast_path(sensor_path);
            dumpSymbolTable();
            param_index++;
            nbTab--;
            out() << repeat("\t", nbTab) << "</sensor>\n";
        }, sensor);
    }
}

void ChipsToXmiVisitor::visit(std::vector<channeled_output>& node){
    for(auto output : node){

        out() << repeat("\t", nbTab) << "<channeled_output\n";

        node_element_declaration<node_element::CHANNEL>* channel = output.get_channel();
        std::vector<rvalue_variant<expression_env::COLLECTIVE>> expressions = output.get_expressions();

        std::string channel_name = channel->get_name();

        std::string path = get_ast_path_by_name(channel_name);

        nbTab++; nbTab++;
        writeAttribute("channel",path);
        out() << ">\n";
        nbTab--;

        for(auto expression : expressions){
            std::visit([&](auto expr){
                out() << repeat("\t", nbTab) << "<accumulator_expressions\n";

                using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

                if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>>) {
                    binary_boolean_visit(*expr);
                } else if constexpr(std::is_same_v<ExprT, rvalue<dataflow_type::INT, expression_env::COLLECTIVE>> || 
                                    std::is_same_v<ExprT, rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>){
                    arithmetic_visit(*expr);
                }else{
                    out() << ast_builder_detail::type_name(std::any{expr}.type()) << "\n";
                } 

                if(!only_one_child(*expr)){
                    out() << "</accumulator_expressions>\n";
                }

            }, expression);
        }

        out() << repeat("\t", nbTab) << "</channeled_output>\n";
    }
}

template<expression_env expenv>
void ChipsToXmiVisitor::visit(std::vector<int_rvalue_expression_variant<expenv>>& node){
    for(auto& dimension : node){
        std::visit([&](auto* dim){

            nbTab--;
            out() << repeat("\t", nbTab) << "<dimensions\n"
                << repeat("\t", ++nbTab);

                std::cerr << "ARITH INDEX PARAM" << std::endl;
            if(auto* r = dynamic_cast<rvalue<dataflow_type::INT, expenv>*>(dim)){
                std::cerr << "INDEX PARAM" << std::endl;
                arithmetic_visit(*r);
            }else{
                std::cerr << "PB INDEX PARAM " << ast_builder_detail::type_name(std::any{*dim}.type()) << std::endl;
            }            
        }, dimension);
    }
}

void ChipsToXmiVisitor::visit(std::vector<function_parameter_variant>& node){
    param_index = 0;
    for(auto& parameter : node){
        std::visit([this](auto* param) {
            if(param){
                out() << repeat("\t", nbTab) << "<parameters\n";


                nbTab++;
                std::string param_name = param->get_name();
                dataflow_type param_type = get_dataflow_type(param);
                std::string dft = dft_to_string(param_type);

                std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> index = param->get_declaration().get_variable().get_dimensions();

                std::string param_base_path = get_ast_path() + "/@parameters." + std::to_string(param_index);
                std::string param_path = param_base_path + "/@declaration/@variable";

                std::cerr << "[DEBUG] Paramètre logique '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;

                std::cerr << "[DEBUG] Génération balise <parameters> pour '" << param_name << "'" << std::endl;
                push_ast_path(param_path);
                register_variable(param_name, param_path,"logical_parameter_"+dft);
                register_parameter(current_fname, param_name, param_path);

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

                if(index.empty()){
                    out() << "/>\n";
                }else{
                    out() << ">\n";

                    visit(index);
                    out() << "</variable>\n";
                }

                
                pop_ast_path("/@declaration");
                nbTab--;
                nbTab--;
                out() << repeat("\t", nbTab) << "</declaration>\n";

                if(param->get_default_value().has_value()){
                    out() << repeat("\t", nbTab) << "<default_value\n";
                    auto default_value = param->get_default_value().value();

                    std::visit([&](auto default_v){
                        using ParamT = std::remove_cv_t<std::remove_pointer_t<decltype(default_v)>>;

                        if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::BOOL, expression_env::PRIMITIVE>>){
                            std::cerr << "BINARY" << param_name << "\n";
                            binary_boolean_visit(*default_v);
                        }else if constexpr(std::is_same_v<ParamT, rvalue<dataflow_type::INT, expression_env::PRIMITIVE>> || 
                                            std::is_same_v<ParamT, rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>){
                            std::cerr << "ARITH" << param_name << "\n";
                            arithmetic_visit(*default_v);
                        }else{
                            out() << ast_builder_detail::type_name(std::any{default_v}.type()) << "\n";
                        }

                        if(!only_one_child(*default_v)){
                            out() << "</default_value>\n";
                        }

                    }, default_value);

                    // // nbTab++; nbTab++;
                    // // out() << repeat("\t", nbTab);
                    // // writeAttribute("xsi:type", "chips.rvalues.primitive:direct"+dft);
                    // // out() << "\n" << repeat("\t", nbTab);
                    // // writeAttribute("value", )
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

void ChipsToXmiVisitor::visit(logical_definition& node){
    current_env = expression_env::PRIMITIVE;
    current_fname = node.get_name();

    register_variable(node.get_name(), get_ast_path(), "logical");
    std::string path = get_ast_path();

    register_definition(node.get_name(), "logical", get_ast_path(), def_index);
    m_current_definition = node.get_name();

    std::cerr << "[DEBUG] Logical definition '" << node.get_name() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    nbTab++;
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", "definitions:logical_definition");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", node.get_name());
    out() << ">\n";
    nbTab--;

    auto parameters = node.get_parameters();
    if(!parameters.empty()){
        visit(parameters);
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
    }else{
        out() << repeat("\t", nbTab) << "<init/>\n";
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
    }else{
        out() << repeat("\t", nbTab) << "<then/>\n";
    }

    auto outputs = node.get_outputs();
    if(!outputs.empty()){
        handle_outputs(outputs);
    }  
}

void ChipsToXmiVisitor::visit(object_definition& node){
    current_env = expression_env::PRIMITIVE;
    current_fname = node.get_name();
    // Enregistrer la définition physique dans la table des symboles
    // Le chemin est : //@preamble/@definitions.X (déterminé par le contexte d'appel)
    register_variable(node.get_name(), get_ast_path(), "object");

    // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
    std::string path = get_ast_path();

    // Register the definition in the definitions table
    register_definition(node.get_name(), "object", get_ast_path(), def_index);
    m_current_definition = node.get_name();

    std::cerr << "[DEBUG] Object definition '" << node.get_name() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    nbTab++;
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", "definitions:object_definition");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", node.get_name());
    out() << ">\n";
    nbTab--;


    auto with = node.get_with_section();
    if(!with.get_statements().empty()){
        push_ast_path("/@with");
        out() << repeat("\t", nbTab) << "<with>\n";
        nbTab++;
        with.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</with>\n";
        pop_ast_path("/@with");
    }else{
        out() << repeat("\t", nbTab) << "<with/>\n";
    }
}

void ChipsToXmiVisitor::visit(collective_function_definition& node){
    current_env = expression_env::COLLECTIVE;
    current_fname = node.get_name();
    // Enregistrer la définition physique dans la table des symboles
    // Le chemin est : //@preamble/@definitions.X (déterminé par le contexte d'appel)
    register_variable(node.get_name(), get_ast_path(), "collective");

    // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
    std::string path = get_ast_path();

    // Register the definition in the definitions table
    register_definition(node.get_name(), "collective", get_ast_path(), def_index);

    m_current_definition = node.get_name();
    collective_function_type type = node.get_type();
    accumulator_definition accumulator = node.get_accumulator();
    node_definition* support_object = node.get_node_definition();
    collectiveops_section operations = node.get_operations();
    target_output target = node.get_target_output();
    default_output default_o = node.get_default_output();
    std::vector<channeled_output> channeled_outputs = node.get_channeled_outputs();

    std::string support_object_name = support_object->get_name();


    std::cerr << "[DEBUG] Collective definition '" << node.get_name() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    nbTab++;
    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type", "definitions:collective_function_definition");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("name", node.get_name());
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("collective_function_type", collective_type_to_string(type));
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("support_object", get_ast_path_by_name(support_object_name));
    out() << ">\n";
    nbTab--;

    if(!accumulator.get_accumulators().empty()){
        push_ast_path("/@accumulator");
        out() << repeat("\t", nbTab) << "<accumulator>\n";
        nbTab++;
        accumulator.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</accumulator>\n";
        pop_ast_path("/@accumulator");
    }else{
        out() << repeat("\t", nbTab) << "<accumulator/>\n";
    }

    if(!operations.get_statements().empty()){
        push_ast_path("/@operations");
        out() << repeat("\t", nbTab) << "<operations>\n";
        nbTab++;
        operations.accept(*this);
        nbTab--;
        out() << repeat("\t", nbTab) << "</operations>\n";
        pop_ast_path("/@operations");
    }else{
        // out() << repeat("\t", nbTab) << "<operations/>\n";
    }
    
    target.accept(*this);

    if(!default_o.get_expressions().empty()){
        default_o.accept(*this);
    }

    if(!channeled_outputs.empty()){
        visit(channeled_outputs);
    }
}

void ChipsToXmiVisitor::visit(channel_plugging& node){

    channel_eater* eat = node.get_eater();
    channel_feeder* feed = node.get_feeder();

    writeAttribute("xsi:type","chips.statements.system:channel_plugging");
    out() << ">\n" << repeat("\t", nbTab);

    eat->accept(*this);
    feed->accept(*this);
}

void ChipsToXmiVisitor::visit(channel_eater& node){

    node_variable_expression* variable_expression = node.get_node();
    node_element_declaration<node_element::CHANNEL>* eating = node.get_eating_channel();

    

    block_type variable_expression_type;
    std::string variable_expression_name;
    std::string variable_expression_path;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index;

    if(auto* physical = dynamic_cast<system_variable_block_expression<block_type::PHYSICAL>*>(variable_expression)){
        variable_expression_type = block_type::PHYSICAL;
        variable_expression_name = physical->get_variable()->get_name();
        variable_expression_path = get_ast_path_by_name(variable_expression_name);
        index = physical->get_index();
    }else if(auto* object = dynamic_cast<system_variable_block_expression<block_type::OBJECT>*>(variable_expression)){
        variable_expression_type = block_type::OBJECT;
        variable_expression_name = object->get_variable()->get_name();
        variable_expression_path = get_ast_path_by_name(variable_expression_name);
        index = object->get_index();
    }

    std::string eating_name = eating->get_name();
    // std::string eating_path = get_ast_path_by_name(eating_name);
    std::string eating_path = get_ast_path_by_name_channel(get_type_of_declarated_block(variable_expression_name), eating_name);

    out() << "<eater\n" << repeat("\t", nbTab);
    writeAttribute("eating_channel", eating_path);
    out() << ">\n" << repeat("\t", nbTab) << "<node\n" << repeat("\t", nbTab);
    writeAttribute("xsi:type", "chips.systemspecific.expressions:"+bt_to_string(variable_expression_type)+"_variable_expression");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable", variable_expression_path);

    if(!index.empty()){
        out() << ">\n";
        for(auto inde : index){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</node>\n";
    }else{
        out() << "/>\n";
    }
    out() << "</eater>\n";
}

void ChipsToXmiVisitor::visit(channel_feeder& node){


    node_variable_expression* variable_expression = node.get_node();
    node_element_declaration<node_element::CHANNEL>* feeding = node.get_feeding_channel();

    block_type variable_expression_type;
    std::string variable_expression_name;
    std::string variable_expression_path;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> index;

    if(auto* physical = dynamic_cast<system_variable_block_expression<block_type::PHYSICAL>*>(variable_expression)){
        variable_expression_type = block_type::PHYSICAL;
        variable_expression_name = physical->get_variable()->get_name();
        variable_expression_path = get_ast_path_by_name(variable_expression_name);
        index = physical->get_index();
    }else if(auto* object = dynamic_cast<system_variable_block_expression<block_type::OBJECT>*>(variable_expression)){
        variable_expression_type = block_type::OBJECT;
        variable_expression_name = object->get_variable()->get_name();
        variable_expression_path = get_ast_path_by_name(variable_expression_name);
        index = object->get_index();
    }

    std::string feeding_name = feeding->get_name();
    // std::string feeding_path = get_ast_path_by_name(feeding_name);
    std::string feeding_path = get_ast_path_by_name_channel(get_type_of_declarated_block(variable_expression_name), feeding_name);

    out() << "<feeder\n" << repeat("\t", nbTab);
    writeAttribute("feeding_channel", feeding_path);
    out() << ">\n" << repeat("\t", nbTab) << "<node\n" << repeat("\t", nbTab);
    writeAttribute("xsi:type", "chips.systemspecific.expressions:"+bt_to_string(variable_expression_type)+"_variable_expression");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable", variable_expression_path);

    if(!index.empty()){
        out() << ">\n";
        for(auto inde : index){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</node>\n";
    }else{
        out() << "/>\n";
    }
    out() << "</feeder>\n";
}

void ChipsToXmiVisitor::visit(linking_statement& node){
    linkable* link = node.get_linkable();
    support* support_node = node.get_support();

    std::string link_name;
    block_type link_type;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> link_index;

    std::string support_name;
    block_type support_type;
    std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> support_index;

    if (auto* logical = dynamic_cast<system_variable_block_expression<block_type::LOGICAL>*>(link)) {
        link_name = logical->m_variable->get_name();
        link_type = block_type::LOGICAL;
        link_index = logical->get_index();
    } else if (auto* physical = dynamic_cast<system_variable_block_expression<block_type::PHYSICAL>*>(link)) {
        link_name = physical->m_variable->get_name();
        link_type = block_type::PHYSICAL;
        link_index = physical->get_index();
    } else if (auto* object = dynamic_cast<system_variable_block_expression<block_type::OBJECT>*>(link)) {
        link_name = object->m_variable->get_name();
        link_type = block_type::OBJECT;
        link_index = object->get_index();
    }

    if (auto* logical = dynamic_cast<system_variable_block_expression<block_type::LOGICAL>*>(support_node)) {
        support_name = logical->m_variable->get_name();
        support_type = block_type::LOGICAL;
        support_index = logical->get_index();
    } else if (auto* physical = dynamic_cast<system_variable_block_expression<block_type::PHYSICAL>*>(support_node)) {
        support_name = physical->m_variable->get_name();
        support_type = block_type::PHYSICAL;
        support_index = physical->get_index();
    } else if (auto* object = dynamic_cast<system_variable_block_expression<block_type::OBJECT>*>(support_node)) {
        support_name = object->m_variable->get_name();
        support_type = block_type::OBJECT;
        support_index = object->get_index();
    }

    std::string link_path = get_ast_path_by_name(link_name);
    std::string support_path = get_ast_path_by_name(support_name);

    out() << repeat("\t", nbTab);
    writeAttribute("xsi:type","chips.statements.system:link");
    out() << ">\n" << repeat("\t", nbTab) << "<linked_component\n" << repeat("\t", nbTab);
    writeAttribute("xsi:type","chips.systemspecific.expressions:"+bt_to_string(link_type)+"_variable_expression");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable",link_path);

    if(link_index.empty()){
        out() << "/>\n";
    }else{
        out() << ">\n";
        for(auto inde : link_index){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</linked_component>\n";
    }

    out() << repeat("\t", nbTab) << "<support_node\n" << repeat("\t", nbTab);
    writeAttribute("xsi:type","chips.systemspecific.expressions:"+bt_to_string(support_type)+"_variable_expression");
    out() << "\n" << repeat("\t", nbTab);
    writeAttribute("variable",support_path);

    if(support_index.empty()){
        out() << "/>\n";
    }else{
        out() << ">\n";
        for(auto inde : support_index){
            out() << "<index\n";

            std::visit([&](auto i){

                using index_t = std::remove_pointer_t<std::decay_t<decltype(i)>>;

                if(!i){
                    out() << "<!-- TODO INDEX -->\n";
                    return;
                }

                if constexpr(std::is_same_v<index_t, input> || std::is_same_v<index_t, stop>){
                    // visit(*i);
                    (*i).accept(*this);
                }else{
                    arithmetic_visit(*i);

                    if(!only_one_child(*i)){
                        out() << "</index>\n";
                    }
                }

            }, inde);
        }
        out() << "</support_node>\n";
    }
}

void ChipsToXmiVisitor::visit(target_output& node){
    out() << repeat("\t", nbTab) << "<target_output>\n";

    auto expressions = node.get_expressions();

    for(auto& expression : expressions){
        std::visit([&](auto* expr){
            nbTab++;
            out() << repeat("\t", nbTab) << "<expression\n";

            using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

            std::cerr << "CURRENT OUTPUT " << std::endl;
            if(expr){
                std::cerr << "CURRENT OUTPUT dynamic type: " << typeid(*expr).name() << std::endl;
            }else{
                std::cerr << "CURRENT OUTPUT dynamic type: <null>" << std::endl;
            }

            if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>>) {
                binary_boolean_visit(*expr);
            } else if constexpr(std::is_same_v<ExprT, rvalue<dataflow_type::INT, expression_env::COLLECTIVE>> || 
                                std::is_same_v<ExprT, rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>){
                arithmetic_visit(*expr);
            }else{
                out() << ast_builder_detail::type_name(std::any{expr}.type()) << "\n";
            } 

            if(!only_one_child(*expr)){
                out() << "</expression>\n";
            }

            nbTab--;
        }, expression);
    }

    out() << repeat("\t", nbTab) << "</target_output>\n";
}

void ChipsToXmiVisitor::visit(default_output& node){

    out() << repeat("\t", nbTab) << "<default_output>\n";

    auto expressions = node.get_expressions();

    for(auto& expression : expressions){
        std::visit([&](auto* expr){
            nbTab++;
            out() << repeat("\t", nbTab) << "<accumulator_expressions\n";

            std::cerr << "DEFAULT OUTPUT " << std::endl;
            if(expr){
                std::cerr << "DEFAULT OUTPUT dynamic type: " << typeid(*expr).name() << std::endl;
            }else{
                std::cerr << "DEFAULT OUTPUT dynamic type: <null>" << std::endl;
            }

            using ExprT = std::remove_cv_t<std::remove_pointer_t<decltype(expr)>>;

            if constexpr (std::is_same_v<ExprT, rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>>) {
                binary_boolean_visit(*expr);
            } else if constexpr(std::is_same_v<ExprT, rvalue<dataflow_type::INT, expression_env::COLLECTIVE>> || 
                                std::is_same_v<ExprT, rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>){
                arithmetic_visit(*expr);
            }else{
                out() << ast_builder_detail::type_name(std::any{expr}.type()) << "\n";
            } 

            nbTab--;
        }, expression);
    }

    out() << repeat("\t", nbTab) << "</default_output>\n";
}

void ChipsToXmiVisitor::visit(accumulator_definition& node){
    std::vector<collective_parameter_variant> accumulators = node.get_accumulators();
    int accumulator_index = 0;

    for(auto& accumulator : accumulators){

        std::visit([&](auto* accum){
            // std::string segment = "/accumulator." + std::to_string(index++);
            // push_ast_path(segment);
            out() << repeat("\t", nbTab) << "<accumulator\n";
            nbTab++;

            std::string pname = accum->get_name();
            dataflow_type accumulator_type = get_dataflow_type(accum);
            std::string dft = dft_to_string(accumulator_type);

            auto& default_value = accum->get_default_value();
            auto& declaration = accum->get_declaration();
            auto declaration_variable = declaration.get_variable();
            auto dimensions = declaration_variable.get_dimensions();

            std::string accumulator_base_path = get_ast_path() + "/@accumulator." + std::to_string(accumulator_index);
            std::string accumulator_path = accumulator_base_path + "/@declaration/@variable";

            push_ast_path(accumulator_path);
            register_variable(pname, accumulator_path, "collective_parameter_"+dft);
            register_parameter(current_fname, pname, accumulator_path);

            nbTab++;
            out() << repeat("\t", nbTab);
            writeAttribute("xsi:type","chips.parameters.collective:"+dft+"_collective_parameter");
            out() << ">\n" << repeat("\t", --nbTab) << "<default_value\n" << repeat("\t", ++nbTab);

            std::cerr << "DEFAULT VALUE COLLECT " << pname << std::endl;
            
            using AccumT = std::remove_cv_t<std::remove_pointer_t<decltype(accum)>>;
            if constexpr(std::is_same_v<AccumT, collective_parameter<dataflow_type::BOOL>>){
                binary_boolean_visit<dataflow_type::BOOL, expression_env::COLLECTIVE>(default_value);
            }else if constexpr(std::is_same_v<AccumT, collective_parameter<dataflow_type::INT>> ||
                               std::is_same_v<AccumT, collective_parameter<dataflow_type::FLOAT>>){
                arithmetic_visit(default_value);
            }

            if(!only_one_child(default_value)){
                out() << "</default_value>\n";
            }

            out() << repeat("\t", --nbTab) << "<declaration>\n" << repeat("\t", nbTab++) 
                  << "<variable\n" << repeat("\t", ++nbTab);
            writeAttribute("name",pname);
            if(!dimensions.empty()){
                out() << ">\n";
                visit(dimensions);
                out() << "</variable>\n";
            }else{
                out() << "/>\n";
            }


            out() << repeat("\t", --nbTab) << "</declaration>\n"
                  << repeat("\t", --nbTab) << "</accumulator>\n";

            pop_ast_path(accumulator_path);
            accumulator_index++;

            nbTab--;
            // pop_ast_path(segment);
        }, accumulator);
    }
}

void ChipsToXmiVisitor::visit(collectiveops_section& node){

    std::vector<collective_statement_variant> statements = node.get_statements();
    int index = 0;

    for(auto& statement : statements){

        std::string segment = "/@statements." + std::to_string(index++);
        push_ast_path(segment);
        std::cerr << "[XMI DEBUG] collectiveops_section statement variant index=" << statement.index() << std::endl;
        out() << repeat("\t", nbTab) << "<statements\n";
        nbTab++;

        handle_statement<statement_env::COLLECTIVE>(statement);

        nbTab--;
        out() << repeat("\t", nbTab) << "</statements>\n";
        pop_ast_path(segment);
    }

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
    // report_semantic_error("Undefined variable: " + name);
    // return name; // Fallback: retourner juste le nom
    return get_ast_path_by_name_parameter(current_fname, name);
}