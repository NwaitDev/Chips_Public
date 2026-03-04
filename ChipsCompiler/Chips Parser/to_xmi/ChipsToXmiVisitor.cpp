#include "ChipsToXmiVisitor.hpp"
#include <iostream>
#include <algorithm>

/*
question : quand on entre dans init on tombe sur un statement_node sans plus de précision. est-ce normal ?

*/

// === PROGRAM & CONTEXT ===
void ChipsToXmiVisitor::visit(chips::program_node& node)
{
    std::cerr << "\n[DEBUG Visitor] ========================================" << std::endl;
    std::cerr << "[DEBUG Visitor] visit(program_node) DÉMARRÉ" << std::endl;
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    std::cerr << "[DEBUG Visitor] ========================================" << std::endl;
    // Contenu après xmi_header() → directement les enfants
    if (auto pres = node.get_preamble())
    {
        std::cerr << "[DEBUG Visitor] Preamble trouvé, appel accept()" << std::endl;
        pres->accept(*this);
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun preambles!" << std::endl;
    }

    if (auto sys = node.get_system())
    {
        std::cerr << "[DEBUG Visitor] System trouvé, appel accept()" << std::endl;
        sys->accept(*this);
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun system!" << std::endl;
    }

    std::cerr << "[DEBUG Visitor] visit(program_node) TERMINÉ" << std::endl;
}

void ChipsToXmiVisitor::visit(chips::preamble_section_node& node)
{
    std::cerr << "[DEBUG Visitor] visit(preamble_section_node) appelé" << std::endl;
    std::cerr << "[DEBUG Visitor] Nombre de definitions: " << node.get_definitions().size() << std::endl;

    out() << "  <preamble>\n";

    push_ast_path("/@preamble");
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

    int index = 0;
    for (auto &pre : node.get_definitions())
    {
        std::cerr << "[DEBUG Visitor] Traitement preamble #" << index++ << std::endl;
        if (pre)
        {
            std::string segment = "/@definitions." + std::to_string(index - 1);
            push_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            pre->accept(*this);
            pop_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        }
        else
        {
            std::cerr << "[WARNING Visitor] Preamble NULL à l'index " << (index - 1) << std::endl;
        }
    }

    pop_ast_path("/@preamble");
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    out() << "  </preamble>\n";
}

void ChipsToXmiVisitor::visit(chips::definition& node){
    std::cerr << "[DEBUG Visitor] visit(definition) appelé - classe de base" << std::endl;
    // Ne rien générer ici - les sous-classes concrètes
    // (object_definition, function_definition, etc.)
    // généreront leurs propres balises
    // via leurs visiteurs spécifiques 
}

void ChipsToXmiVisitor::visit(chips::system_section_node& node)
{
    // std::cerr << "[DEBUG Visitor] visit(system_node) appelé" << std::endl;
    // ensure_namespace_for_prefix("chips.statements.system");

    // out() << "  <system>\n";

    // push_ast_path("/@system");
    // std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

    // std::string previous_tag = m_statement_tag;
    // m_statement_tag = "system";

    // // Parcourir les déclarations système
    // if (auto statements = node.get_system_statements())
    // {
    //     std::cerr << "[DEBUG Visitor] System statements trouvé, " << statements->get_statements().size() << " statements" << std::endl;
    //     int index = 0;
    //     for (auto &st : statements->get_statements())
    //     {
    //         if (st)
    //         {
    //             m_extra_statements_generated = 0;
    //             std::string segment = "/@system." + std::to_string(index);
    //             push_ast_path(segment);
    //             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    //             st->accept(*this);
    //             pop_ast_path(segment);
    //             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    //             index++;
    //             index += m_extra_statements_generated;
    //         }
    //     }
    // }
    // else
    // {
    //     std::cerr << "[WARNING Visitor] Aucun system statements!" << std::endl;
    // }

    // m_statement_tag = previous_tag;

    // pop_ast_path("/@system");
    // std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    // out() << "  </system>\n";
}

// // === SYSTEM STATEMENTS ===

// void ChipsToXmiVisitor::visit(s_statements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(s_statements_node) appelé" << std::endl;
//     int index = 0;
//     for (auto &st : node.get_statements())
//     {
//         if (st)
//         {
//             std::string segment = "/@statements." + std::to_string(index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             st->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(const s_statements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(const s_statements_node) appelé" << std::endl;
//     int index = 0;
//     for (auto &st : node.get_statements())
//     {
//         if (st)
//         {
//             std::string segment = "/@statements." + std::to_string(index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             st->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(s_statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(s_statement_node) type: " << node.get_statement_type() << std::endl;

//     switch (node.get_statement_type())
//     {
//     case S_IMPLEMENTS_ST:
//         if (auto impl = dynamic_cast<implements_node *>(&node))
//             impl->accept(*this);
//         break;
//     case S_LINK_ST:
//         if (auto link = dynamic_cast<link_node *>(&node))
//             link->accept(*this);
//         break;
//     case S_EXPR_PLUG_ST:
//         if (auto plug = dynamic_cast<plugging_node *>(&node))
//             plug->accept(*this);
//         break;
//     case LOOP_ST:
//         if (auto loop = dynamic_cast<s_loop_node *>(&node))
//             loop->accept(*this);
//         break;
//     case IF_ST:
//         if (auto ifn = dynamic_cast<s_if_node *>(&node))
//             ifn->accept(*this);
//         break;
//     case IFELSE_ST:
//         if (auto ifelse = dynamic_cast<s_if_else_node *>(&node))
//             ifelse->accept(*this);
//         break;
//     case S_FUNC_BLOCK_INST_ST:
//         if (auto fbi = dynamic_cast<functionnal_block_instanciation_node *>(&node))
//             fbi->accept(*this);
//         break;
//     default:
//         out() << "    <!-- s_statement_node type="
//               << node.get_statement_type() << " -->\n";
//     }
// }

// void ChipsToXmiVisitor::visit(implements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(implements_node)" << std::endl;

//     std::string implementer_name = node.get_ident1();    // Ex: "pc" (PhysicalCounter instance)
//     std::string implemented_name = node.get_ident2();    // Ex: "ao" (AbstractObject instance)
//     std::string implementation_name = node.get_ident3(); // Ex: "abstractObjectByCounter"

//     std::cerr << "    Implementer: " << implementer_name << std::endl;
//     std::cerr << "    Implemented: " << implemented_name << std::endl;
//     std::cerr << "    Implementation: " << implementation_name << std::endl;

//     // 1. Lookup the implementation definition
//     SymbolInfo impl_info = get_symbol_info(implementation_name);

//     // 2. Lookup the implemented instance (object or logical)
//     SymbolInfo implemented_info = get_symbol_info(implemented_name);
//     std::string implemented_xsi_type = get_xsi_type_for_symbol(implemented_info);

//     // 3. Lookup the implementer instance (physical or logical)
//     SymbolInfo implementer_info = get_symbol_info(implementer_name);
//     std::string implementer_xsi_type = get_xsi_type_for_symbol(implementer_info);

//     ensure_namespace_for_prefix("chips.statements.system");
//     ensure_namespace_for_prefix("chips.systemspecific.expressions");

//     std::cerr << "    Implementation path: " << impl_info.path << std::endl;
//     std::cerr << "    Implemented path: " << implemented_info.path << ", xsi:type: " << implemented_xsi_type << std::endl;
//     std::cerr << "    Implementer path: " << implementer_info.path << ", xsi:type: " << implementer_xsi_type << std::endl;

//     // 4. Generate the implements_statement
//     // NOTE: There is a typo in the XMI schema - "implmentation" instead of "implementation"
//     // We must replicate it exactly to match the reference XMI
//     out() << "    <system\n";
//     out() << "      xsi:type=\"chips.statements.system:implements_statement\"\n";
//     out() << "      implmentation=\"" << impl_info.path << "\">\n";

//     // 5. Generate the <implemented> element with variable expression
//     out() << "      <implemented\n";
//     out() << "        xsi:type=\"" << implemented_xsi_type << "\"\n";
//     out() << "        variable=\"" << implemented_info.path << "\" />\n";

//     // 6. Generate the <implementer> element with variable expression
//     out() << "      <implementer\n";
//     out() << "        xsi:type=\"" << implementer_xsi_type << "\"\n";
//     out() << "        variable=\"" << implementer_info.path << "\" />\n";

//     out() << "    </system>\n";
// }

// void ChipsToXmiVisitor::visit(link_node &node)
// {

//     semanticAnalyzer.analyze(node);

//     std::cerr << "[DEBUG Visitor] visit(link_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.statements.system");
//     ensure_namespace_for_prefix("chips.systemspecific.expressions");
//     ensure_namespace_for_prefix("chips.rvalues.system");
//     ensure_namespace_for_prefix("chips.xvalues.system");

//     std::string source = node.get_source();
//     std::string target = node.get_target();

//     std::cerr << "    Source: " << source << std::endl;
//     std::cerr << "    Target: " << target << std::endl;

//     SymbolInfo source_info = get_symbol_info(source);
//     SymbolInfo target_info = get_symbol_info(target);

//     std::string source_xsi_type = get_xsi_type_for_symbol(source_info);
//     std::string target_xsi_type = get_xsi_type_for_symbol(target_info);

//     out() << "    <" << m_statement_tag << "\n";
//     out() << "      xsi:type=\"chips.statements.system:link\">\n";
//     out() << "      <linked_component\n";
//     out() << "        xsi:type=\"" << source_xsi_type << "\"\n";
//     out() << "        variable=\"" << source_info.path << "\">\n";
//     write_index_from_suffixes(node.get_suffixes_source(),
//                               "        ",
//                               "chips.xvalues.system",
//                               "chips.rvalues.system",
//                               true);
//     out() << "      </linked_component>\n";



//     out() << "      <support_node\n";
//     out() << "        xsi:type=\"" << target_xsi_type << "\"\n";
//     out() << "        variable=\"" << target_info.path << "\">\n";
//     write_index_from_suffixes(node.get_suffixes_target(),
//                               "        ",
//                               "chips.xvalues.system",
//                               "chips.rvalues.system",
//                               true);
//     out() << "      </support_node>\n";
//     out() << "    </" << m_statement_tag << ">\n";
// }

// void ChipsToXmiVisitor::visit(plugging_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(plugging_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.statements.system");
//     ensure_namespace_for_prefix("chips.systemspecific.expressions");
//     ensure_namespace_for_prefix("chips.systemspecific.expressions.feeder");

//     // Parse eater side: instance.identifier
//     block_node *eater_block = node.get_block();
//     std::string eater_instance_name;
//     if (eater_block)
//     {
//         eater_instance_name = eater_block->get_identifier();
//     }
//     std::string eater_identifier = node.get_identifier();

//     std::cerr << "    Eater instance: " << eater_instance_name << std::endl;
//     std::cerr << "    Eater identifier: " << eater_identifier << std::endl;

//     // Parse feeder side: bp.push
//     expression_node *feeder_expr = node.get_expression();
//     std::string feeder_instance_name;
//     std::string feeder_identifier;

//     // Cast to plugging_expr_node to get feeder details
//     if (auto plugging_expr = dynamic_cast<plugging_expr_node *>(feeder_expr))
//     {
//         block_node *feeder_block = plugging_expr->get_block();
//         if (feeder_block)
//         {
//             feeder_instance_name = feeder_block->get_identifier();
//         }
//         feeder_identifier = plugging_expr->get_identifier();
//     }

//     std::cerr << "    Feeder instance: " << feeder_instance_name << std::endl;
//     std::cerr << "    Feeder identifier: " << feeder_identifier << std::endl;

//     // Lookup instances in symbol table
//     SymbolInfo eater_info = get_symbol_info(eater_instance_name);
//     SymbolInfo feeder_info = get_symbol_info(feeder_instance_name);
//     SymbolInfo eater_id_info = get_symbol_info(eater_identifier);
//     SymbolInfo feeder_id_info = get_symbol_info(feeder_identifier);

//     // Channel plugging
//     if (eater_id_info.type == "channel")
//     {
//         // Namespaces utilisés uniquement pour channel plugging et feeding logique
//         ensure_namespace_for_prefix("chips.xvalues.system");
//         ensure_namespace_for_prefix("chips.rvalues.system");
        
//         out() << "    <" << m_statement_tag << "\n";
//         out() << "      xsi:type=\"chips.statements.system:channel_plugging\">\n";

//         out() << "      <eater\n";
//         writeAttribute("        eating_channel", eater_id_info.path);
//         out() << ">\n";
//         out() << "        <node\n";
//         writeAttribute("          xsi:type", "chips.systemspecific.expressions:object_variable_expression");
//         out() << "\n";
//         writeAttribute("          variable", eater_info.path);
//         suffixes_node *eater_suffixes = eater_block ? eater_block->get_suffixes() : nullptr;
//         if (eater_suffixes && !eater_suffixes->get_suffixes().empty())
//         {
//             out() << ">\n";
//             write_index_from_suffixes(eater_suffixes,
//                                       "          ",
//                                       "chips.xvalues.system",
//                                       "chips.rvalues.system",
//                                       false);
//             out() << "        </node>\n";
//         }
//         else
//         {
//             out() << " />\n";
//         }
//         out() << "      </eater>\n";

//         out() << "      <feeder\n";
//         writeAttribute("        feeding_channel", feeder_id_info.path);
//         out() << ">\n";
//         out() << "        <node\n";
//         writeAttribute("          xsi:type", "chips.systemspecific.expressions:object_variable_expression");
//         out() << "\n";
//         writeAttribute("          variable", feeder_info.path);
//         suffixes_node *feeder_suffixes = nullptr;
//         if (auto plugging_expr = dynamic_cast<plugging_expr_node *>(feeder_expr))
//         {
//             if (auto feeder_block = plugging_expr->get_block())
//             {
//                 feeder_suffixes = feeder_block->get_suffixes();
//             }
//         }
//         if (feeder_suffixes && !feeder_suffixes->get_suffixes().empty())
//         {
//             out() << ">\n";
//             write_index_from_suffixes(feeder_suffixes,
//                                       "          ",
//                                       "chips.xvalues.system",
//                                       "chips.rvalues.system",
//                                       false);
//             out() << "        </node>\n";
//         }
//         else
//         {
//             out() << " />\n";
//         }
//         out() << "      </feeder>\n";

//         out() << "    </" << m_statement_tag << ">\n";
//         return;
//     }

//     bool is_physical = eater_id_info.type.find("sensor:") == 0 || feeder_id_info.type.find("actuator:") == 0;
//     bool is_logical = eater_id_info.type.find("logical_parameter:") == 0;

//     // Logical feeding
//     if (is_logical)
//     {
//         // Namespaces utilisés uniquement pour channel plugging et feeding logique
//         ensure_namespace_for_prefix("chips.xvalues.system");
//         ensure_namespace_for_prefix("chips.rvalues.system");
        
//         std::string dataflow_type = eater_id_info.type.substr(18); // after "logical_parameter:"
//         std::string param_path = eater_id_info.path;
//         size_t decl_pos = param_path.find("/@declaration/@variable");
//         if (decl_pos != std::string::npos)
//         {
//             param_path = param_path.substr(0, decl_pos);
//         }

//         out() << "    <" << m_statement_tag << "\n";
//         out() << "      xsi:type=\"chips.statements.system:feeding_logical_" << dataflow_type << "\">\n";

//         out() << "      <eater\n";
//         out() << "        parameter=\"" << param_path << "\">\n";
//         out() << "        <variable_expression\n";
//         out() << "          variable=\"" << eater_info.path << "\"";
//         suffixes_node *eater_suffixes = eater_block ? eater_block->get_suffixes() : nullptr;
//         if (eater_suffixes && !eater_suffixes->get_suffixes().empty())
//         {
//             out() << ">\n";
//             write_index_from_suffixes(eater_suffixes,
//                                       "          ",
//                                       "chips.xvalues.system",
//                                       "chips.rvalues.system",
//                                       false);
//             out() << "        </variable_expression>\n";
//         }
//         else
//         {
//             out() << " />\n";
//         }
//         out() << "      </eater>\n";

//         if (auto bin_expr = dynamic_cast<binary_expression_node *>(feeder_expr))
//         {
//             std::string op_name;
//             switch (bin_expr->get_type())
//             {
//             case PLUS_EXP:
//                 op_name = "plus";
//                 break;
//             case MINUS_EXP:
//                 op_name = "minus";
//                 break;
//             case TIMES_EXP:
//                 op_name = "times";
//                 break;
//             case DIV_EXP:
//                 op_name = "divide";
//                 break;
//             case MOD_EXP:
//                 op_name = "modulo";
//                 break;
//             default:
//                 op_name = "plus";
//                 break;
//             }

//             out() << "      <feeder\n";
//             writeAttribute("        xsi:type", "chips.rvalues.dataflow.operators.int:" + op_name);
//             out() << ">\n";

//             auto write_operand = [&](const std::string &tag, expression_node *operand)
//             {
//                 out() << "        <" << tag << "\n";
//                 if (dynamic_cast<variable_node *>(operand) || dynamic_cast<suffixised_node *>(operand))
//                 {
//                     writeAttribute("          xsi:type", "chips.xvalues.system:int_variable_expression");
//                     out() << "\n";
//                     writeAttribute("          variable", get_ast_path_by_name(getExpressionValue(*operand)));
//                     out() << " />\n";
//                     return;
//                 }
//                 if (auto num = dynamic_cast<number_literal_node *>(operand))
//                 {
//                     std::string value = getExpressionValue(*operand);
//                     writeAttribute("          xsi:type", "chips.rvalues.system:direct_int");
//                     if (!value.empty() && value != "0" && value != "0.0" && value != "false")
//                     {
//                         out() << "\n";
//                         writeAttribute("          value", value);
//                     }
//                     out() << " />\n";
//                     return;
//                 }
//                 writeAttribute("          xsi:type", "chips.rvalues.system:direct_int");
//                 out() << " />\n";
//             };

//             write_operand("left_operand", bin_expr->get_lhs());
//             write_operand("right_operand", bin_expr->get_rhs());
//             out() << "      </feeder>\n";
//         }
//         else if (auto cast_expr = dynamic_cast<collective_cast_node *>(feeder_expr))
//         {
//             std::string collective_name;
//             std::string output_name;
//             std::string feeder_block_name;

//             if (auto c_op = cast_expr->get_collective_operation())
//             {
//                 collective_name = c_op->get_identifier();
//             }
//             output_name = cast_expr->get_identifier();
//             if (auto feeder_block = cast_expr->get_block())
//             {
//                 feeder_block_name = feeder_block->get_identifier();
//             }

//             std::string collective_path = get_ast_path_by_name(collective_name);
//             std::string output_path = get_ast_path_by_name(output_name);
//             SymbolInfo feeder_block_info = get_symbol_info(feeder_block_name);
//             SymbolInfo output_info = get_symbol_info(output_name);
            
//             // Extraire le type de l'output depuis la table des symboles
//             std::string output_type = "int"; // Par défaut
//             if (!output_info.type.empty())
//             {
//                 size_t colon_pos = output_info.type.find(':');
//                 if (colon_pos != std::string::npos)
//                 {
//                     output_type = output_info.type.substr(colon_pos + 1);
//                 }
//             }

//             out() << "      <feeder\n";
//             writeAttribute("        xsi:type", "chips.systemspecific.expressions.feeder:logical_collective_cast");
//             out() << "\n";
//             writeAttribute("        collective_function", collective_path);
//             out() << ">\n";

//             out() << "        <logical_feeder_expression\n";
//             writeAttribute("          xsi:type", "chips.systemspecific.expressions.feeder:" + output_type + "_logical_output");
//             out() << "\n";
//             writeAttribute("          output", output_path);
//             out() << ">\n";

//             out() << "          <variable_expression\n";
//             writeAttribute("            variable", feeder_block_info.path);
//             out() << " />\n";
//             out() << "        </logical_feeder_expression>\n";
//             out() << "      </feeder>\n";
//         }
//         else if (dynamic_cast<variable_node *>(feeder_expr) || dynamic_cast<suffixised_node *>(feeder_expr))
//         {
//             out() << "      <feeder\n";
//             writeAttribute("        xsi:type", "chips.xvalues.system:int_variable_expression");
//             out() << "\n";
//             writeAttribute("        variable", get_ast_path_by_name(getExpressionValue(*feeder_expr)));
//             out() << " />\n";
//         }
//         else
//         {
//             out() << "      <feeder\n";
//             writeAttribute("        xsi:type", "chips.rvalues.system:direct_int");
//             out() << " />\n";
//         }

//         out() << "    </" << m_statement_tag << ">\n";
//         return;
//     }

//     // Physical feeding (default)
//     std::string dataflow_type = "bool";
//     if (eater_id_info.type.find("sensor:") == 0)
//     {
//         dataflow_type = eater_id_info.type.substr(7);
//     }
//     else if (feeder_id_info.type.find("actuator:") == 0)
//     {
//         dataflow_type = feeder_id_info.type.substr(9);
//     }

//     std::string sensor_param_path = eater_id_info.path;
//     size_t decl_pos = sensor_param_path.find("/@declaration/@variable");
//     if (decl_pos != std::string::npos)
//     {
//         sensor_param_path = sensor_param_path.substr(0, decl_pos);
//     }

//     out() << "    <" << m_statement_tag << "\n";
//     out() << "      xsi:type=\"chips.statements.system:feeding_physical_" << dataflow_type << "\">\n";

//     out() << "      <eater\n";
//     out() << "        parameter=\"" << sensor_param_path << "\">\n";
//     out() << "        <variable_expression\n";
//     out() << "          variable=\"" << eater_info.path << "\"";
//     suffixes_node *eater_suffixes = eater_block ? eater_block->get_suffixes() : nullptr;
//     if (eater_suffixes && !eater_suffixes->get_suffixes().empty())
//     {
//         out() << ">\n";
//         write_index_from_suffixes(eater_suffixes,
//                                   "          ",
//                                   "chips.xvalues.system",
//                                   "chips.rvalues.system",
//                                   false);
//         out() << "        </variable_expression>\n";
//     }
//     else
//     {
//         out() << " />\n";
//     }
//     out() << "      </eater>\n";

//     out() << "      <feeder\n";
//     out() << "        xsi:type=\"chips.systemspecific.expressions.feeder:" << dataflow_type << "_physical_output\"\n";
//     out() << "        output=\"" << feeder_id_info.path << "\">\n";
//     out() << "        <variable_expression\n";
//     out() << "          variable=\"" << feeder_info.path << "\"";
//     suffixes_node *feeder_suffixes = nullptr;
//     if (auto plugging_expr = dynamic_cast<plugging_expr_node *>(feeder_expr))
//     {
//         if (auto feeder_block = plugging_expr->get_block())
//         {
//             feeder_suffixes = feeder_block->get_suffixes();
//         }
//     }
//     if (feeder_suffixes && !feeder_suffixes->get_suffixes().empty())
//     {
//         out() << ">\n";
//         write_index_from_suffixes(feeder_suffixes,
//                                   "          ",
//                                   "chips.xvalues.system",
//                                   "chips.rvalues.system",
//                                   false);
//         out() << "        </variable_expression>\n";
//     }
//     else
//     {
//         out() << " />\n";
//     }
//     out() << "      </feeder>\n";

//     out() << "    </" << m_statement_tag << ">\n";
// }

// void ChipsToXmiVisitor::visit(s_loop_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(s_loop_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.statements.system");
//     ensure_namespace_for_prefix("chips.xvalues.system");
//     ensure_namespace_for_prefix("chips.rvalues.system");

//     std::string iterator_name = node.get_identifier();

//     std::cerr << "    Iterator: " << iterator_name << std::endl;

//     out() << "    <system\n";
//     out() << "      xsi:type=\"chips.statements.system:foreach\">\n";

//     // Generate iterator
//     out() << "      <iterator\n";
//     out() << "        xsi:type=\"chips.statements.system:int_declaration\">\n";
//     out() << "        <variable\n";
//     out() << "          name=\"" << iterator_name << "\" />\n";
//     out() << "      </iterator>\n";

//     std::string iterator_path = get_ast_path() + "/@iterator/@variable";
//     register_variable(iterator_name, iterator_path, "int");
//     std::cerr << "[DEBUG] Iterator '" << iterator_name << "' enregistré avec le chemin: " << iterator_path << std::endl;

//     // Generate iterable expression
//     if (auto loop_expr = node.get_loop_expr())
//     {
//         std::cerr << "[DEBUG Visitor] s_loop_node has loop expression" << std::endl;
//         out() << "      <iterable_expr\n";
//         push_ast_path("/@iterable_expr");
//         loop_expr->accept(*this);
//         pop_ast_path("/@iterable_expr");
//         out() << " />\n";
//     }

//     // Generate statements - change tag to "statements" for foreach body
//     if (auto stts = node.get_statements())
//     {
//         std::cerr << "[DEBUG Visitor] s_loop_node has statements" << std::endl;
//         std::string old_tag = m_statement_tag;
//         m_statement_tag = "statements";
//         push_ast_path("/@statements");
//         stts->accept(*this);
//         pop_ast_path("/@statements");
//         m_statement_tag = old_tag;
//     }

//     out() << "    </system>\n";
// }

// void ChipsToXmiVisitor::visit(s_if_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(s_if_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.statements.system");
//     ensure_namespace_for_prefix("chips.rvalues.system");

//     out() << "    <" << m_statement_tag << "\n";
//     out() << "      xsi:type=\"chips.statements.system:if\">\n";

//     // Generate condition
//     if (auto cond = node.get_condition())
//     {
//         std::cerr << "[DEBUG Visitor] s_if_node has condition" << std::endl;
//         out() << "      <condition\n";
//         push_ast_path("/@condition");
//         cond->accept(*this);
//         pop_ast_path("/@condition");
//         out() << "      </condition>\n";
//     }

//     // Generate if_section - change tag to "if_statements" for if body
//     out() << "      <if_section>\n";
//     if (auto stts = node.get_statements())
//     {
//         std::cerr << "[DEBUG Visitor] s_if_node has statements" << std::endl;
//         std::string old_tag = m_statement_tag;
//         m_statement_tag = "if_statements";
//         push_ast_path("/@if_section/@if_statements");
//         stts->accept(*this);
//         pop_ast_path("/@if_section/@if_statements");
//         m_statement_tag = old_tag;
//     }
//     out() << "      </if_section>\n";

//     out() << "    </" << m_statement_tag << ">\n";
// }

// void ChipsToXmiVisitor::visit(s_if_else_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(s_if_else_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.statements.system");

//     out() << "    <" << m_statement_tag << "\n";
//     out() << "      xsi:type=\"chips.statements.system:if\">\n";

//     // Get the if_node which contains condition and if statements
//     if (auto ifnode = node.get_if_node())
//     {
//         std::cerr << "[DEBUG Visitor] s_if_else_node has if_node" << std::endl;

//         // Generate condition
//         if (auto cond = ifnode->get_condition())
//         {
//             std::cerr << "[DEBUG Visitor] s_if_else_node condition" << std::endl;
//             out() << "      <condition\n";
//             push_ast_path("/@condition");
//             cond->accept(*this);
//             pop_ast_path("/@condition");
//             out() << "      </condition>\n";
//         }

//         // Generate if_section - change tag to "if_statements" for if body
//         out() << "      <if_section>\n";
//         if (auto if_stts = ifnode->get_statements())
//         {
//             std::cerr << "[DEBUG Visitor] s_if_else_node if statements" << std::endl;
//             std::string old_tag = m_statement_tag;
//             m_statement_tag = "if_statements";
//             push_ast_path("/@if_section/@if_statements");
//             if_stts->accept(*this);
//             pop_ast_path("/@if_section/@if_statements");
//             m_statement_tag = old_tag;
//         }
//         out() << "      </if_section>\n";
//     }

//     // Generate else_section if there are else statements - use "else_statements" tag
//     if (auto else_stts = node.get_else_node())
//     {
//         std::cerr << "[DEBUG Visitor] s_if_else_node has else statements" << std::endl;
//         out() << "      <else_section>\n";
//         std::string old_tag = m_statement_tag;
//         m_statement_tag = "else_statements";
//         push_ast_path("/@else_section/@else_statements");
//         else_stts->accept(*this);
//         pop_ast_path("/@else_section/@else_statements");
//         m_statement_tag = old_tag;
//         out() << "      </else_section>\n";
//     }

//     out() << "    </" << m_statement_tag << ">\n";
// }

// void ChipsToXmiVisitor::visit(functionnal_block_instanciation_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(functionnal_block_instanciation_node)" << std::endl;

//     std::string def_name = node.get_ident1();  // Ex: "PhysicalCounter"
//     std::string inst_name = node.get_ident2(); // Ex: "pc"

//     std::cerr << "    Definition: " << def_name << std::endl;
//     std::cerr << "    Instance: " << inst_name << std::endl;

//     // 1. Lookup the definition in symbol table
//     SymbolInfo def_info = get_symbol_info(def_name);

//     // 2. Get the declaration xsi:type based on definition type
//     std::string xsi_type = get_declaration_type_from_definition(def_info.type);
//     ensure_namespace_for_type(xsi_type);

//     std::cerr << "    Definition type: " << def_info.type << std::endl;
//     std::cerr << "    Declaration xsi:type: " << xsi_type << std::endl;
//     std::cerr << "    Definition path: " << def_info.path << std::endl;

//     // 3. Generate the system declaration
//     out() << "    <system\n";
//     out() << "      xsi:type=\"" << xsi_type << "\"\n";
//     out() << "      def=\"" << def_info.path << "\">\n";

//     // 4. Generate variable element
//     out() << "      <variable\n";
//     out() << "        name=\"" << inst_name << "\"";

//     // 5. Handle optional dimensions (suffixes)
//     suffixes_node *suffixes = node.get_suffixes();
//     if (suffixes && !suffixes->get_suffixes().empty())
//     {
//         out() << ">\n";
//         out() << "        <dimensions\n";

//         for (auto &suffix_expr : suffixes->get_suffixes())
//         {
//             if (suffix_expr)
//             {
//                 suffix_expr->accept(*this);
//             }
//         }
//         out() << "        />\n";
//         out() << "      </variable>\n";
//     }
//     else
//     {
//         out() << " />\n";
//     }

//     out() << "    </system>\n";

//     // 6. Register the instance in symbol table
//     // The instance inherits the type from its definition (physical, logical, object)
//     std::string instance_path = get_ast_path() + "/@variable";
//     register_variable(inst_name, instance_path, def_info.type);

//     std::cerr << "    Registered instance '" << inst_name << "' with type '" << def_info.type
//               << "' at path: " << instance_path << std::endl;
// }

// // === DECLARATION CONTEXT ===

// void ChipsToXmiVisitor::visit(object_definition_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(object_definition_node) name=" << node.get_identifier() << std::endl;

//     // Enregistrer l'objet lui-même dans la table des symboles
//     // Le chemin est : //@preamble/@definitions.X (où X est déterminé par le contexte d'appel)
//     register_variable(node.get_identifier(), get_ast_path(), "object");
    
//     // Extract the definition index from the current path
//     int def_index = 0;
//     std::string path = get_ast_path();
//     size_t pos = path.rfind("@definitions.");
//     if (pos != std::string::npos) {
//         try {
//             def_index = std::stoi(path.substr(pos + 13));
//         } catch (...) {
//             def_index = 0;
//         }
//     }
    
//     // Register the definition in the definitions table
//     register_definition(node.get_identifier(), "object", get_ast_path(), def_index);
//     m_current_definition = node.get_identifier();
    
//     std::cerr << "[DEBUG] Object '" << node.get_identifier() << "' enregistré avec le chemin: " << get_ast_path() << std::endl;

//     out() << "    <definitions\n";
//     writeAttribute("      xsi:type", "definitions:object_definition");
//     out() << "\n";
//     writeAttribute("      name", node.get_identifier());
//     out() << ">\n";

//     // Visiter la section "with" si elle existe
//     if (auto with = node.get_with())
//     {
//         std::cerr << "[DEBUG Visitor] Object a une section with" << std::endl;
//         push_ast_path("/@with");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         with->accept(*this);
//         pop_ast_path("/@with");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//     }
//     else
//     {
//         std::cerr << "[DEBUG Visitor] Object SANS section with" << std::endl;
//     }

//     m_current_definition = "";  // Reset current definition
//     out() << "    </definitions>\n";
// }

void ChipsToXmiVisitor::visit(chips::function_definition& node)
{
    std::cerr << "[DEBUG Visitor] visit(function_definition_node) - classe abstraite" << std::endl;
    out() << "    <!-- function_definition_node abstrait -->\n";
}

void ChipsToXmiVisitor::visit(chips::logical_definition &node)
{
//     semanticAnalyzer.analyze(node);

    std::cerr << "[DEBUG Visitor] visit(logical_definition) name=" << node.get_identifier() << std::endl;

    // Enregistrer la définition logique dans la table des symboles
    register_variable(node.get_identifier(), get_ast_path(), "logical");
    
    // Extract the definition index from the current path
    int def_index = 0;
    std::string path = get_ast_path();
    size_t pos = path.rfind("@definitions.");
    if (pos != std::string::npos) {
        try {
            def_index = std::stoi(path.substr(pos + 13));
        } catch (...) {
            def_index = 0;
        }
    }
    
    // Register the definition in the definitions table
    register_definition(node.get_identifier(), "logical", get_ast_path(), def_index);
    m_current_definition = node.get_identifier();
    
    std::cerr << "[DEBUG] Logical definition '" << node.get_identifier() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    out() << "    <definitions\n";
    writeAttribute("      xsi:type", "definitions:logical_definition");
    out() << "\n";
    writeAttribute("      name", node.get_identifier());
    out() << ">\n";

    // Enregistrer et générer les paramètres logiques (dataflow parameters)
    if(!node.get_parameters().empty()){
        std::cerr << "[DEBUG Visitor] Logical a des paramètres" << std::endl; 
        int param_index = 0;

        for(auto& param : node.get_parameters()){
            std::visit([this](auto* p) {
                if(p){
                    out() << "paramètre\n";
                    // std::string param_name = p->get_identifier();
                    // auto param_type = p->get_df_type();
                    // std::string dataflow_type = "int";

                    // if (param_type)
                    // {
                    //     DATAFLOW_TYPE df_type = param_type->get_type();
                    //     if (df_type == FLOAT_DF)
                    //         dataflow_type = "float";
                    //     else if (df_type == BOOL_DF)
                    //         dataflow_type = "bool";
                    // }

                    // // Chemin pour paramètre logique: //@preamble/@definitions.X/@parameters.Y/@declaration/@variable
                    // std::string param_base_path = get_ast_path() + "/@parameters." + std::to_string(param_index);
                    // std::string param_path = param_base_path + "/@declaration/@variable";
                    // // Enregistrer avec chemin complet pour les références
                    // register_variable(param_name, param_path, "logical_parameter:" + dataflow_type);
                    // std::cerr << "[DEBUG] Paramètre logique '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;

                    // std::cerr << "[DEBUG] Génération balise <parameters> pour '" << param_name << "'" << std::endl;
                    // push_ast_path("/@parameters." + std::to_string(param_index));
                    // out() << "      <parameters\n";
                    // writeAttribute("          xsi:type", "chips.parameters.logical:" + dataflow_type + "_logical_parameter");
                    // out() << "\n";
                    // writeAttribute("          name", param_name);
                    // out() << ">\n";

                    // out() << "        <declaration>\n";
                    // push_ast_path("/@declaration");
                    // out() << "          <variable\n";
                    // writeAttribute("              name", param_name);
                    // out() << "/>\n";
                    // pop_ast_path("/@declaration");
                    // out() << "        </declaration>\n";

                    // out() << "      </parameters>\n";
                    // std::cerr << "[DEBUG] Balise <parameters> terminée pour '" << param_name << "'" << std::endl;
                    // pop_ast_path("/@parameters." + std::to_string(param_index));

                    // param_index++;
                }
            }, param);
        }
    }

    if(auto init = node.get_init()){
        std::cerr << "[DEBUG Visitor] Logical a une section init" << std::endl;
        push_ast_path("/@init");
        init->accept(*this);
        pop_ast_path("/@init");
    }

    if (auto then = node.get_then())
    {
        std::cerr << "[DEBUG Visitor] Logical a une section then" << std::endl;
        push_ast_path("/@then");
        then->accept(*this);
        pop_ast_path("/@then");
    }

    if(!node.get_outputs().empty()){
        std::cerr << "[DEBUG Visitor] Logical a des outputs" << std::endl;
        for(auto& output : node.get_outputs()){
            std::visit([this](auto* o) {
                if(o){
                    o->accept(*this);
                }
            }, output);
        }
    }else{
        std::cerr << "[DEBUG Visitor] Logical SANS outputs" << std::endl;
    }

    m_current_definition = "";  // Reset current definition
    out() << "    </definitions>\n";
}

// void ChipsToXmiVisitor::visit(physical_function_definition_node &node)
// {
//     semanticAnalyzer.analyze(node);

//     std::cerr << "[DEBUG Visitor] visit(physical_function_definition_node) name=" << node.get_identifier() << std::endl;

//     // Enregistrer la définition physique dans la table des symboles
//     // Le chemin est : //@preamble/@definitions.X (déterminé par le contexte d'appel)
//     register_variable(node.get_identifier(), get_ast_path(), "physical");
    
//     // Extract the definition index from the current path (e.g., "//@preamble/@definitions.0" -> 0)
//     int def_index = 0;
//     std::string path = get_ast_path();
//     size_t pos = path.rfind("@definitions.");
//     if (pos != std::string::npos) {
//         try {
//             def_index = std::stoi(path.substr(pos + 13));
//         } catch (...) {
//             def_index = 0;
//         }
//     }
    
//     // Register the definition in the definitions table
//     register_definition(node.get_identifier(), "physical", get_ast_path(), def_index);
//     m_current_definition = node.get_identifier();
    
//     std::cerr << "[DEBUG] Physical definition '" << node.get_identifier() << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

//     out() << "    <definitions\n";
//     writeAttribute("      xsi:type", "definitions:physical_definition");
//     out() << "\n";
//     writeAttribute("      name", node.get_identifier());
//     out() << ">\n";

//     // Enregistrer les paramètres (sensors, actuators, etc.) dans la table des symboles
//     if (auto params = node.get_pdf_parameter_list())
//     {
//         std::cerr << "[DEBUG Visitor] Physical a des paramètres" << std::endl;
//         int sensor_index = 0;

//         for (auto &param : params->get_pdf_param_decls())
//         {
//             if (param)
//             {
//                 std::string param_name = param->get_identifier();
//                 auto param_type = param->get_df_type();
//                 std::string dataflow_type = "int";

//                 if (param_type && param_type->get_df_type())
//                 {
//                     DATAFLOW_TYPE df_type = param_type->get_df_type()->get_type();
//                     if (df_type == FLOAT_DF)
//                         dataflow_type = "float";
//                     else if (df_type == BOOL_DF)
//                         dataflow_type = "bool";
//                 }

//                 // TODO: Vérifier si c'est un sensor ou actuator via is_sensor
//                 // Pour l'instant, on suppose que c'est un sensor si le nom du paramètre est typique
//                 // Une meilleure approche serait d'ajouter une méthode is_sensor() à physical_dataflow_parameter_type_node

//                 // Chemin pour sensor: //@preamble/@definitions.X/@sensor.Y/@declaration/@variable
//                 // This is the full path for variable expressions to reference
//                 std::string sensor_base_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index);
//                 std::string param_path = sensor_base_path + "/@declaration/@variable";
//                 // Register with full path for variable expression references
//                 register_variable(param_name, param_path, "sensor:" + dataflow_type);
//                 std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
//                 sensor_index++;
//             }
//         }
//     }

//     // Visiter les sections dans l'ordre : with, init, then, puis outputs
//     // (outputs doit être visité après init/then pour avoir accès aux chemins des variables déclarées)
//     if (auto with = node.get_with())
//     {
//         std::cerr << "[DEBUG Visitor] Physical a une section with" << std::endl;
//         push_ast_path("/@with");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         with->accept(*this);
//         pop_ast_path("/@with");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//     }

//     if (auto init = node.get_init())
//     {
//         std::cerr << "[DEBUG Visitor] Physical a une section init" << std::endl;
//         push_ast_path("/@init");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         init->accept(*this);
//         pop_ast_path("/@init");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//     }

//     if (auto then = node.get_then())
//     {
//         std::cerr << "[DEBUG Visitor] Physical a une section then" << std::endl;
//         push_ast_path("/@then");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         then->accept(*this);
//         pop_ast_path("/@then");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//     }

//     if (auto outputs = node.get_outputs())
//     {
//         std::cerr << "[DEBUG Visitor] Physical a des outputs" << std::endl;
//         outputs->accept(*this);
//     }

//     // Générer les sensors
//     if (auto params = node.get_pdf_parameter_list())
//     {
//         std::cerr << "[DEBUG Visitor] Génération des sensors" << std::endl;
//         int sensor_index = 0;

//         for (auto &param : params->get_pdf_param_decls())
//         {
//             if (param)
//             {
//                 std::string param_name = param->get_identifier();
//                 auto param_type = param->get_df_type();

//                 // Déterminer le type du paramètre
//                 std::string dataflow_type = "int"; // Default
//                 if (param_type && param_type->get_df_type())
//                 {
//                     DATAFLOW_TYPE df_type = param_type->get_df_type()->get_type();
//                     if (df_type == INT_DF)
//                         dataflow_type = "int";
//                     else if (df_type == FLOAT_DF)
//                         dataflow_type = "float";
//                     else if (df_type == BOOL_DF)
//                         dataflow_type = "bool";
//                 }

//                 std::cerr << "[DEBUG] Génération du sensor #" << sensor_index << ": " << param_name << " (" << dataflow_type << ")" << std::endl;

//                 push_ast_path("/@sensor." + std::to_string(sensor_index));
//                 std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

//                 out() << "      <sensor\n";
//                 writeAttribute("          xsi:type", "chips.parameters.physical:" + dataflow_type + "_physical_parameter");
//                 out() << "\n";
//                 writeAttribute("          name", param_name);
//                 out() << ">\n";

//                 out() << "        <declaration>\n";
//                 push_ast_path("/@declaration");
//                 out() << "          <variable\n";
//                 writeAttribute("              name", param_name);
//                 out() << "/>\n";
//                 pop_ast_path("/@declaration");
//                 out() << "        </declaration>\n";

//                 out() << "      </sensor>\n";

//                 pop_ast_path("/@sensor." + std::to_string(sensor_index));
//                 std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//                 sensor_index++;
//             }
//         }
//     }

//     m_current_definition = "";  // Reset current definition
//     out() << "    </definitions>\n";
// }

// void ChipsToXmiVisitor::visit(collective_operation_definition_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_operation_definition_node)" << std::endl;

//     if (auto sig = node.get_signature())
//     {
//         std::string func_name = sig->get_ident1();
//         std::string support_obj = sig->get_ident2();
//         std::string support_obj_path = get_ast_path_by_name(support_obj);

//         std::cerr << "[DEBUG Visitor] Collective function: " << func_name << ", support_object: " << support_obj << std::endl;

//         // Enregistrer la fonction collective dans la table des symboles
//         register_variable(func_name, get_ast_path(), "collective_operation");
//         std::cerr << "[DEBUG] Collective operation '" << func_name << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

//         out() << "    <definitions\n";
//         writeAttribute("      xsi:type", "definitions:collective_function_definition");
//         out() << "\n";
//         writeAttribute("      name", func_name);
//         out() << "\n";
//         writeAttribute("      support_object", support_obj_path);
//         out() << ">\n";

//         // Accumulateurs (paramètres collectifs)
//         if (auto cdf_decls = sig->get_collective_dataflow_defaulted_decls())
//         {
//             out() << "      <accumulator>\n";
//             int accum_index = 0;
//             for (auto &decl : cdf_decls->get_cdf_defaulted_decls())
//             {
//                 if (decl)
//                 {
//                     std::string param_name = decl->get_identifier();
//                     auto param_type = decl->get_df_type();
//                     std::string dataflow_type = "int";

//                     if (param_type)
//                     {
//                         DATAFLOW_TYPE df_type = param_type->get_type();
//                         if (df_type == FLOAT_DF)
//                             dataflow_type = "float";
//                         else if (df_type == BOOL_DF)
//                             dataflow_type = "bool";
//                     }

//                     std::cerr << "[DEBUG Visitor] Accumulator parameter: " << param_name << " (" << dataflow_type << ")" << std::endl;

//                     // Enregistrer le paramètre dans la table des symboles
//                     std::string param_path = get_ast_path() + "/@accumulator/@accumulator." + std::to_string(accum_index) + "/@declaration/@variable";
//                     register_variable(param_name, param_path, "collective_parameter:" + dataflow_type);

//                     out() << "        <accumulator\n";
//                     writeAttribute("          xsi:type", "chips.parameters.collective:" + dataflow_type + "_collective_parameter");
//                     out() << ">\n";

//                     // default_value
//                     if (auto default_expr = decl->get_expression())
//                     {
//                         out() << "          <default_value\n";

//                         if (auto input_expr = dynamic_cast<input_node *>(default_expr))
//                         {
//                             writeAttribute("            xsi:type", "chips.rvalues.collective:input_kw");
//                         }
//                         else if (auto suf = dynamic_cast<suffixised_node *>(default_expr))
//                         {
//                             std::string val_name = suf->get_identifier();
//                             if (val_name == "input")
//                                 writeAttribute("            xsi:type", "chips.rvalues.collective:input_kw");
//                             else if (val_name == "stop")
//                                 writeAttribute("            xsi:type", "chips.rvalues.collective:stop_kw");
//                         }
//                         else if (auto num = dynamic_cast<number_literal_node *>(default_expr))
//                         {
//                             std::string literal_type = "int";
//                             std::string literal_value;
//                             EXPRESSION_TYPE type = num->get_type();
//                             if (type == FLOAT_EXP)
//                             {
//                                 literal_type = "float";
//                                 literal_value = std::to_string(num->get_float());
//                             }
//                             else if (type == BOOL_EXP)
//                             {
//                                 literal_type = "bool";
//                                 literal_value = num->get_bool() ? "true" : "false";
//                             }
//                             else
//                             {
//                                 literal_type = "int";
//                                 literal_value = std::to_string(num->get_int());
//                             }
//                             writeAttribute("            xsi:type", "chips.rvalues.collective:direct_" + literal_type);
//                             out() << "\n";
//                             writeAttribute("            value", literal_value);
//                         }
//                         out() << " />\n";
//                     }

//                     // declaration
//                     out() << "          <declaration>\n";
//                     out() << "            <variable\n";
//                     writeAttribute("              name", param_name);
//                     out() << " />\n";
//                     out() << "          </declaration>\n";

//                     out() << "        </accumulator>\n";
//                     accum_index++;
//                 }
//             }
//             out() << "      </accumulator>\n";
//         }

//         // Operations (statements)
//         if (auto stmts = node.get_statements())
//         {
//             out() << "      <operations>\n";
//             push_ast_path("/@operations");
            
//             int stmt_index = 0;
//             for (auto &stmt : stmts->get_statements())
//             {
//                 if (stmt)
//                 {
//                     std::cerr << "[DEBUG] Traitement statement à index: " << stmt_index << std::endl;
//                     m_extra_statements_generated = 0;  // Réinitialiser le compteur
                    
//                     std::string segment = "/@statements." + std::to_string(stmt_index);
//                     push_ast_path(segment);
//                     std::cerr << "[DEBUG] Segment poussé: " << segment << ", AST path: " << get_ast_path() << std::endl;
//                     stmt->accept(*this);
//                     pop_ast_path(segment);
                    
//                     std::cerr << "[DEBUG] Statements extra générés: " << m_extra_statements_generated << std::endl;
//                     stmt_index++;  // Incrémenter pour le statement actuel
//                     stmt_index += m_extra_statements_generated;  // Ajouter les statements supplémentaires
//                     std::cerr << "[DEBUG] Prochain index: " << stmt_index << std::endl;
//                 }
//             }
            
//             pop_ast_path("/@operations");
//             out() << "      </operations>\n";
//         }

//         // current_object_output
//         if (auto exprs = node.get_expressions())
//         {
//             const auto &expr_list = exprs->get_expressions();
//             if (!expr_list.empty())
//             {
//                 out() << "      <current_object_output>\n";
//                 write_collective_output_expression(*expr_list[0], "expression", "        ");
//                 out() << "      </current_object_output>\n";
//             }
//         }

//         // channeled_output (from node.get_output())
//         if (auto output = node.get_output())
//         {
//             std::string output_id = output->get_identifier();
//             auto output_exprs = output->get_expressions();

//             if (output_id != "default")
//             {
//                 // C'est un channeled_output
//                 std::string channel_path = get_ast_path_by_name(output_id);
//                 if (channel_path == output_id)
//                 {
//                     // Non trouvé, essayer de construire le chemin manuellement
//                     channel_path = support_obj_path + "/@with/@statements.0";
//                 }

//                 out() << "      <channeled_output\n";
//                 writeAttribute("        channel", channel_path);
//                 out() << ">\n";

//                 if (output_exprs)
//                 {
//                     const auto &expr_list = output_exprs->get_expressions();
//                     for (size_t i = 0; i < expr_list.size(); ++i)
//                     {
//                         if (expr_list[i])
//                         {
//                             write_collective_output_expression(*expr_list[i], "accumulator_expressions", "        ");
//                         }
//                     }
//                 }
//                 out() << "      </channeled_output>\n";
//             }
//         }

//         // default_output (from optionnal_output)
//         if (auto opt_outputs = node.get_optionnal_output())
//         {
//             const auto &outputs = opt_outputs->get_outputs();
//             for (auto &output_node : outputs)
//             {
//                 if (output_node)
//                 {
//                     std::string output_id = output_node->get_identifier();
//                     auto output_exprs = output_node->get_expressions();

//                     if (output_id == "default")
//                     {
//                         // default_output
//                         out() << "      <default_output>\n";
//                         if (output_exprs)
//                         {
//                             const auto &expr_list = output_exprs->get_expressions();
//                             for (size_t i = 0; i < expr_list.size(); ++i)
//                             {
//                                 if (expr_list[i])
//                                 {
//                                     write_collective_output_expression(*expr_list[i], "accumulator_expressions", "        ");
//                                 }
//                             }
//                         }
//                         out() << "      </default_output>\n";
//                     }
//                 }
//             }
//         }

//         out() << "    </definitions>\n";
//     }
// }

// void ChipsToXmiVisitor::visit(implementation_definition_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(implementation_definition_node) name=" << node.get_ident1() << std::endl;

//     std::cerr << "[DEBUG Visitor] visit(implementation_definition_node) name=" << node.get_ident1() << std::endl;

//     register_variable(node.get_ident1(), get_ast_path(), "implementation");

//     std::cerr << "what is in std::unique_ptr<node_mappings_node> node; ?" << std::endl;

//     ensure_namespace_for_prefix("chips.statements.implementation");

//     out() << "    <definitions\n";
//     writeAttribute("      xsi:type", "definitions:implementation_definition");
//     out() << "\n";
//     writeAttribute("      name", node.get_ident1());
//     out() << "\n";
    
//     // Save the definition names for use in node_mappings_node
//     m_impl_def_implemented_object = node.get_ident2();
//     m_impl_def_implementing_node = node.get_ident3();
    
//     // Try to find the implemented object definition
//     std::string implemented_obj_name = node.get_ident2();
//     std::string implemented_obj_path = "";
//     auto it = m_definitions_table.find(implemented_obj_name);
//     if (it != m_definitions_table.end()) {
//         implemented_obj_path = it->second.path;
//         std::cerr << "[DEBUG] Found implemented_object '" << implemented_obj_name << "' at path: " << implemented_obj_path << std::endl;
//     } else {
//         // Fallback to get_ast_path_by_name if not found
//         implemented_obj_path = get_ast_path_by_name(implemented_obj_name);
//         std::cerr << "[WARNING] Implemented_object '" << implemented_obj_name << "' not found in definitions_table, using fallback: " << implemented_obj_path << std::endl;
//     }
//     writeAttribute("      implemented_object", implemented_obj_path);
//     out() << "\n";
    
//     // Try to find the implementing node definition
//     std::string implementing_node_name = node.get_ident3();
//     std::string implementing_node_path = "";
//     it = m_definitions_table.find(implementing_node_name);
//     if (it != m_definitions_table.end()) {
//         implementing_node_path = it->second.path;
//         std::cerr << "[DEBUG] Found implementing_node '" << implementing_node_name << "' at path: " << implementing_node_path << std::endl;
//     } else {
//         // Fallback to get_ast_path_by_name if not found
//         implementing_node_path = get_ast_path_by_name(implementing_node_name);
//         std::cerr << "[WARNING] Implementing_node '" << implementing_node_name << "' not found in definitions_table, using fallback: " << implementing_node_path << std::endl;
//     }
//     writeAttribute("      implementing_node", implementing_node_path);
//     out() << ">\n";
    
//     // gestions des having statements
//     if (auto having = node.get_node())
//     {
//         std::cerr << "[DEBUG Visitor] Implementation a des having statements" << std::endl;
//         push_ast_path("/@having");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         having->accept(*this);
//         pop_ast_path("/@having");
//         std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//     }
//     else
//     {
//         std::cerr << "[DEBUG Visitor] Implementation SANS having statements" << std::endl;
//     }

//     // Reset the implementation definition context
//     m_impl_def_implemented_object = "";
//     m_impl_def_implementing_node = "";
    
//     out() << "    </definitions>\n";
// }

// void ChipsToXmiVisitor::visit(node_mappings_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(node_mappings_node)" << std::endl;

//     // Récupérer les noms des variables source (implementing) et cible (implemented)
//     std::string implementing_var_name = node.get_ident1();
//     std::string implemented_var_name = node.get_ident2();

//     // Ignorer les nodes vides (fin de liste chaînée)
//     if (implementing_var_name.empty() && implemented_var_name.empty())
//     {
//         std::cerr << "[DEBUG] Node mapping vide (fin de liste), ignoré" << std::endl;
//         return;
//     }

//     // Find the paths of the variables in the appropriate definitions
//     std::string implementing_var_path = "";
//     std::string implemented_var_path = "";
//     std::string var_type = "unknown";
    
//     // Find implementing variable in the implementing node definition
//     if (!m_impl_def_implementing_node.empty()) {
//         SymbolInfo var_info = find_variable_in_definition(m_impl_def_implementing_node, implementing_var_name);
//         if (!var_info.path.empty()) {
//             implementing_var_path = var_info.path;
//             var_type = var_info.type;
//             std::cerr << "[DEBUG] Found implementing_var '" << implementing_var_name << "' in '" << m_impl_def_implementing_node << "': " << implementing_var_path << std::endl;
//         }
//     }
    
//     // Find implemented variable in the implemented object definition
//     if (!m_impl_def_implemented_object.empty()) {
//         SymbolInfo var_info = find_variable_in_definition(m_impl_def_implemented_object, implemented_var_name);
//         if (!var_info.path.empty()) {
//             implemented_var_path = var_info.path;
//             std::cerr << "[DEBUG] Found implemented_var '" << implemented_var_name << "' in '" << m_impl_def_implemented_object << "': " << implemented_var_path << std::endl;
//         }
//     }
    
//     // If not found using definitions, fallback to symbol table
//     if (implementing_var_path.empty()) {
//         SymbolInfo impl_info = get_symbol_info(implementing_var_name);
//         implementing_var_path = get_ast_path_by_name(implementing_var_name);
//         var_type = impl_info.type;
//         std::cerr << "[WARNING] Could not find implementing_var '" << implementing_var_name << "' in definitions, using fallback" << std::endl;
//     }
    
//     if (implemented_var_path.empty()) {
//         implemented_var_path = get_ast_path_by_name(implemented_var_name);
//         std::cerr << "[WARNING] Could not find implemented_var '" << implemented_var_name << "' in definitions, using fallback" << std::endl;
//     }

//     std::cerr << "[DEBUG] Having statement: " << implementing_var_name << " (type=" << var_type << ") as " << implemented_var_name << std::endl;

//     // Écrire le having_statement avec le bon type
//     out() << "      <having_statements\n";

//     if (var_type == "channel")
//     {
//         writeAttribute("        xsi:type", statement_type("channel_aliasing", StatementFamily::Implementation));
//         out() << "\n";
//         writeAttribute("        implementing_channel", implementing_var_path);
//         out() << "\n";
//         writeAttribute("        implemented_channel", implemented_var_path);
//         out() << " />\n";
//     }
//     else if (var_type == "contextual")
//     {
//         writeAttribute("        xsi:type", statement_type("contextual_aliasing", StatementFamily::Implementation));
//         out() << "\n";
//         // For contextual variables, we need to point to the statement, not the inner variable
//         // The symbol table has "/.../@with/@statements.X/@variable/@variable"
//         // But we need "/.../@with/@statements.X"
        
//         // Remove "/@variable/@variable" suffix if present
//         std::string var_suffix = "/@variable/@variable";
//         size_t pos = implementing_var_path.find(var_suffix);
//         if (pos != std::string::npos && pos + var_suffix.length() == implementing_var_path.length())
//         {
//             implementing_var_path = implementing_var_path.substr(0, pos);
//         }
//         pos = implemented_var_path.find(var_suffix);
//         if (pos != std::string::npos && pos + var_suffix.length() == implemented_var_path.length())
//         {
//             implemented_var_path = implemented_var_path.substr(0, pos);
//         }

//         writeAttribute("        implementing_var", implementing_var_path);
//         out() << "\n";
//         writeAttribute("        implemented_var", implemented_var_path);
//         out() << " />\n";
//     }
//     else
//     {
//         // Par défaut, traiter comme channel
//         std::cerr << "[WARNING] Type de variable inconnu pour having statement: " << var_type << ", traité comme channel" << std::endl;
//         writeAttribute("        xsi:type", statement_type("channel_aliasing", StatementFamily::Implementation));
//         out() << "\n";
//         writeAttribute("        implementing_channel", implementing_var_path);
//         out() << "\n";
//         writeAttribute("        implemented_channel", implemented_var_path);
//         out() << " />\n";
//     }

//     // Visiter le prochain mapping s'il existe (liste chaînée)
//     if (auto next = node.get_node())
//     {
//         next->accept(*this);
//     }
// }

// void ChipsToXmiVisitor::visit(c_signature_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_signature_node)" << std::endl;
//     out() << "    <!-- c_signature_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(output_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(output_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.outputs");
//     ensure_namespace_for_prefix("chips.rvalues.primitive");
//     ensure_namespace_for_prefix("chips.xvalues.primitive");

//     out() << "      <outputs\n";
//     writeAttribute("        xsi:type", "chips.outputs:pure_output");
//     out() << ">\n";

//     for (const auto &expr : node.get_outputs())
//     {
//         if (!expr)
//         {
//             continue;
//         }

//         if (auto num = dynamic_cast<number_literal_node *>(expr.get()))
//         {
//             std::string literal_type = "int";
//             std::string literal_value;
//             EXPRESSION_TYPE type = num->get_type();
//             if (type == FLOAT_EXP)
//             {
//                 literal_type = "float";
//                 literal_value = std::to_string(num->get_float());
//             }
//             else if (type == BOOL_EXP)
//             {
//                 literal_type = "bool";
//                 literal_value = num->get_bool() ? "true" : "false";
//             }
//             else
//             {
//                 literal_type = "int";
//                 literal_value = std::to_string(num->get_int());
//             }

//             out() << "        <expression\n";
//             writeAttribute("          xsi:type", "chips.rvalues.primitive:direct_" + literal_type);
//             if (literal_value != "0" && literal_value != "0.0" && literal_value != "false")
//             {
//                 out() << "\n";
//                 writeAttribute("          value", literal_value);
//             }
//             out() << " />\n";
//             continue;
//         }

//         std::string expr_name = getExpressionValue(*expr);
//         SymbolInfo info = get_symbol_info(expr_name);
//         std::string dataflow_type = "int";
//         if (info.type == "bool")
//         {
//             dataflow_type = "bool";
//         }
//         else if (info.type == "float")
//         {
//             dataflow_type = "float";
//         }

//         std::string variable_path = get_ast_path_by_name(expr_name);
//         out() << "        <expression\n";
//         writeAttribute("          xsi:type", "chips.xvalues.primitive:" + dataflow_type + "_variable_expression");
//         out() << "\n";
//         writeAttribute("          variable", variable_path);
//         out() << " />\n";
//     }

//     out() << "      </outputs>\n";
// }

// // === WITH / SECTIONS ===

// void ChipsToXmiVisitor::visit(with_section_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(with_section_node)" << std::endl;
//     auto statements = node.get_statements();
//     if (!statements || statements->get_statements().empty())
//     {
//         return;
//     }

//     out() << "      <with>\n";
//     std::cerr << "[DEBUG Visitor] With section a des statements" << std::endl;
//     statements->accept(*this);
//     out() << "      </with>\n";
// }

// void ChipsToXmiVisitor::visit(with_statements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(with_statements_node) - " << node.get_statements().size() << " statements" << std::endl;

//     int index = 0;
//     for (auto &st : node.get_statements())
//     {
//         if (st)
//         {
//             std::string segment = "/@statements." + std::to_string(index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             st->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(with_statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(with_statement_node)" << std::endl;
//     out() << "        <!-- with_statement_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(with_two_identifier_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(with_two_identifier_node)" << std::endl;

//     std::string type_identifier = node.get_ident1();
//     std::string name = node.get_ident2();
//     std::string type = statement_type("channel_declaration", StatementFamily::Node);

//     // Enregistrer le channel dans la table des symboles
//     // Le chemin du channel est juste get_ast_path() car on est déjà dans /@with/@statements.X
//     register_variable(name, get_ast_path(), "channel");
    
//     // Also register in the current definition if we're in one
//     if (!m_current_definition.empty()) {
//         register_definition_variable(m_current_definition, name, get_ast_path(), "channel");
//     }
    
//     std::cerr << "[DEBUG] Channel '" << name << "' enregistré avec le chemin: " << get_ast_path() << std::endl;

//     out() << "        <statements\n";
//     writeAttribute("          xsi:type", type);
//     out() << "\n";
//     writeAttribute("          name", name);
//     out() << "\n";
//     writeAttribute("          type_identifier", type_identifier);
//     out() << "/>\n";
// }

// void ChipsToXmiVisitor::visit(with_context_statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(with_context_statement_node)" << std::endl;

//     bool has_value = true;

//     std::string name = node.get_identifier();
//     std::string type_primitive = node.get_df_type()->get_type() == INT_DF ? "int" : node.get_df_type()->get_type() == FLOAT_DF ? "float"
//                                                                                 : node.get_df_type()->get_type() == BOOL_DF    ? "bool"
//                                                                                                                                : "Unknown";
//     std::string type = statement_type("contextual_" + type_primitive + "_declaration", StatementFamily::Node);

//     std::string segment = "/@variable/@variable";
//     push_ast_path(segment);
//     std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

//     // Enregistrer la variable dans la table des symboles avec le chemin complet vers la variable
//     // Ce chemin sera utilisé pour les références dans les expressions
//     // Pour les having_statements, on devra enlever le suffix "/@variable/@variable"
//     register_variable(name, get_ast_path(), "contextual");
    
//     // Also register in the current definition if we're in one
//     if (!m_current_definition.empty()) {
//         register_definition_variable(m_current_definition, name, get_ast_path(), "contextual");
//     }
    
//     std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

//     expression_node *rhs = node.get_rhs()->get_rhs();

//     std::string rhs_value = getExpressionValue(*rhs);

//     out() << "        <statements\n";
//     writeAttribute("        xsi:type", type);
//     out() << "\n";
//     writeAttribute("        identifier", name);
//     out() << ">\n          <variable>\n            <variable\n";
//     writeAttribute("name", name);
//     out() << "/>\n          </variable>\n";
//     if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false" && rhs_value != "unknown")
//     {
//         out() << "        </" << m_statement_tag << ">\n        <" << m_statement_tag << "\n";
//         writeAttribute("        xsi:type", statement_type(type_primitive + "_assignment", StatementFamily::Primitive));
//         out() << ">\n";
//         out() << "          <lvalue\n";
//         writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type_primitive + "_variable_expression");
//         out() << "\n";
//         writeAttribute("            variable", get_ast_path());
//         out() << "/>\n";
//         out() << "          <rvalue\n";
//         writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type_primitive);
//         std::cerr << "[Debug] value ?????????????? " << rhs_value << std::endl;
//         if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false")
//         {
//             out() << "\n";
//             writeAttribute("            value", rhs_value);
//         }
//         out() << "/>\n";
//     }
//     out() << "        </" << m_statement_tag << ">\n";
//     pop_ast_path(segment);
//     std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
// }

void ChipsToXmiVisitor::visit(chips::init_section& node)
{
//     std::cerr << "[DEBUG Visitor] visit(init_section_node)" << std::endl;
//     auto statements = node.get_statements();
//     if (!statements || statements->get_statements().empty())
//     {
//         return;
//     }

//     out() << "      <init>\n";
//     int index = 0;
//     for (auto &st : statements->get_statements())
//     {
//         if (st)
//         {
//             std::string segment = "/@statements." + std::to_string(index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             st->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
//     out() << "      </init>\n";
}

void ChipsToXmiVisitor::visit(chips::then_section& node)
{
//     std::cerr << "[DEBUG Visitor] visit(then_section_node)" << std::endl;
//     auto statements = node.get_statements();
//     if (!statements || statements->get_statements().empty())
//     {
//         return;
//     }

//     out() << "      <then>\n";
//     int index = 0;
//     for (auto &st : statements->get_statements())
//     {
//         if (st)
//         {
//             std::string segment = "/@statements." + std::to_string(index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             st->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
//     out() << "      </then>\n";
}

void ChipsToXmiVisitor::visit(chips::function_output_variant& node){
    std::visit([this](auto* output) {
        if(output){

        }
    }, node);
}

// void ChipsToXmiVisitor::visit(physical_named_outputs_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_named_outputs_node)" << std::endl;

//     int output_index = 0;
//     int actuator_index = 0;

//     for (auto &output : node.get_outputs())
//     {
//         if (output)
//         {
//             // Determine if this is an actuator or a regular output
//             std::string segment;
//             if (dynamic_cast<actuator_node *>(output.get()))
//             {
//                 segment = "/@actuator." + std::to_string(actuator_index++);
//             }
//             else
//             {
//                 segment = "/@output." + std::to_string(output_index++);
//             }

//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             output->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(physical_named_output_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_named_output_node)" << std::endl;
//     std::cerr << "[DEBUG Visitor] Output name: " << node.get_identifier() << std::endl;

//     // Récupérer les paramètres
//     expressions_node *params = node.get_parameters();

//     // Balise ouvrante <outputs avec attributs
//     out() << "      <outputs\n";
//     writeAttribute("          xsi:type", "chips.outputs.logical:int_output");
//     out() << "\n";
//     writeAttribute("          name", node.get_identifier());
//     out() << ">\n";

//     // Traiter les paramètres (expressions)
//     if (params)
//     {
//         const auto &param_list = params->get_expressions();
//         std::cerr << "[DEBUG Visitor] Nombre de paramètres: " << param_list.size() << std::endl;

//         for (const auto &expr : param_list)
//         {
//             if (expr)
//             {
//                 // Extraire la valeur/nom du paramètre
//                 std::string param_name = getExpressionValue(*expr);
//                 std::cerr << "[DEBUG Visitor] Paramètre: " << param_name << std::endl;

//                 // C'est probablement une variable, chercher dans la table des symboles
//                 std::string variable_path = get_ast_path_by_name(param_name);

//                 out() << "        <expression\n";
//                 writeAttribute("            xsi:type", "chips.xvalues.primitive:int_variable_expression");
//                 out() << "\n";
//                 writeAttribute("            variable", variable_path);
//                 out() << "/>\n";
//             }
//         }
//     }
//     else
//     {
//         std::cerr << "[WARNING Visitor] Aucun paramètre pour l'output" << std::endl;
//     }

//     // Balise fermante
//     out() << "      </outputs>\n";
// }

// void ChipsToXmiVisitor::visit(named_outputs_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(named_outputs_node)" << std::endl;
//     int output_index = 0;
//     for (auto &output : node.get_outputs())
//     {
//         if (output)
//         {
//             std::string segment = "/@outputs." + std::to_string(output_index++);
//             push_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//             output->accept(*this);
//             pop_ast_path(segment);
//             std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(named_output_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(named_output_node)" << std::endl;
//     std::cerr << "[DEBUG Visitor] Output name: " << node.get_identifier() << std::endl;

//     // Récupérer les paramètres
//     expressions_node *params = node.get_parameters();
    
//     // Détecter le type de l'output à partir des paramètres
//     std::string output_type = "int"; // Par défaut
//     if (params && !params->get_expressions().empty())
//     {
//         const auto &first_expr = params->get_expressions().front();
//         if (first_expr)
//         {
//             // Vérifier si c'est une variable
//             std::string param_name = getExpressionValue(*first_expr);
//             SymbolInfo var_info = get_symbol_info(param_name);
            
//             // Extraire le type du symbole (ex: "primitive_variable:int" -> "int")
//             if (!var_info.type.empty())
//             {
//                 size_t colon_pos = var_info.type.find(':');
//                 if (colon_pos != std::string::npos)
//                 {
//                     output_type = var_info.type.substr(colon_pos + 1);
//                 }
//             }
//             // Si c'est un littéral numérique
//             else if (auto num = dynamic_cast<number_literal_node *>(first_expr.get()))
//             {
//                 EXPRESSION_TYPE type = num->get_type();
//                 if (type == INT_EXP)
//                     output_type = "int";
//                 else if (type == FLOAT_EXP)
//                     output_type = "float";
//                 else if (type == BOOL_EXP)
//                     output_type = "bool";
//             }
//         }
//     }

//     // Enregistrer l'output avec son type
//     register_variable(node.get_identifier(), get_ast_path(), "logical_output:" + output_type);
//     std::cerr << "[DEBUG] Output '" << node.get_identifier() << "' enregistré avec le chemin: " << get_ast_path() << " et type: " << output_type << std::endl;

//     // Balise ouvrante <outputs avec attributs
//     out() << "      <outputs\n";
//     writeAttribute("          xsi:type", "chips.outputs.logical:" + output_type + "_output");
//     out() << "\n";
//     writeAttribute("          name", node.get_identifier());
//     out() << ">\n";

//     // Traiter les paramètres (expressions)
//     if (params)
//     {
//         const auto &param_list = params->get_expressions();
//         std::cerr << "[DEBUG Visitor] Nombre de paramètres: " << param_list.size() << std::endl;

//         for (const auto &expr : param_list)
//         {
//             if (expr)
//             {
//                 // Extraire la valeur/nom du paramètre
//                 std::string param_name = getExpressionValue(*expr);
//                 std::cerr << "[DEBUG Visitor] Paramètre: " << param_name << std::endl;

//                 // C'est probablement une variable, chercher dans la table des symboles
//                 std::string variable_path = get_ast_path_by_name(param_name);

//                 out() << "        <expression\n";
//                 writeAttribute("            xsi:type", "chips.xvalues.primitive:" + output_type + "_variable_expression");
//                 out() << "\n";
//                 writeAttribute("            variable", variable_path);
//                 out() << "/>\n";
//             }
//         }
//     }
//     else
//     {
//         std::cerr << "[WARNING Visitor] Aucun paramètre pour l'output" << std::endl;
//     }

//     // Balise fermante
//     out() << "      </outputs>\n";
// }

// void ChipsToXmiVisitor::visit(actuator_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(actuator_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.outputs.physical");

//     expressions_node *params = node.get_parameters();
//     std::string output_type = "bool";

//     if (params && !params->get_expressions().empty())
//     {
//         const auto &first_expr = params->get_expressions().front();
//         if (first_expr)
//         {
//             if (auto num = dynamic_cast<number_literal_node *>(first_expr.get()))
//             {
//                 EXPRESSION_TYPE type = num->get_type();
//                 if (type == INT_EXP)
//                 {
//                     output_type = "int";
//                 }
//                 else if (type == FLOAT_EXP)
//                 {
//                     output_type = "float";
//                 }
//                 else if (type == BOOL_EXP)
//                 {
//                     output_type = "bool";
//                 }
//             }
//         }
//     }

//     // Register actuator in symbol table with type information
//     std::string actuator_name = node.get_identifier();
//     std::string actuator_path = get_ast_path();
//     register_variable(actuator_name, actuator_path, "actuator:" + output_type);
//     std::cerr << "[DEBUG] Actuator '" << actuator_name << "' registered with type 'actuator:" << output_type << "' at path: " << actuator_path << std::endl;

//     out() << "      <actuator\n";
//     writeAttribute("          xsi:type", "chips.outputs.physical:" + output_type + "_output");
//     out() << "\n";
//     writeAttribute("          name", node.get_identifier());
//     out() << ">\n";

//     if (params)
//     {
//         const auto &param_list = params->get_expressions();
//         for (const auto &expr : param_list)
//         {
//             if (!expr)
//             {
//                 continue;
//             }

//             if (auto num = dynamic_cast<number_literal_node *>(expr.get()))
//             {
//                 std::string literal_type = "bool";
//                 std::string literal_value;
//                 EXPRESSION_TYPE type = num->get_type();
//                 if (type == INT_EXP)
//                 {
//                     literal_type = "int";
//                     literal_value = std::to_string(num->get_int());
//                 }
//                 else if (type == FLOAT_EXP)
//                 {
//                     literal_type = "float";
//                     literal_value = std::to_string(num->get_float());
//                 }
//                 else if (type == BOOL_EXP)
//                 {
//                     literal_type = "bool";
//                     literal_value = num->get_bool() ? "true" : "false";
//                 }

//                 out() << "        <expression\n";
//                 writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + literal_type);
//                 out() << "\n";
//                 writeAttribute("            value", literal_value);
//                 out() << "/>\n";
//             }
//             else
//             {
//                 std::string param_name = getExpressionValue(*expr);
//                 std::string variable_path = get_ast_path_by_name(param_name);

//                 out() << "        <expression\n";
//                 writeAttribute("            xsi:type", "chips.xvalues.primitive:" + output_type + "_variable_expression");
//                 out() << "\n";
//                 writeAttribute("            variable", variable_path);
//                 out() << "/>\n";
//             }
//         }
//     }
//     else
//     {
//         std::cerr << "[WARNING Visitor] Aucun parametre pour l'actuator" << std::endl;
//     }

//     out() << "      </actuator>\n";
// }

// void ChipsToXmiVisitor::visit(statements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(statements_node)" << std::endl;
//     out() << "      <!-- statements_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(rhs_assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(rhs_assignment_node)" << std::endl;
//     out() << "      <!-- rhs_assignment_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(assignment_node)" << std::endl;
//     out() << "      <!-- assignment_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(this_attribute_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(this_attribute_node)" << std::endl;
//     out() << "      <!-- this_attribute_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(function_call_statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(function_call_statement_node)" << std::endl;
//     out() << "      <!-- function_call_statement_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(if_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(if_node)" << std::endl;
//     out() << "      <!-- if_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(if_else_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(if_else_node)" << std::endl;

//     out() << "        <statements\n";
//     writeAttribute("            xsi:type", statement_type("if_else", StatementFamily::Primitive));
//     out() << ">\n";

//     // Condition
//     if (auto if_part = node.get_if_node())
//     {
//         if (auto cond = if_part->get_condition())
//         {
//             std::cerr << "[DEBUG Visitor] if_else: traitement de la condition" << std::endl;
//             std::string cond_var_name = getExpressionValue(*cond);
//             std::string cond_var_path = get_ast_path_by_name(cond_var_name);

//             out() << "          <condition\n";
//             writeAttribute("              xsi:type", "chips.xvalues.primitive:bool_variable_expression");
//             out() << "\n";
//             writeAttribute("              variable", cond_var_path);
//             out() << "/>\n";
//         }

//         // Section if
//         out() << "          <if_section>\n";
//         if (auto if_stmts = if_part->get_statements())
//         {
//             std::cerr << "[DEBUG Visitor] if_else: traitement if_section" << std::endl;
//             // Changer le tag pour if_statements
//             std::string old_tag = m_statement_tag;
//             m_statement_tag = "if_statements";

//             int index = 0;
//             for (auto &st : if_stmts->get_statements())
//             {
//                 if (st)
//                 {
//                     std::string segment = "/@if_statements." + std::to_string(index++);
//                     push_ast_path(segment);
//                     st->accept(*this);
//                     pop_ast_path(segment);
//                 }
//             }

//             // Restaurer le tag
//             m_statement_tag = old_tag;
//         }
//         out() << "          </if_section>\n";
//     }

//     // Section else
//     out() << "          <else_section>\n";
//     if (auto else_stmts = node.get_else_node())
//     {
//         std::cerr << "[DEBUG Visitor] if_else: traitement else_section" << std::endl;
//         // Changer le tag pour else_statements
//         std::string old_tag = m_statement_tag;
//         m_statement_tag = "else_statements";

//         int index = 0;
//         for (auto &st : else_stmts->get_statements())
//         {
//             if (st)
//             {
//                 std::string segment = "/@else_statements." + std::to_string(index++);
//                 push_ast_path(segment);
//                 st->accept(*this);
//                 pop_ast_path(segment);
//             }
//         }

//         // Restaurer le tag
//         m_statement_tag = old_tag;
//     }
//     out() << "          </else_section>\n";

//     out() << "        </statements>\n";
// }

// void ChipsToXmiVisitor::visit(loop_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(loop_node)" << std::endl;
//     out() << "      <!-- loop_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(block_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(block_node)" << std::endl;
//     out() << "      <!-- block_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(statement_node) - classe abstraite" << std::endl;
//     // Dispatch vers les sous-classes concrètes
//     if (auto df = dynamic_cast<dataflow_full_declaration_node *>(&node))
//     {
//         std::cerr << "--> [Dispatch] dataflow_full_declaration_node détecté" << std::endl;
//         df->accept(*this);
//     }
//     else if (auto var_assign = dynamic_cast<variable_assignment_node *>(&node))
//     {
//         std::cerr << "--> [Dispatch] variable_assignment_node détecté" << std::endl;
//         var_assign->accept(*this);
//     }
//     else if (auto ctx_assign = dynamic_cast<context_variable_assignment_node *>(&node))
//     {
//         std::cerr << "--> [Dispatch] context_variable_assignment_node détecté" << std::endl;
//         ctx_assign->accept(*this);
//     }
//     else
//     {
//         out() << "    <!-- statement_node type inconnu -->\n";
//     }
// }

// void ChipsToXmiVisitor::visit(dataflow_full_declaration_node &node) {

//     semanticAnalyzer.analyze(node);

//     std::cerr << "[DEBUG Visitor] visit(dataflow_full_declaration_node) name=" 
//               << node.get_identifier() << std::endl;
    
//     std::string type = node.get_privitve_type();
//     std::string name = node.get_identifier();
//     bool is_system_context = (m_statement_tag == "system");
//     std::string xvalue_prefix = is_system_context ? "chips.xvalues.system" : "chips.xvalues.primitive";
//     std::string rvalue_prefix = is_system_context ? "chips.rvalues.system" : "chips.rvalues.primitive";

//     out() << "        <" << m_statement_tag << "\n";
//     writeAttribute("xsi:type", statement_type(type + "_declaration"));
//     out() << ">\n";

//     std::string segment = "/@variable";
//     push_ast_path(segment);
//     std::string declared_var_path = get_ast_path();  // Sauvegarder le chemin de la variable déclarée
//     register_variable(name, declared_var_path, type);
//     std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << declared_var_path << std::endl;

//     out() << "          <variable\n";
//     writeAttribute("            name", name);

//     suffixes_node *suffixes = nullptr;
//     if (auto df_type = node.get_df_type())
//     {
//         suffixes = df_type->get_suffixes();
//     }

//     if (suffixes && !suffixes->get_suffixes().empty())
//     {
//         out() << ">\n";
//         out() << "            <dimensions\n";
//         for (auto &suffix_expr : suffixes->get_suffixes())
//         {
//             if (suffix_expr)
//             {
//                 suffix_expr->accept(*this);
//             }
//         }
//         out() << "            />\n";
//         out() << "          </variable>\n";
//     }
//     else
//     {
//         out() << "/>\n";
//     }

//     out() << "        </" << m_statement_tag << ">\n";
    
//     pop_ast_path(segment);

//     // Traiter l'assignation si elle existe (même pour 0/false)
//     if (auto rhs = node.get_rhs())
//     {
//         if (auto rhs_expr = rhs->get_rhs())
//         {
//             std::cerr << "[DEBUG] dataflow_full_declaration_node: Assignment détecté pour variable '" << name << "'" << std::endl;
//             // Signaler qu'un statement supplémentaire va être généré
//             m_extra_statements_generated++;
//             std::cerr << "[DEBUG] m_extra_statements_generated incrémenté à: " << m_extra_statements_generated << std::endl;
            
//             // Récupérer le chemin de base et construire le nouveau segment
//             std::string current_path = m_current_ast_path;
//             size_t last_slash = current_path.rfind('/');
//             if (last_slash != std::string::npos) {
//                 std::string last_segment = current_path.substr(last_slash);
//                 // Extraire le numéro du segment actuel
//                 size_t dot_pos = last_segment.rfind('.');
//                 if (dot_pos != std::string::npos) {
//                     int current_index = std::stoi(last_segment.substr(dot_pos + 1));
//                     std::string base_path = current_path.substr(0, last_slash);
//                     std::string next_segment = "/@statements." + std::to_string(current_index + 1);
                    
//                     // Temporairement changer le chemin pour l'assignment
//                     std::string saved_path = m_current_ast_path;
//                     set_ast_path(base_path + next_segment);
                    
//                     std::string rhs_value = getExpressionValue(*rhs_expr);
//                     out() << "        <" << m_statement_tag << "\n";
//                     writeAttribute("        xsi:type", statement_type(type + "_assignment"));
//                     out() << ">\n";
//                     out() << "          <lvalue\n";
//                     writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//                     out() << "\n";
//                     writeAttribute("            variable", declared_var_path);  // Utiliser le chemin sauvegardé
//                     out() << "/>\n";
//                     bool is_var_rvalue = dynamic_cast<variable_node *>(rhs_expr) || dynamic_cast<suffixised_node *>(rhs_expr);
//                     if (is_var_rvalue)
//                     {
//                         std::string var_name = getExpressionValue(*rhs_expr);
//                         std::string var_path_rhs = get_ast_path_by_name(var_name);

//                         out() << "          <rvalue\n";
//                         writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//                         out() << "\n";
//                         writeAttribute("            variable", var_path_rhs);
//                         out() << "/>\n";
//                     }
//                     else
//                     {
//                         out() << "          <rvalue\n";
//                         writeAttribute("            xsi:type", rvalue_prefix + ":direct_" + type);
//                         std::cerr << "[Debug] value ?????????????? " << rhs_value << std::endl;
//                         if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false")
//                         {
//                             out() << "\n";
//                             writeAttribute("            value", rhs_value);
//                         }
//                         out() << "/>\n";
//                     }
//                     out() << "        </" << m_statement_tag << ">\n";
                    
//                     // Restaurer le chemin
//                     set_ast_path(saved_path);
//                 }
//             }
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(variable_assignment_node &node) {

//     semanticAnalyzer.analyze(node);

//     std::cerr << "[DEBUG Visitor] visit(variable_assignment_node) identifier=" 
//               << node.get_identifier() << std::endl;
    
//     std::string name = node.get_identifier();
//     std::string path = get_ast_path_by_name(name);
//     std::cerr << "[DEBUG] Variable path: " << path << std::endl;
//     bool is_system_context = (m_statement_tag == "system");
//     std::string xvalue_prefix = is_system_context ? "chips.xvalues.system" : "chips.xvalues.primitive";
//     std::string rvalue_prefix = is_system_context ? "chips.rvalues.system" : "chips.rvalues.primitive";
//     std::string op_prefix = is_system_context ? "chips.rvalues.dataflow.operators.int" : "chips.rvalues.primitive.operators.int";

//     if (auto expr = node.get_expression())
//     {
//         std::cerr << "[DEBUG] Expression trouvée" << std::endl;

//         // Vérifier le type d'expression
//         if (auto bin_expr = dynamic_cast<binary_expression_node *>(expr))
//         {
//             std::cerr << "[DEBUG] --> Expression binaire détectée!" << std::endl;
//         }
//         else if (auto num = dynamic_cast<number_literal_node *>(expr))
//         {
//             std::cerr << "[DEBUG] --> Number literal détecté: " << num->get_int() << std::endl;
//         }
//         else if (auto var = dynamic_cast<variable_node *>(expr))
//         {
//             std::cerr << "[DEBUG] --> Variable node détecté" << std::endl;
//         }
//         else if (auto suf = dynamic_cast<suffixised_node *>(expr))
//         {
//             std::cerr << "[DEBUG] --> Suffixised node détecté: " << suf->get_identifier() << std::endl;
//         }
//         else
//         {
//             std::cerr << "[DEBUG] --> Type d'expression inconnu" << std::endl;
//         }

//         std::string value = getExpressionValue(*expr);
//         std::cerr << "[DEBUG] Assignment value: " << value << std::endl;

//         // Déterminer le type de l'expression
//         std::string type = "int"; // Default
//         if (auto num = dynamic_cast<number_literal_node *>(expr))
//         {
//             type = num->get_type() == FLOAT_EXP ? "float" : num->get_type() == BOOL_EXP ? "bool"
//                                                                                         : "int";
//         }

//         out() << "        <" << m_statement_tag << "\n";
//         writeAttribute("        xsi:type", statement_type(type + "_assignment"));
//         out() << ">\n";
//         out() << "          <lvalue\n";
//         writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//         out() << "\n";
//         writeAttribute("            variable", path);

//         suffixes_node *lvalue_suffixes = node.get_suffixes();
//         if (lvalue_suffixes && !lvalue_suffixes->get_suffixes().empty())
//         {
//             out() << ">\n";
//             write_index_from_suffixes(lvalue_suffixes, "            ", xvalue_prefix, rvalue_prefix, false);
//             out() << "          </lvalue>\n";
//         }
//         else
//         {
//             out() << " />\n";
//         }

//         // Traiter la rvalue
//         if (auto bin_expr = dynamic_cast<binary_expression_node *>(expr))
//         {
//             std::cerr << "[DEBUG] Génération de la rvalue binaire" << std::endl;
//             EXPRESSION_TYPE op_type = bin_expr->get_type();

//             std::string op_name;
//             switch (op_type)
//             {
//             case PLUS_EXP:
//                 op_name = "plus";
//                 std::cerr << "[DEBUG] Opérateur: addition (+)" << std::endl;
//                 break;
//             case MINUS_EXP:
//                 op_name = "minus";
//                 std::cerr << "[DEBUG] Opérateur: soustraction (-)" << std::endl;
//                 break;
//             case TIMES_EXP:
//                 op_name = "times";
//                 std::cerr << "[DEBUG] Opérateur: multiplication (*)" << std::endl;
//                 break;
//             case DIV_EXP:
//                 op_name = "divide";
//                 std::cerr << "[DEBUG] Opérateur: division (/)" << std::endl;
//                 break;
//             case MOD_EXP:
//                 op_name = "modulo";
//                 std::cerr << "[DEBUG] Opérateur: modulo (%)" << std::endl;
//                 break;
//             default:
//                 op_name = "plus"; // Default
//                 std::cerr << "[DEBUG] Opérateur: inconnu, utilisant plus par défaut" << std::endl;
//             }

//             out() << "          <rvalue\n";
//             writeAttribute("            xsi:type", op_prefix + ":" + op_name);
//             out() << ">\n";

//             // Opérande gauche
//             if (auto left = bin_expr->get_lhs())
//             {
//                 std::cerr << "[DEBUG] Traitement de l'opérande gauche" << std::endl;

//                 // Vérifier si c'est un littéral ou une variable
//                 if (auto num_lit = dynamic_cast<number_literal_node *>(left))
//                 {
//                     // C'est un littéral numérique
//                     std::string lit_type = "int";
//                     std::string lit_value;

//                     EXPRESSION_TYPE exp_type = num_lit->get_type();
//                     if (exp_type == INT_EXP)
//                     {
//                         lit_type = "int";
//                         lit_value = std::to_string(num_lit->get_int());
//                     }
//                     else if (exp_type == FLOAT_EXP)
//                     {
//                         lit_type = "float";
//                         lit_value = std::to_string(num_lit->get_float());
//                     }
//                     else if (exp_type == BOOL_EXP)
//                     {
//                         lit_type = "bool";
//                         lit_value = num_lit->get_bool() ? "true" : "false";
//                     }

//                     std::cerr << "[DEBUG] Opérande gauche: littéral " << lit_type << " = " << lit_value << std::endl;

//                     out() << "            <left_operand\n";
//                     writeAttribute("              xsi:type", rvalue_prefix + ":direct_" + lit_type);
//                     if (lit_value != "0" && lit_value != "0.0" && lit_value != "false")
//                     {
//                         out() << "\n";
//                         writeAttribute("              value", lit_value);
//                     }
//                     out() << "/>\n";
//                 }
//                 else
//                 {
//                     // C'est une variable
//                     std::string left_value = getExpressionValue(*left);
//                     std::cerr << "[DEBUG] Opérande gauche: variable = " << left_value << std::endl;

//                     out() << "            <left_operand\n";
//                     writeAttribute("              xsi:type", xvalue_prefix + ":int_variable_expression");
//                     out() << "\n";
//                     // Chercher le chemin si c'est une variable
//                     std::string left_path = get_ast_path_by_name(left_value);
//                     writeAttribute("              variable", left_path);
//                     out() << "/>\n";
//                 }
//             }

//             // Opérande droite
//             if (auto right = bin_expr->get_rhs())
//             {
//                 std::cerr << "[DEBUG] Traitement de l'opérande droite" << std::endl;

//                 // Vérifier si c'est un littéral ou une variable
//                 if (auto num_lit = dynamic_cast<number_literal_node *>(right))
//                 {
//                     // C'est un littéral numérique
//                     std::string lit_type = "int";
//                     std::string lit_value;

//                     EXPRESSION_TYPE exp_type = num_lit->get_type();
//                     if (exp_type == INT_EXP)
//                     {
//                         lit_type = "int";
//                         lit_value = std::to_string(num_lit->get_int());
//                     }
//                     else if (exp_type == FLOAT_EXP)
//                     {
//                         lit_type = "float";
//                         lit_value = std::to_string(num_lit->get_float());
//                     }
//                     else if (exp_type == BOOL_EXP)
//                     {
//                         lit_type = "bool";
//                         lit_value = num_lit->get_bool() ? "true" : "false";
//                     }

//                     std::cerr << "[DEBUG] Opérande droite: littéral " << lit_type << " = " << lit_value << std::endl;

//                     out() << "            <right_operand\n";
//                     writeAttribute("              xsi:type", rvalue_prefix + ":direct_" + lit_type);
//                     if (lit_value != "0" && lit_value != "0.0" && lit_value != "false")
//                     {
//                         out() << "\n";
//                         writeAttribute("              value", lit_value);
//                     }
//                     out() << "/>\n";
//                 }
//                 else
//                 {
//                     // C'est une variable
//                     std::string right_value = getExpressionValue(*right);
//                     std::cerr << "[DEBUG] Opérande droite: variable = " << right_value << std::endl;

//                     out() << "            <right_operand\n";
//                     writeAttribute("              xsi:type", xvalue_prefix + ":int_variable_expression");
//                     out() << "\n";
//                     // Chercher le chemin si c'est une variable
//                     std::string right_path = get_ast_path_by_name(right_value);
//                     writeAttribute("              variable", right_path);
//                     out() << "/>\n";
//                 }
//             }

//             out() << "          </rvalue>\n";
//         }
//         else
//         {
//             bool is_var_rvalue = dynamic_cast<variable_node *>(expr) || dynamic_cast<suffixised_node *>(expr);
//             if (is_var_rvalue)
//             {
//                 std::string var_name = getExpressionValue(*expr);
//                 std::string var_path = get_ast_path_by_name(var_name);
//                 suffixes_node *rvalue_suffixes = nullptr;
//                 if (auto suf = dynamic_cast<suffixised_node *>(expr))
//                 {
//                     rvalue_suffixes = suf->get_suffixes();
//                 }

//                 out() << "          <rvalue\n";
//                 writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//                 out() << "\n";
//                 writeAttribute("            variable", var_path);

//                 if (rvalue_suffixes && !rvalue_suffixes->get_suffixes().empty())
//                 {
//                     out() << ">\n";
//                     write_index_from_suffixes(rvalue_suffixes, "            ", xvalue_prefix, rvalue_prefix, false);
//                     out() << "          </rvalue>\n";
//                 }
//                 else
//                 {
//                     out() << " />\n";
//                 }
//             }
//             else
//             {
//                 // Rvalue simple (literal)
//                 out() << "          <rvalue\n";
//                 writeAttribute("            xsi:type", rvalue_prefix + ":direct_" + type);
//                 std::cerr << "[Debug] value: " << value << std::endl;
//                 if (value != "0" && value != "0.0" && value != "false")
//                 {
//                     out() << "\n";
//                     writeAttribute("            value", value);
//                 }
//                 out() << "/>\n";
//             }
//         }

//         out() << "        </" << m_statement_tag << ">\n";
//     }
// }

// void ChipsToXmiVisitor::visit(context_variable_assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(context_variable_assignment_node) identifier=" << node.get_identifier() << std::endl;

//     std::string name = node.get_identifier();
//     std::string path = get_ast_path_by_name(name);
//     bool is_system_context = (m_statement_tag == "system");
//     std::string xvalue_prefix = is_system_context ? "chips.xvalues.system" : "chips.xvalues.primitive";
//     std::string rvalue_prefix = is_system_context ? "chips.rvalues.system" : "chips.rvalues.primitive";

//     if (auto expr = node.get_expression())
//     {
//         std::string value = getExpressionValue(*expr);
//         std::cerr << "[DEBUG] Context assignment value: " << value << std::endl;

//         std::string type = "int"; // Default
//         if (auto num = dynamic_cast<number_literal_node *>(expr))
//         {
//             type = num->get_type() == FLOAT_EXP ? "float" : num->get_type() == BOOL_EXP ? "bool"
//                                                                                         : "int";
//         }

//         out() << "        <" << m_statement_tag << "\n";
//         writeAttribute("        xsi:type", statement_type(type + "_assignment"));
//         out() << ">\n";
//         out() << "          <lvalue\n";
//         writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//         out() << "\n";
//         writeAttribute("            variable", path);

//         suffixes_node *lvalue_suffixes = node.get_suffixes();
//         if (lvalue_suffixes && !lvalue_suffixes->get_suffixes().empty())
//         {
//             out() << ">\n";
//             write_index_from_suffixes(lvalue_suffixes, "            ", xvalue_prefix, rvalue_prefix, false);
//             out() << "          </lvalue>\n";
//         }
//         else
//         {
//             out() << " />\n";
//         }
//         bool is_var_rvalue = dynamic_cast<variable_node *>(expr) || dynamic_cast<suffixised_node *>(expr);
//         if (is_var_rvalue)
//         {
//             std::string var_name = getExpressionValue(*expr);
//             std::string var_path = get_ast_path_by_name(var_name);
//             suffixes_node *rvalue_suffixes = nullptr;
//             if (auto suf = dynamic_cast<suffixised_node *>(expr))
//             {
//                 rvalue_suffixes = suf->get_suffixes();
//             }

//             out() << "          <rvalue\n";
//             writeAttribute("            xsi:type", xvalue_prefix + ":" + type + "_variable_expression");
//             out() << "\n";
//             writeAttribute("            variable", var_path);

//             if (rvalue_suffixes && !rvalue_suffixes->get_suffixes().empty())
//             {
//                 out() << ">\n";
//                 write_index_from_suffixes(rvalue_suffixes, "            ", xvalue_prefix, rvalue_prefix, false);
//                 out() << "          </rvalue>\n";
//             }
//             else
//             {
//                 out() << " />\n";
//             }
//         }
//         else
//         {
//             out() << "          <rvalue\n";
//             writeAttribute("            xsi:type", rvalue_prefix + ":direct_" + type);
//             std::cerr << "[Debug] value ?????????????? " << value << std::endl;
//             if (value != "0" && value != "0.0" && value != "false")
//             {
//                 out() << "\n";
//                 writeAttribute("            value", value);
//             }
//             out() << "/>\n";
//         }
//         out() << "        </" << m_statement_tag << ">\n";
//     }
// }

// // === EXPRESSIONS ===

// void ChipsToXmiVisitor::visit(expression_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(expression_node)" << std::endl;
//     out() << "    <!-- expression_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(suffixable_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(suffixable_node)" << std::endl;
//     out() << "    <!-- suffixable_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(binary_expression_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(binary_expression_node)" << std::endl;

//     auto operand_type = [&](expression_node *expr) -> std::string
//     {
//         if (!expr)
//         {
//             return "int";
//         }
//         if (auto num = dynamic_cast<number_literal_node *>(expr))
//         {
//             EXPRESSION_TYPE type = num->get_type();
//             if (type == FLOAT_EXP)
//                 return "float";
//             if (type == BOOL_EXP)
//                 return "bool";
//             return "int";
//         }
//         if (dynamic_cast<variable_node *>(expr) || dynamic_cast<suffixised_node *>(expr))
//         {
//             std::string name = getExpressionValue(*expr);
//             SymbolInfo info = get_symbol_info(name);
//             std::string t = info.type;
//             size_t pos = t.find(':');
//             if (pos != std::string::npos)
//             {
//                 t = t.substr(pos + 1);
//             }
//             if (t == "float" || t == "bool" || t == "int")
//             {
//                 return t;
//             }
//         }
//         return "int";
//     };

//     auto write_operand = [&](const std::string &tag, expression_node *expr, const std::string &type)
//     {
//         out() << "        <" << tag << "\n";
//         if (dynamic_cast<variable_node *>(expr) || dynamic_cast<suffixised_node *>(expr))
//         {
//             writeAttribute("          xsi:type", "chips.xvalues.system:" + type + "_variable_expression");
//             out() << "\n";
//             writeAttribute("          variable", get_ast_path_by_name(getExpressionValue(*expr)));
//             out() << " />\n";
//             return;
//         }
//         if (auto num = dynamic_cast<number_literal_node *>(expr))
//         {
//             std::string literal_type = (num->get_type() == FLOAT_EXP) ? "float" : (num->get_type() == BOOL_EXP) ? "bool" : "int";
//             writeAttribute("          xsi:type", "chips.rvalues.system:direct_" + literal_type);
//             std::string value = getExpressionValue(*expr);
//             if (!value.empty() && value != "0" && value != "0.0" && value != "false")
//             {
//                 out() << "\n";
//                 writeAttribute("          value", value);
//             }
//             out() << " />\n";
//             return;
//         }
//         writeAttribute("          xsi:type", "chips.rvalues.system:direct_" + type);
//         out() << " />\n";
//     };

//     EXPRESSION_TYPE op_type = node.get_type();
//     std::string left_type = operand_type(node.get_lhs());
//     std::string right_type = operand_type(node.get_rhs());
//     std::string result_type = (left_type == "float" || right_type == "float") ? "float" : (left_type == "bool" || right_type == "bool") ? "bool"
//                                                                                                                                         : "int";

//     std::string op_prefix;
//     std::string op_name;

//     switch (op_type)
//     {
//     case GT_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "float") ? "gt_float" : "gt_int";
//         break;
//     case LT_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "float") ? "lt_float" : "lt_int";
//         break;
//     case GEQ_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "float") ? "geq_float" : "geq_int";
//         break;
//     case LEQ_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "float") ? "leq_float" : "leq_int";
//         break;
//     case EQ_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "bool") ? "eq_bool" : (result_type == "float") ? "eq_float"
//                                                                               : "eq_int";
//         break;
//     case NEQ_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = (result_type == "bool") ? "neq_bool" : (result_type == "float") ? "neq_float"
//                                                                                : "neq_int";
//         break;
//     case PLUS_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.int";
//         op_name = "plus";
//         break;
//     case MINUS_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.int";
//         op_name = "minus";
//         break;
//     case TIMES_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.int";
//         op_name = "times";
//         break;
//     case DIV_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.int";
//         op_name = "divide";
//         break;
//     case MOD_EXP:
//         op_prefix = "chips.rvalues.dataflow.operators.int";
//         op_name = "modulo";
//         break;
//     default:
//         op_prefix = "chips.rvalues.dataflow.operators.bool";
//         op_name = "gt_int";
//         break;
//     }

//     writeAttribute("xsi:type", op_prefix + ":" + op_name);
//     out() << ">\n";
//     write_operand("left_operand", node.get_lhs(), result_type == "bool" ? "int" : result_type);
//     write_operand("right_operand", node.get_rhs(), result_type == "bool" ? "int" : result_type);
// }

// void ChipsToXmiVisitor::visit(unary_expression_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(unary_expression_node)" << std::endl;
//     out() << "    <!-- unary_expression_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(number_literal_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(number_literal_node)" << std::endl;
//     out() << "    <!-- number_literal_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(function_call_node &node)
// {
//     // DOESN'T IN GRAMMAR
//     std::cerr << "[DEBUG Visitor] visit(function_call_node)" << std::endl;
//     out() << "    <!-- function_call_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(variable_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(variable_node)" << std::endl;
    
//     std::string identifier = node.get_identifier();
//     std::cerr << "[DEBUG Visitor] variable_node identifier: " << identifier << std::endl;

//     SymbolInfo info = get_symbol_info(identifier); // Affiche les informations de symboles pour le variable_node

//     std::string declaration_path = get_ast_path_by_name(identifier);
//     std::cerr << "[DEBUG Visitor] variable_node declaration path: " << declaration_path << std::endl;

//     writeAttribute("xsi:type", "chips.xvalues.system:" + info.type + "_variable_expression");
//     out() << "\n";
//     writeAttribute("variable", declaration_path);
// }

// void ChipsToXmiVisitor::visit(plugging_expr_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(plugging_expr_node)" << std::endl;
//     out() << "    <!-- plugging_expr_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(collective_cast_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_cast_node)" << std::endl;
//     out() << "    <!-- collective_cast_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(collective_operation_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_operation_node)" << std::endl;
//     out() << "    <!-- collective_operation_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(object_virtual_output_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(object_virtual_output_node)" << std::endl;
//     out() << "    <!-- object_virtual_output_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(object_physical_attribute_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(object_physical_attribute_node)" << std::endl;
//     out() << "    <!-- object_physical_attribute_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(cast_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(cast_node)" << std::endl;
//     out() << "    <!-- cast_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(stop_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(stop_node)" << std::endl;
//     out() << "    <!-- stop_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(input_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(input_node)" << std::endl;
//     out() << "    <!-- input_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_cast_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_cast_node)" << std::endl;
//     out() << "    <!-- c_cast_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(context_expression_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(context_expression_node)" << std::endl;
//     out() << "    <!-- context_expression_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(integrated_function_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(integrated_function_node)" << std::endl;
//     out() << "    <!-- integrated_function_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(context_decl_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(context_decl_node)" << std::endl;
//     out() << "    <!-- context_decl_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(suffixes_node &node)
// {

//     semanticAnalyzer.analyze(node);

//     std::cerr << "[DEBUG Visitor] visit(suffixes_node)" << std::endl;
//     out() << "    <!-- suffixes_node TODO -->\n";
// }

// void ChipsToXmiVisitor::visit(suffixised_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(suffixised_node)" << std::endl;
    
//     std::string identifier = node.get_identifier();
//     std::cerr << "[DEBUG Visitor] suffixised_node identifier: " << identifier << std::endl;

//     get_symbol_info(identifier); // Affiche les informations de symboles pour le suffixised_node

//     std::string declaration_path = get_ast_path_by_name(identifier);
//     std::cerr << "[DEBUG Visitor] suffixised_node declaration path: " << declaration_path << std::endl;

//     writeAttribute("xsi:type", "chips.xvalues.system:" + get_symbol_info(identifier).type + "_variable_expression");
//     out() << "\n";
//     writeAttribute("variable", declaration_path);
// }

// void ChipsToXmiVisitor::visit(paren_expression_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(paren_expression_node)" << std::endl;
//     out() << "    <!-- paren_expression_node TODO -->\n";
// }

// // === COLLECTIVE / CONFIGURATION HELPERS ===

// void ChipsToXmiVisitor::visit(c_keywords_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_keywords_node)" << std::endl;
//     out() << "    <!-- c_keywords_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(spread_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(spread_node)" << std::endl;
//     out() << "    <!-- spread_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(collect_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collect_node)" << std::endl;
//     out() << "    <!-- collect_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_statements_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_statements_node)" << std::endl;
//     out() << "    <!-- c_statements_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_statement_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_statement_node)" << std::endl;
//     out() << "    <!-- c_statement_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_loop_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_loop_node)" << std::endl;
//     out() << "    <!-- c_loop_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_if_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_if_node)" << std::endl;
//     out() << "    <!-- c_if_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_if_else_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_if_else_node)" << std::endl;

//     out() << "        <statements\n";
//     writeAttribute("          xsi:type", statement_type("if_else", StatementFamily::Collective));
//     out() << ">\n";

//     // Condition
//     if (auto if_node = node.get_if_node())
//     {
//         if (auto cond = if_node->get_condition())
//         {
//             std::string cond_val = getExpressionValue(*cond);

//             out() << "          <condition\n";

//             // Check if it's a binary expression
//             if (auto bin_expr = dynamic_cast<binary_expression_node *>(cond))
//             {
//                 EXPRESSION_TYPE op_type = bin_expr->get_type();
//                 std::string op_name;

//                 // Map EXPRESSION_TYPE to operator name
//                 switch (op_type)
//                 {
//                 case GT_EXP:
//                     op_name = "chips.rvalues.collective.operators.bool:gt_int";
//                     break;
//                 case LT_EXP:
//                     op_name = "chips.rvalues.collective.operators.bool:lt_int";
//                     break;
//                 case EQ_EXP:
//                     op_name = "chips.rvalues.collective.operators.bool:eq_int";
//                     break;
//                 default:
//                     op_name = "chips.rvalues.collective.operators.bool:gt_int"; // Default
//                 }

//                 writeAttribute("            xsi:type", op_name);
//                 out() << ">\n";

//                 // Left operand
//                 if (auto left = bin_expr->get_lhs())
//                 {
//                     out() << "            <left_operand\n";
//                     std::string left_val = getExpressionValue(*left);
//                     if (dynamic_cast<variable_node *>(left) || dynamic_cast<suffixised_node *>(left))
//                     {
//                         writeAttribute("              xsi:type", "chips.xvalues.collective:int_variable_expression");
//                         out() << "\n";
//                         writeAttribute("              variable", get_ast_path_by_name(left_val));
//                     }
//                     else
//                     {
//                         writeAttribute("              xsi:type", "chips.rvalues.collective:direct_int");
//                         if (!left_val.empty())
//                         {
//                             out() << "\n";
//                             writeAttribute("              value", left_val);
//                         }
//                     }
//                     out() << " />\n";
//                 }

//                 // Right operand
//                 if (auto right = bin_expr->get_rhs())
//                 {
//                     out() << "            <right_operand\n";
//                     std::string right_val = getExpressionValue(*right);
//                     if (dynamic_cast<variable_node *>(right) || dynamic_cast<suffixised_node *>(right))
//                     {
//                         writeAttribute("              xsi:type", "chips.xvalues.collective:int_variable_expression");
//                         out() << "\n";
//                         writeAttribute("              variable", get_ast_path_by_name(right_val));
//                     }
//                     else
//                     {
//                         writeAttribute("              xsi:type", "chips.rvalues.collective:direct_int");
//                         if (!right_val.empty())
//                         {
//                             out() << "\n";
//                             writeAttribute("              value", right_val);
//                         }
//                     }
//                     out() << " />\n";
//                 }

//                 out() << "          </condition>\n";
//             }
//             else
//             {
//                 // Simple variable or non-binary condition
//                 std::string cond_path = get_ast_path_by_name(cond_val);
//                 writeAttribute("            xsi:type", "chips.xvalues.collective:bool_variable_expression");
//                 out() << "\n";
//                 writeAttribute("            variable", cond_path);
//                 out() << "/>\n";
//             }
//         }
//     }

//     // If section
//     out() << "          <if_section>\n";
//     if (auto if_node = node.get_if_node())
//     {
//         if (auto if_stmts = if_node->get_statements())
//         {
//             std::string old_tag = m_statement_tag;
//             m_statement_tag = "if_statements";

//             int stmt_index = 0;
//             for (auto &stmt : if_stmts->get_statements())
//             {
//                 if (stmt)
//                 {
//                     std::string segment = "/@if_statements." + std::to_string(stmt_index++);
//                     push_ast_path(segment);
//                     stmt->accept(*this);
//                     pop_ast_path(segment);
//                 }
//             }

//             m_statement_tag = old_tag;
//         }
//     }
//     out() << "          </if_section>\n";

//     // Else section
//     out() << "          <else_section>\n";
//     if (auto else_stmts = node.get_else_node())
//     {
//         std::string old_tag = m_statement_tag;
//         m_statement_tag = "else_statements";

//         int stmt_index = 0;
//         for (auto &stmt : else_stmts->get_statements())
//         {
//             if (stmt)
//             {
//                 std::string segment = "/@else_statements." + std::to_string(stmt_index++);
//                 push_ast_path(segment);
//                 stmt->accept(*this);
//                 pop_ast_path(segment);
//             }
//         }

//         m_statement_tag = old_tag;
//     }
//     out() << "          </else_section>\n";

//     out() << "        </statements>\n";
// }

// void ChipsToXmiVisitor::visit(c_expressions_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_expressions_node)" << std::endl;
//     out() << "    <!-- c_expressions_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_output_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_output_node)" << std::endl;
//     ensure_namespace_for_prefix("chips.rvalues.collective");
//     ensure_namespace_for_prefix("chips.xvalues.collective");

//     auto write_collective_expr = [&](expression_node &expr, const std::string &tag)
//     {
//         if (auto stop_expr = dynamic_cast<stop_node *>(&expr))
//         {
//             (void)stop_expr;
//             out() << "        <" << tag << "\n";
//             writeAttribute("          xsi:type", "chips.rvalues.collective:stop_kw");
//             out() << " />\n";
//             return;
//         }
//         if (auto input_expr = dynamic_cast<input_node *>(&expr))
//         {
//             (void)input_expr;
//             out() << "        <" << tag << "\n";
//             writeAttribute("          xsi:type", "chips.rvalues.collective:input_kw");
//             out() << " />\n";
//             return;
//         }
//         if (auto num = dynamic_cast<number_literal_node *>(&expr))
//         {
//             std::string literal_type = "int";
//             std::string literal_value;
//             EXPRESSION_TYPE type = num->get_type();
//             if (type == FLOAT_EXP)
//             {
//                 literal_type = "float";
//                 literal_value = std::to_string(num->get_float());
//             }
//             else if (type == BOOL_EXP)
//             {
//                 literal_type = "bool";
//                 literal_value = num->get_bool() ? "true" : "false";
//             }
//             else
//             {
//                 literal_type = "int";
//                 literal_value = std::to_string(num->get_int());
//             }

//             out() << "        <" << tag << "\n";
//             writeAttribute("          xsi:type", "chips.rvalues.collective:direct_" + literal_type);
//             if (literal_value != "0" && literal_value != "0.0" && literal_value != "false")
//             {
//                 out() << "\n";
//                 writeAttribute("          value", literal_value);
//             }
//             out() << " />\n";
//             return;
//         }

//         std::string expr_name = getExpressionValue(expr);
//         SymbolInfo info = get_symbol_info(expr_name);
//         std::string dataflow_type = "int";
//         if (info.type == "bool")
//         {
//             dataflow_type = "bool";
//         }
//         else if (info.type == "float")
//         {
//             dataflow_type = "float";
//         }

//         std::string variable_path = get_ast_path_by_name(expr_name);
//         out() << "        <" << tag << "\n";
//         writeAttribute("          xsi:type", "chips.xvalues.collective:" + dataflow_type + "_variable_expression");
//         out() << "\n";
//         writeAttribute("          variable", variable_path);
//         out() << " />\n";
//     };

//     std::string output_name = node.get_identifier();
//     bool is_default = (output_name == "default");

//     if (is_default)
//     {
//         out() << "      <default_output>\n";
//     }
//     else
//     {
//         std::string channel_path = get_ast_path_by_name(output_name);
//         out() << "      <channeled_output\n";
//         writeAttribute("        channel", channel_path);
//         out() << ">\n";
//     }

//     if (auto exprs = node.get_expressions())
//     {
//         for (const auto &expr : exprs->get_expressions())
//         {
//             if (expr)
//             {
//                 write_collective_expr(*expr, "accumulator_expressions");
//             }
//         }
//     }

//     if (is_default)
//     {
//         out() << "      </default_output>\n";
//     }
//     else
//     {
//         out() << "      </channeled_output>\n";
//     }
// }

// void ChipsToXmiVisitor::visit(c_optionnal_outputs_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_optionnal_outputs_node)" << std::endl;
//     for (auto &output : node.get_outputs())
//     {
//         if (output)
//         {
//             output->accept(*this);
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(collective_dataflow_defaulted_decls_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_dataflow_defaulted_decls_node)" << std::endl;
//     out() << "    <!-- collective_dataflow_defaulted_decls_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(collective_dataflow_defaulted_decl_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_dataflow_defaulted_decl_node)" << std::endl;
//     out() << "    <!-- collective_dataflow_defaulted_decl_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(collective_dataflow_full_declaration_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_dataflow_full_declaration_node)" << std::endl;

//     std::string var_name = node.get_identifier();
//     std::string var_path = get_ast_path() + "/@variable";

//     // Determine type
//     std::string type_name = "int";
//     if (auto df_type = node.get_df_type())
//     {
//         DATAFLOW_TYPE dtype = df_type->get_type();
//         if (dtype == INT_DF)
//             type_name = "int";
//         else if (dtype == FLOAT_DF)
//             type_name = "float";
//         else if (dtype == BOOL_DF)
//             type_name = "bool";
//     }

//     // Register variable immediately so subsequent statements can find it
//     register_variable(var_name, var_path, "collective_parameter:" + type_name);
//     std::cerr << "[DEBUG] Collective variable '" << var_name << "' registered with path: " << var_path << std::endl;

//     // Emit declaration statement
//     out() << "        <" << m_statement_tag << "\n";
//     writeAttribute("          xsi:type", statement_type(type_name + "_declaration", StatementFamily::Collective));
//     out() << ">\n";
//     out() << "          <variable\n";
//         writeAttribute("            name", var_name);
//         out() << " />\n";
//     out() << "        </" << m_statement_tag << ">\n";

//     // If it has an RHS (assignment), emit assignment statement
//     if (auto rhs = node.get_rhs())
//     {
//         if (auto expr = rhs->get_expression())
//         {
//             m_extra_statements_generated++;
//             std::cerr << "[DEBUG] collective_dataflow: Assignment détecté pour variable '" << var_name << "', extra=" << m_extra_statements_generated << std::endl;
            
//             out() << "        <" << m_statement_tag << "\n";
//             writeAttribute("          xsi:type", statement_type(type_name + "_assignment", StatementFamily::Collective));
//             out() << ">\n";

//             // lvalue - the variable
//             out() << "          <lvalue\n";
//             writeAttribute("            xsi:type", "chips.xvalues.collective:" + type_name + "_variable_expression");
//             out() << "\n";
//             writeAttribute("            variable", var_path);
//             out() << "/>\n";

//             // rvalue
//             write_collective_rvalue("          ", "rvalue", *expr, type_name);

//             out() << "        </" << m_statement_tag << ">\n";
//         }
//     }
// }

// void ChipsToXmiVisitor::visit(collective_rhs_assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(collective_rhs_assignment_node)" << std::endl;
//     out() << "    <!-- collective_rhs_assignment_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(c_variable_assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_variable_assignment_node)" << std::endl;

//     std::string var_name = node.get_identifier();
//     std::string var_path = get_ast_path_by_name(var_name);

//     // If variable not found, register it now (implicit declaration)
//     if (var_path == var_name || var_path.empty())
//     {
//         var_path = get_ast_path() + "/@variable";
//         register_variable(var_name, var_path, "collective_parameter:int");
//         std::cerr << "[DEBUG] Collective variable '" << var_name << "' implicitly registered with path: " << var_path << std::endl;
//     }

//     // Determine the type of the variable
//     SymbolInfo var_info = get_symbol_info(var_name);
//     std::string dataflow_type = "int"; // default
//     if (var_info.type.find("collective_parameter:") == 0)
//     {
//         dataflow_type = var_info.type.substr(21); // Extract type after "collective_parameter:"
//     }

//     out() << "        <" << m_statement_tag << "\n";
//     writeAttribute("          xsi:type", statement_type(dataflow_type + "_assignment", StatementFamily::Collective));
//     out() << ">\n";

//     // lvalue
//     out() << "          <lvalue\n";
//     writeAttribute("            xsi:type", "chips.xvalues.collective:" + dataflow_type + "_variable_expression");
//     out() << "\n";
//     writeAttribute("            variable", var_path);
//     out() << "/>\n";

//     // rvalue
//     if (auto expr = node.get_expression())
//     {
//         write_collective_rvalue("          ", "rvalue", *expr, dataflow_type);
//         out() << "        </" << m_statement_tag << ">\n";
//     }
// }

// void ChipsToXmiVisitor::visit(c_context_variable_assignment_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(c_context_variable_assignment_node)" << std::endl;

//     std::string var_name = node.get_identifier();
//     std::string var_path = get_ast_path_by_name(var_name);

//     // Determine the type of the variable
//     SymbolInfo var_info = get_symbol_info(var_name);
//     std::string dataflow_type = "int"; // default
//     if (var_info.type.find("collective_parameter:") == 0)
//     {
//         dataflow_type = var_info.type.substr(22); // Extract type after "collective_parameter:"
//     }

//     out() << "        <" << m_statement_tag << "\n";
//     writeAttribute("          xsi:type", statement_type(dataflow_type + "_assignment", StatementFamily::Collective));
//     out() << ">\n";

//     // lvalue
//     out() << "          <lvalue\n";
//     writeAttribute("            xsi:type", "chips.xvalues.collective:" + dataflow_type + "_variable_expression");
//     out() << "\n";
//     writeAttribute("            variable", var_path);
//     out() << "/>\n";

//     // rvalue
//     if (auto expr = node.get_expression())
//     {
//         write_collective_rvalue("          ", "rvalue", *expr, dataflow_type);
//     }

//     out() << "        </" << m_statement_tag << ">\n";
// }

// // === DATAFLOW TYPES & PARAMETERS ===

void ChipsToXmiVisitor::visit(chips::function_parameter_variant& node){
    std::visit([this](auto* param) {
        if(param){

        }
    }, node);
}

// void ChipsToXmiVisitor::visit(dataflow_type_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(dataflow_type_node)" << std::endl;
//     out() << "    <!-- dataflow_type_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(physical_dataflow_parameter_type_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_type_node)" << std::endl;
//     out() << "    <!-- physical_dataflow_parameter_type_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(expressions_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(expressions_node)" << std::endl;
//     out() << "    <!-- expressions_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(dataflow_parameter_list_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_list_node)" << std::endl;
//     out() << "    <!-- dataflow_parameter_list_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(physical_dataflow_parameter_list_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_list_node)" << std::endl;
//     out() << "    <!-- physical_dataflow_parameter_list_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(dataflow_parameter_decls_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_decls_node)" << std::endl;
//     out() << "    <!-- dataflow_parameter_decls_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(physical_dataflow_parameter_decls_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_decls_node)" << std::endl;
//     out() << "    <!-- physical_dataflow_parameter_decls_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(dataflow_parameter_decl_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_decl_node)" << std::endl;
//     out() << "    <!-- dataflow_parameter_decl_node TODO -->\n";
//     (void)node;
// }

// void ChipsToXmiVisitor::visit(physical_dataflow_parameter_decl_node &node)
// {
//     std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_decl_node)" << std::endl;
//     out() << "    <!-- physical_dataflow_parameter_decl_node TODO -->\n";
//     (void)node;
// }

// // === FALLBACK ===

void ChipsToXmiVisitor::visit(chips::ast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // TODO : comprendre pourquoi on arrive ici après un noeud with
    out() << "    <!-- ast_node générique -->\n";
}

// === HELPERS ===

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

void ChipsToXmiVisitor::writeAttribute(const std::string &name, const std::string &value)
{
    std::string normalized = name;
    while (!normalized.empty() && (normalized.front() == ' ' || normalized.front() == '\t'))
    {
        normalized.erase(normalized.begin());
    }

    if (normalized == "xsi:type")
    {
        ensure_namespace_for_type(value);
    }
    out() << " " << name << "=\"" << value << "\"";
}

void ChipsToXmiVisitor::ensure_namespace_for_prefix(const std::string &ns_prefix)
{
    if (ns_prefix.empty())
    {
        return;
    }

    std::string suffix = ns_prefix;
    if (suffix.rfind("chips.", 0) == 0)
    {
        suffix = suffix.substr(6);
    }

    size_t pos = 0;
    while ((pos = suffix.find('.', pos)) != std::string::npos)
    {
        suffix.replace(pos, 1, "/");
        pos++;
    }

    std::string url = suffix.empty() || suffix[0] != '/'
                          ? "http://chips/" + suffix
                          : "http://chips" + suffix;
    m_writer.add_namespace_if_needed(ns_prefix, url);
}

void ChipsToXmiVisitor::ensure_namespace_for_type(const std::string &type_value)
{
    size_t colon_pos = type_value.find(':');
    if (colon_pos == std::string::npos)
    {
        return;
    }
    ensure_namespace_for_prefix(type_value.substr(0, colon_pos));
}

void ChipsToXmiVisitor::endEmptyElement()
{
    out() << " />\n";
}

std::string ChipsToXmiVisitor::getExpressionValue(expression_node &expr)
{
    std::cerr << "[DEBUG getExpressionValue] Analyse d'une expression" << std::endl;

    // Essayer binary_expression_node
    if (auto bin = dynamic_cast<binary_expression_node *>(&expr))
    {
        std::cerr << "[DEBUG getExpressionValue] --> Expression binaire détectée" << std::endl;
        return "binary_expression";
    }

    // Essayer number_literal_node
    if (auto num = dynamic_cast<number_literal_node *>(&expr))
    {
        std::cerr << "[DEBUG getExpressionValue] --> Number literal détecté" << std::endl;
        EXPRESSION_TYPE type = num->get_type();
        if (type == INT_EXP)
        {
            return std::to_string(num->get_int());
        }
        else if (type == FLOAT_EXP)
        {
            return std::to_string(num->get_float());
        }
        else if (type == BOOL_EXP)
        {
            return num->get_bool() ? "true" : "false";
        }
    }
    // Essayer suffixised_node (variable ou attribut)
    else if (auto suf = dynamic_cast<suffixised_node *>(&expr))
    {
        std::cerr << "[DEBUG getExpressionValue] --> Suffixised node détecté: " << suf->get_identifier() << std::endl;
        return suf->get_identifier();
    }
    // Essayer function_call_node
    else if (auto fcall = dynamic_cast<function_call_node *>(&expr))
    {
        std::cerr << "[DEBUG getExpressionValue] --> Function call détecté: " << fcall->get_identifier() << std::endl;
        return fcall->get_identifier() + "()";
    }
    // Essayer variable_node
    else if (auto var = dynamic_cast<variable_node *>(&expr))
    {
        std::cerr << "[DEBUG getExpressionValue] --> Variable node détecté" << std::endl;
        return var->get_identifier();
    }

    // Fallback
    std::cerr << "[DEBUG getExpressionValue] --> Type inconnu, retour 'unknown'" << std::endl;
    return "unknown";
}

void ChipsToXmiVisitor::write_collective_rvalue(const std::string &indent, const std::string &tag, expression_node &expr, const std::string &value_type)
{
    std::string attr_indent = indent + "  ";

    if (auto bin_expr = dynamic_cast<binary_expression_node *>(&expr))
    {
        EXPRESSION_TYPE op_type = bin_expr->get_type();
        std::string op_xsi;
        std::string operand_type = value_type;
        std::string numeric_type = (value_type == "float") ? "float" : "int";

        switch (op_type)
        {
        case PLUS_EXP:
            op_xsi = "chips.rvalues.collective.operators." + numeric_type + ":plus";
            operand_type = numeric_type;
            break;
        case MINUS_EXP:
            op_xsi = "chips.rvalues.collective.operators." + numeric_type + ":minus";
            operand_type = numeric_type;
            break;
        case TIMES_EXP:
            op_xsi = "chips.rvalues.collective.operators." + numeric_type + ":mult";
            operand_type = numeric_type;
            break;
        case DIV_EXP:
            op_xsi = "chips.rvalues.collective.operators." + numeric_type + ":div";
            operand_type = numeric_type;
            break;
        case MOD_EXP:
            op_xsi = "chips.rvalues.collective.operators.int:mod";
            operand_type = "int";
            break;
        case AND_EXP:
            op_xsi = "chips.rvalues.collective.operators.bool:and";
            operand_type = "bool";
            break;
        case OR_EXP:
            op_xsi = "chips.rvalues.collective.operators.bool:or";
            operand_type = "bool";
            break;
        case EQ_EXP:
            if (value_type == "bool")
                op_xsi = "chips.rvalues.collective.operators.bool:eq_bool";
            else if (value_type == "float")
                op_xsi = "chips.rvalues.collective.operators.bool:eq_float";
            else
                op_xsi = "chips.rvalues.collective.operators.bool:eq_int";
            operand_type = (value_type == "float") ? "float" : (value_type == "bool") ? "bool"
                                                                                         : "int";
            break;
        case NEQ_EXP:
            if (value_type == "bool")
                op_xsi = "chips.rvalues.collective.operators.bool:neq_bool";
            else if (value_type == "float")
                op_xsi = "chips.rvalues.collective.operators.bool:neq_float";
            else
                op_xsi = "chips.rvalues.collective.operators.bool:neq_int";
            operand_type = (value_type == "float") ? "float" : (value_type == "bool") ? "bool"
                                                                                         : "int";
            break;
        case GT_EXP:
            op_xsi = (value_type == "float") ? "chips.rvalues.collective.operators.bool:gt_float"
                                               : "chips.rvalues.collective.operators.bool:gt_int";
            operand_type = (value_type == "float") ? "float" : "int";
            break;
        case LT_EXP:
            op_xsi = (value_type == "float") ? "chips.rvalues.collective.operators.bool:lt_float"
                                               : "chips.rvalues.collective.operators.bool:lt_int";
            operand_type = (value_type == "float") ? "float" : "int";
            break;
        case GEQ_EXP:
            op_xsi = (value_type == "float") ? "chips.rvalues.collective.operators.bool:geq_float"
                                               : "chips.rvalues.collective.operators.bool:geq_int";
            operand_type = (value_type == "float") ? "float" : "int";
            break;
        case LEQ_EXP:
            op_xsi = (value_type == "float") ? "chips.rvalues.collective.operators.bool:leq_float"
                                               : "chips.rvalues.collective.operators.bool:leq_int";
            operand_type = (value_type == "float") ? "float" : "int";
            break;
        default:
            op_xsi = "chips.rvalues.collective.operators.int:plus";
            operand_type = "int";
            break;
        }

        out() << indent << "<" << tag << "\n";
        writeAttribute(attr_indent + "xsi:type", op_xsi);
        out() << ">\n";

        if (auto left = bin_expr->get_lhs())
        {
            write_collective_rvalue(indent + "  ", "left_operand", *left, operand_type);
        }
        if (auto right = bin_expr->get_rhs())
        {
            write_collective_rvalue(indent + "  ", "right_operand", *right, operand_type);
        }

        out() << indent << "</" << tag << ">\n";
        return;
    }

    if (dynamic_cast<input_node *>(&expr))
    {
        out() << indent << "<" << tag << "\n";
        writeAttribute(attr_indent + "xsi:type", "chips.rvalues.collective:input_kw");
        out() << " />\n";
        return;
    }

    if (dynamic_cast<stop_node *>(&expr))
    {
        out() << indent << "<" << tag << "\n";
        writeAttribute(attr_indent + "xsi:type", "chips.rvalues.collective:stop_kw");
        out() << " />\n";
        return;
    }

    if (auto kw = dynamic_cast<suffixised_node *>(&expr))
    {
        std::string kw_name = kw->get_identifier();
        if (kw_name == "input" || kw_name == "stop")
        {
            out() << indent << "<" << tag << "\n";
            writeAttribute(attr_indent + "xsi:type", kw_name == "input"
                                                        ? "chips.rvalues.collective:input_kw"
                                                        : "chips.rvalues.collective:stop_kw");
            out() << " />\n";
            return;
        }
    }

    if (dynamic_cast<variable_node *>(&expr) || dynamic_cast<suffixised_node *>(&expr))
    {
        std::string expr_val = getExpressionValue(expr);
        out() << indent << "<" << tag << "\n";
        writeAttribute(attr_indent + "xsi:type", "chips.xvalues.collective:" + value_type + "_variable_expression");
        out() << "\n";
        writeAttribute(attr_indent + "variable", get_ast_path_by_name(expr_val));
        out() << " />\n";
        return;
    }

    std::string expr_val = getExpressionValue(expr);
    out() << indent << "<" << tag << "\n";
    writeAttribute(attr_indent + "xsi:type", "chips.rvalues.collective:direct_" + value_type);
    if (!expr_val.empty() && expr_val != "0" && expr_val != "0.0" && expr_val != "false")
    {
        out() << "\n";
        writeAttribute(attr_indent + "value", expr_val);
    }
    out() << " />\n";
}

void ChipsToXmiVisitor::write_collective_output_expression(expression_node &expr, const std::string &tag, const std::string &indent)
{
    // Handle stop_kw and input_kw nodes
    if (dynamic_cast<stop_node *>(&expr))
    {
        out() << indent << "<" << tag << "\n";
        writeAttribute(indent + "  xsi:type", "chips.rvalues.collective:stop_kw");
        out() << " />\n";
        return;
    }

    if (dynamic_cast<input_node *>(&expr))
    {
        out() << indent << "<" << tag << "\n";
        writeAttribute(indent + "  xsi:type", "chips.rvalues.collective:input_kw");
        out() << " />\n";
        return;
    }

    // Handle suffixised_node that might be "stop" or "input" keywords
    if (auto suf = dynamic_cast<suffixised_node *>(&expr))
    {
        std::string val_name = suf->get_identifier();
        if (val_name == "stop")
        {
            out() << indent << "<" << tag << "\n";
            writeAttribute(indent + "  xsi:type", "chips.rvalues.collective:stop_kw");
            out() << " />\n";
            return;
        }
        if (val_name == "input")
        {
            out() << indent << "<" << tag << "\n";
            writeAttribute(indent + "  xsi:type", "chips.rvalues.collective:input_kw");
            out() << " />\n";
            return;
        }
    }

    // Handle numeric literals
    if (auto num = dynamic_cast<number_literal_node *>(&expr))
    {
        std::string literal_type = "int";
        std::string literal_value;
        EXPRESSION_TYPE type = num->get_type();
        if (type == FLOAT_EXP)
        {
            literal_type = "float";
            literal_value = std::to_string(num->get_float());
        }
        else if (type == BOOL_EXP)
        {
            literal_type = "bool";
            literal_value = num->get_bool() ? "true" : "false";
        }
        else
        {
            literal_type = "int";
            literal_value = std::to_string(num->get_int());
        }

        out() << indent << "<" << tag << "\n";
        writeAttribute(indent + "  xsi:type", "chips.rvalues.collective:direct_" + literal_type);
        if (literal_value != "0" && literal_value != "0.0" && literal_value != "false")
        {
            out() << "\n";
            writeAttribute(indent + "  value", literal_value);
        }
        out() << " />\n";
        return;
    }

    // Handle variables - determine type from symbol table
    std::string expr_name = getExpressionValue(expr);
    SymbolInfo info = get_symbol_info(expr_name);
    std::string dataflow_type = "int"; // default

    // Extract type from info.type (e.g., "collective_parameter:bool" -> "bool")
    if (info.type.find("collective_parameter:") == 0)
    {
        dataflow_type = info.type.substr(21); // After "collective_parameter:"
    }
    else if (info.type == "bool" || info.type == "int" || info.type == "float")
    {
        dataflow_type = info.type;
    }

    std::string variable_path = get_ast_path_by_name(expr_name);
    out() << indent << "<" << tag << "\n";
    writeAttribute(indent + "  xsi:type", "chips.xvalues.collective:" + dataflow_type + "_variable_expression");
    out() << "\n";
    writeAttribute(indent + "  variable", variable_path);
    out() << " />\n";
}

void ChipsToXmiVisitor::write_index_from_suffixes(suffixes_node *suffixes,
                                                  const std::string &indent,
                                                  const std::string &xvalue_prefix,
                                                  const std::string &rvalue_prefix,
                                                  bool emit_default)
{
    if (!suffixes || suffixes->get_suffixes().empty())
    {
        if (!emit_default)
        {
            return;
        }
        out() << indent << "<index\n";
        writeAttribute(indent + "  xsi:type", rvalue_prefix + ":direct_int");
        out() << " />\n";
        return;
    }

    expression_node *expr = suffixes->get_suffixes().front().get();
    if (!expr)
    {
        if (!emit_default)
        {
            return;
        }
        out() << indent << "<index\n";
        writeAttribute(indent + "  xsi:type", rvalue_prefix + ":direct_int");
        out() << " />\n";
        return;
    }

    if (auto bin_expr = dynamic_cast<binary_expression_node *>(expr))
    {
        std::string op_name;
        switch (bin_expr->get_type())
        {
        case PLUS_EXP:
            op_name = "plus";
            break;
        case MINUS_EXP:
            op_name = "minus";
            break;
        case TIMES_EXP:
            op_name = "times";
            break;
        case DIV_EXP:
            op_name = "divide";
            break;
        case MOD_EXP:
            op_name = "modulo";
            break;
        default:
            op_name = "minus";
            break;
        }

        out() << indent << "<index\n";
        writeAttribute(indent + "  xsi:type", "chips.rvalues.dataflow.operators.int:" + op_name);
        out() << ">\n";

        auto write_operand = [&](const std::string &tag, expression_node *operand)
        {
            out() << indent << "  <" << tag << "\n";
            if (dynamic_cast<variable_node *>(operand) || dynamic_cast<suffixised_node *>(operand))
            {
                writeAttribute(indent + "    xsi:type", xvalue_prefix + ":int_variable_expression");
                out() << "\n";
                writeAttribute(indent + "    variable", get_ast_path_by_name(getExpressionValue(*operand)));
                out() << " />\n";
                return;
            }
            if (auto num = dynamic_cast<number_literal_node *>(operand))
            {
                std::string value = getExpressionValue(*operand);
                writeAttribute(indent + "    xsi:type", rvalue_prefix + ":direct_int");
                if (!value.empty() && value != "0" && value != "0.0" && value != "false")
                {
                    out() << "\n";
                    writeAttribute(indent + "    value", value);
                }
                out() << " />\n";
                return;
            }
            writeAttribute(indent + "    xsi:type", rvalue_prefix + ":direct_int");
            out() << " />\n";
        };

        write_operand("left_operand", bin_expr->get_lhs());
        write_operand("right_operand", bin_expr->get_rhs());
        out() << indent << "</index>\n";
        return;
    }

    out() << indent << "<index\n";
    std::string expr_value = getExpressionValue(*expr);
    bool is_var_expr = dynamic_cast<variable_node *>(expr) || dynamic_cast<suffixised_node *>(expr);

    if (is_var_expr)
    {
        writeAttribute(indent + "  xsi:type", xvalue_prefix + ":int_variable_expression");
        out() << "\n";
        writeAttribute(indent + "  variable", get_ast_path_by_name(expr_value));
        out() << " />\n";
        return;
    }

    writeAttribute(indent + "  xsi:type", rvalue_prefix + ":direct_int");
    if (expr_value != "0" && expr_value != "0.0" && expr_value != "false" && expr_value != "unknown")
    {
        out() << "\n";
        writeAttribute(indent + "  value", expr_value);
    }
    out() << " />\n";
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

std::string ChipsToXmiVisitor::get_xsi_type_for_symbol(const SymbolInfo &info)
{
    // Map symbol type to xsi:type for variable expressions
    std::string type = info.type;

    if (type == "physical")
    {
        return "chips.systemspecific.expressions:physical_variable_expression";
    }
    else if (type == "logical")
    {
        return "chips.systemspecific.expressions:logical_variable_expression";
    }
    else if (type == "object")
    {
        return "chips.systemspecific.expressions:object_variable_expression";
    }

    // Unknown type - log warning and return generic expression type
    std::cerr << "[WARNING] Unknown symbol type in get_xsi_type_for_symbol: '" << type << "'" << std::endl;
    return "chips.systemspecific.expressions:variable_expression";
}

std::string ChipsToXmiVisitor::get_declaration_type_from_definition(const std::string &definition_type)
{
    // Map definition type to declaration xsi:type in system section
    // physical_definition -> physical_declaration
    // logical_definition -> logical_declaration
    // object_definition -> object_declaration

    if (definition_type == "physical")
    {
        return "chips.statements.system:physical_declaration";
    }
    else if (definition_type == "logical")
    {
        return "chips.statements.system:logical_declaration";
    }
    else if (definition_type == "object")
    {
        return "chips.statements.system:object_declaration";
    }

    // Unknown type - log warning and return generic
    std::cerr << "[WARNING] Unknown definition type in get_declaration_type_from_definition: '"
              << definition_type << "'" << std::endl;
    return "chips.statements.system:declaration";
}

ChipsToXmiVisitor::SymbolInfo ChipsToXmiVisitor::get_symbol_info(const std::string &name)
{
    auto it = m_symbol_table.find(name);
    if (it != m_symbol_table.end())
    {
        return it->second;
    }

    std::cerr << ">>>>>>>>>[WARNING] Symbol '" << name << "' NON trouvé dans la table des symboles" << std::endl;
    return SymbolInfo(name, "unknown"); // Fallback
}

void ChipsToXmiVisitor::report_semantic_error(const std::string &message)
{
    std::string detail = message;
    if (!m_current_ast_path.empty())
    {
        detail += " (path: " + m_current_ast_path + ")";
    }
    m_semantic_errors.push_back(detail);
    std::cerr << "[SEMANTIC ERROR] " << detail << std::endl;
}