#include "ChipsToXmiVisitor.hpp"
#include <iostream>

/*
question : quand on entre dans init on tombe sur un statement_node sans plus de précision. est-ce normal ?

*/

// === PROGRAM & CONTEXT ===

void ChipsToXmiVisitor::visit(chips_node &node)
{
    std::cerr << "\n[DEBUG Visitor] ========================================" << std::endl;
    std::cerr << "[DEBUG Visitor] visit(chips_node) DÉMARRÉ" << std::endl;
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    std::cerr << "[DEBUG Visitor] ========================================" << std::endl;
    // Contenu après xmi_header() → directement les enfants
    if (auto pres = node.get_preambles())
    {
        std::cerr << "[DEBUG Visitor] Preambles trouvé, appel accept()" << std::endl;
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

    std::cerr << "[DEBUG Visitor] visit(chips_node) TERMINÉ" << std::endl;
}

void ChipsToXmiVisitor::visit(preambles_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(preambles_node) appelé" << std::endl;
    std::cerr << "[DEBUG Visitor] Nombre de preambles: " << node.get_preamble_list().size() << std::endl;

    out() << "  <preamble>\n";

    push_ast_path("/@preamble");
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

    int index = 0;
    for (auto &pre : node.get_preamble_list())
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

void ChipsToXmiVisitor::visit(preamble_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(preamble_node) appelé - classe de base" << std::endl;
    // Ne rien générer ici - les sous-classes concrètes
    // (object_definition, function_definition, etc.)
    // généreront leurs propres balises
    // via leurs visiteurs spécifiques
}

void ChipsToXmiVisitor::visit(system_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(system_node) appelé" << std::endl;

    out() << "  <system>\n";

    push_ast_path("/@system");
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

    // Parcourir les déclarations système
    if (auto statements = node.get_system_statements())
    {
        std::cerr << "[DEBUG Visitor] System statements trouvé, "
                  << statements->get_statements().size() << " statements" << std::endl;
        int index = 0;
        for (auto &st : statements->get_statements())
        {
            if (st)
            {
                std::string segment = "/@system." + std::to_string(index++);
                push_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
                st->accept(*this);
                pop_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun system statements!" << std::endl;
    }

    pop_ast_path("/@system");
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    out() << "  </system>\n";
}

// === SYSTEM STATEMENTS ===

void ChipsToXmiVisitor::visit(s_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_statements_node) appelé" << std::endl;
    int index = 0;
    for (auto &st : node.get_statements())
    {
        if (st)
        {
            std::string segment = "/@statements." + std::to_string(index++);
            push_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            st->accept(*this);
            pop_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        }
    }
}

void ChipsToXmiVisitor::visit(const s_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(const s_statements_node) appelé" << std::endl;
    int index = 0;
    for (auto &st : node.get_statements())
    {
        if (st)
        {
            std::string segment = "/@statements." + std::to_string(index++);
            push_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            st->accept(*this);
            pop_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        }
    }
}

void ChipsToXmiVisitor::visit(s_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_statement_node) type: "
              << node.get_statement_type() << std::endl;

    switch (node.get_statement_type())
    {
    case S_IMPLEMENTS_ST:
        if (auto impl = dynamic_cast<implements_node *>(&node))
            impl->accept(*this);
        break;
    case S_LINK_ST:
        if (auto link = dynamic_cast<link_node *>(&node))
            link->accept(*this);
        break;
    default:
        out() << "    <!-- s_statement_node type="
              << node.get_statement_type() << " -->\n";
    }
}

void ChipsToXmiVisitor::visit(implements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(implements_node)" << std::endl;
    out() << "    <!-- implements_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(link_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(link_node)" << std::endl;
    out() << "    <!-- link_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(plugging_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(plugging_node)" << std::endl;
    out() << "    <!-- plugging_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(s_loop_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_loop_node)" << std::endl;
    out() << "    <!-- s_loop_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(s_if_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_if_node)" << std::endl;
    out() << "    <!-- s_if_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(s_if_else_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_if_else_node)" << std::endl;
    out() << "    <!-- s_if_else_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(functionnal_block_instanciation_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(functionnal_block_instanciation_node)" << std::endl;
    out() << "    <!-- functionnal_block_instanciation_node TODO -->\n";
}

// === DECLARATION CONTEXT ===

void ChipsToXmiVisitor::visit(object_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(object_definition_node) name="
              << node.get_identifier() << std::endl;

    out() << "    <definitions\n";
    writeAttribute("      xsi:type", "definitions:object_definition");
    out() << "\n";
    writeAttribute("      name", node.get_identifier());
    out() << ">\n";

    // Visiter la section "with" si elle existe
    if (auto with = node.get_with())
    {
        std::cerr << "[DEBUG Visitor] Object a une section with" << std::endl;
        push_ast_path("/@with");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        with->accept(*this);
        pop_ast_path("/@with");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    }
    else
    {
        std::cerr << "[DEBUG Visitor] Object SANS section with" << std::endl;
    }

    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(function_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(function_definition_node) - classe abstraite" << std::endl;
    out() << "    <!-- function_definition_node abstrait -->\n";
}

void ChipsToXmiVisitor::visit(logical_function_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(logical_function_definition_node) name="
              << node.get_identifier() << std::endl;

    out() << "    <definitions\n";
    writeAttribute("      xsi:type", "definitions:logical_definition");
    out() << "\n";
    writeAttribute("      name", node.get_identifier());
    out() << ">\n";

    if (auto init = node.get_init())
    {
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

    // outputs not visited here (no visitor overload for named_outputs_node)
    out() << "      <!-- TODO: outputs -->\n";

    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(physical_function_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_function_definition_node) name="
              << node.get_identifier() << std::endl;

    out() << "    <definitions\n";
    writeAttribute("      xsi:type", "definitions:physical_definition");
    out() << "\n";
    writeAttribute("      name", node.get_identifier());
    out() << ">\n";

    // Enregistrer les paramètres (sensors, actuators, etc.) dans la table des symboles
    if (auto params = node.get_pdf_parameter_list())
    {
        std::cerr << "[DEBUG Visitor] Physical a des paramètres" << std::endl;
        int sensor_index = 0;
        int actuator_index = 0;
        
        for (auto &param : params->get_pdf_param_decls())
        {
            if (param)
            {
                std::string param_name = param->get_identifier();
                auto param_type = param->get_df_type();
                
                // TODO: Vérifier si c'est un sensor ou actuator via is_sensor
                // Pour l'instant, on suppose que c'est un sensor si le nom du paramètre est typique
                // Une meilleure approche serait d'ajouter une méthode is_sensor() à physical_dataflow_parameter_type_node
                
                // Chemin pour sensor: //@preamble/@definitions.X/@sensor.Y/@declaration/@variable
                std::string param_path = get_ast_path() + "/@sensor." + std::to_string(sensor_index) + "/@declaration/@variable";
                register_variable(param_name, param_path);
                std::cerr << "[DEBUG] Paramètre sensor '" << param_name << "' enregistré avec le chemin: " << param_path << std::endl;
                sensor_index++;
            }
        }
    }

    // Visiter les sections dans l'ordre : with, init, then, puis outputs
    // (outputs doit être visité après init/then pour avoir accès aux chemins des variables déclarées)
    if (auto with = node.get_with())
    {
        std::cerr << "[DEBUG Visitor] Physical a une section with" << std::endl;
        push_ast_path("/@with");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        with->accept(*this);
        pop_ast_path("/@with");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    }

    if (auto init = node.get_init())
    {
        std::cerr << "[DEBUG Visitor] Physical a une section init" << std::endl;
        push_ast_path("/@init");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        init->accept(*this);
        pop_ast_path("/@init");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    }

    if (auto then = node.get_then())
    {
        std::cerr << "[DEBUG Visitor] Physical a une section then" << std::endl;
        push_ast_path("/@then");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        then->accept(*this);
        pop_ast_path("/@then");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    }

    if (auto outputs = node.get_outputs())
    {
        std::cerr << "[DEBUG Visitor] Physical a des outputs" << std::endl;
        push_ast_path("/@outputs");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        outputs->accept(*this);
        pop_ast_path("/@outputs");
        std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
    }

    // Générer les sensors
    if (auto params = node.get_pdf_parameter_list())
    {
        std::cerr << "[DEBUG Visitor] Génération des sensors" << std::endl;
        int sensor_index = 0;
        
        for (auto &param : params->get_pdf_param_decls())
        {
            if (param)
            {
                std::string param_name = param->get_identifier();
                auto param_type = param->get_df_type();
                
                // Déterminer le type du paramètre
                std::string dataflow_type = "int"; // Default
                if (param_type && param_type->get_df_type())
                {
                    DATAFLOW_TYPE df_type = param_type->get_df_type()->get_type();
                    if (df_type == INT_DF)
                        dataflow_type = "int";
                    else if (df_type == FLOAT_DF)
                        dataflow_type = "float";
                    else if (df_type == BOOL_DF)
                        dataflow_type = "bool";
                }
                
                std::cerr << "[DEBUG] Génération du sensor #" << sensor_index << ": " << param_name << " (" << dataflow_type << ")" << std::endl;
                
                push_ast_path("/@sensor." + std::to_string(sensor_index));
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
                
                out() << "      <sensor\n";
                writeAttribute("          xsi:type", "chips.parameters.physical:" + dataflow_type + "_physical_parameter");
                out() << "\n";
                writeAttribute("          name", param_name);
                out() << ">\n";
                
                out() << "        <declaration>\n";
                push_ast_path("/@declaration");
                out() << "          <variable\n";
                writeAttribute("              name", param_name);
                out() << "/>\n";
                pop_ast_path("/@declaration");
                out() << "        </declaration>\n";
                
                out() << "      </sensor>\n";
                
                pop_ast_path("/@sensor." + std::to_string(sensor_index));
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
                sensor_index++;
            }
        }
    }

    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(collective_operation_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_operation_definition_node)" << std::endl;
    out() << "    <!-- collective_operation_definition_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(implementation_definition_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(implementation_definition_node) name="
              << node.get_ident1() << std::endl;

    out() << "    <definitions\n";
    writeAttribute("      xsi:type", "definitions:implementation_definition");
    out() << "\n";
    writeAttribute("      name", node.get_ident1());
    out() << ">\n";

    out() << "      <!-- TODO: implemented_object, implementing_node, having -->\n";

    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(node_mappings_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(node_mappings_node)" << std::endl;
    out() << "    <!-- node_mappings_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(c_signature_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_signature_node)" << std::endl;
    out() << "    <!-- c_signature_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(output_node)" << std::endl;
    out() << "    <!-- output_node TODO -->\n";
}

// === WITH / SECTIONS ===

void ChipsToXmiVisitor::visit(with_section_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_section_node)" << std::endl;

    out() << "      <with>\n";

    if (auto statements = node.get_statements())
    {
        std::cerr << "[DEBUG Visitor] With section a des statements" << std::endl;
        statements->accept(*this);
    }

    out() << "      </with>\n";
}

void ChipsToXmiVisitor::visit(with_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_statements_node) - "
              << node.get_statements().size() << " statements" << std::endl;

    int index = 0;
    for (auto &st : node.get_statements())
    {
        if (st)
        {
            std::string segment = "/@statements." + std::to_string(index++);
            push_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            st->accept(*this);
            pop_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        }
    }
}

void ChipsToXmiVisitor::visit(with_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_statement_node)" << std::endl;
    out() << "        <!-- with_statement_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(with_two_identifier_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_two_identifier_node)" << std::endl;

    std::string type_identifier = node.get_ident1();
    std::string name = node.get_ident2();
    std::string type = "chips.statements.node:channel_declaration";

    out() << "        <statements\n";
    writeAttribute("          xsi:type", type);
    out() << "\n";
    writeAttribute("          name", name);
    out() << "\n";
    writeAttribute("          type_identifier", type_identifier);
    out() << "/>\n";
}

void ChipsToXmiVisitor::visit(with_context_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_context_statement_node)" << std::endl;

    bool has_value = true;

    std::string name = node.get_identifier();
    std::string type_primitive = node.get_df_type()->get_type() == INT_DF ? "int" : node.get_df_type()->get_type() == FLOAT_DF ? "float"
                                                                                : node.get_df_type()->get_type() == BOOL_DF    ? "bool"
                                                                                                                               : "Unknown";
    std::string type = "chips.statements.node:contextual_" + type_primitive + "_declaration";

    std::string segment = "/@variable/@variable";
    push_ast_path(segment);
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;

    // Enregistrer la variable dans la table des symboles
    register_variable(name, get_ast_path());
    std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;

    expression_node *rhs = node.get_rhs()->get_rhs();

    std::string rhs_value = getExpressionValue(*rhs);

    out() << "        <statements\n";
    writeAttribute("        xsi:type", type);
    out() << "\n";
    writeAttribute("        identifier", name);
    out() << ">\n          <variable>\n            <variable\n";
    writeAttribute("name", name);
    out() << "/>\n          </variable>\n";
    if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false" && rhs_value != "unknown")
    {
        out() << "        </" << m_statement_tag << ">\n        <" << m_statement_tag << "\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type_primitive + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type_primitive + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", get_ast_path());
        out() << "/>\n";
        out() << "          <rvalue\n";
        writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type_primitive);
        std::cerr << "[Debug] value ?????????????? " << rhs_value << std::endl;
        if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false") {
            out() << "\n";
            writeAttribute("            value", rhs_value);
        }
        out() << "/>\n";
    }
    out() << "        </" << m_statement_tag << ">\n";
    pop_ast_path(segment);
    std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
}

void ChipsToXmiVisitor::visit(init_section_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(init_section_node)" << std::endl;
    out() << "      <init>\n";
    if (auto statements = node.get_statements())
    {
        int index = 0;
        for (auto &st : statements->get_statements())
        {
            if (st)
            {
                std::string segment = "/@statements." + std::to_string(index++);
                push_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
                st->accept(*this);
                pop_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            }
        }
    }
    else
    {
        out() << "        <!-- TODO: statements -->\n";
    }
    out() << "      </init>\n";
}

void ChipsToXmiVisitor::visit(then_section_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(then_section_node)" << std::endl;
    out() << "      <then>\n";
    if (auto statements = node.get_statements())
    {
        int index = 0;
        for (auto &st : statements->get_statements())
        {
            if (st)
            {
                std::string segment = "/@statements." + std::to_string(index++);
                push_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
                st->accept(*this);
                pop_ast_path(segment);
                std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            }
        }
    }
    else
    {
        out() << "        <!-- TODO: statements -->\n";
    }
    out() << "      </then>\n";
}

void ChipsToXmiVisitor::visit(physical_named_outputs_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_named_outputs_node)" << std::endl;
    
    int index = 0;
    for (auto &output : node.get_outputs())
    {
        if (output)
        {
            std::string segment = "/@output." + std::to_string(index++);
            push_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
            output->accept(*this);
            pop_ast_path(segment);
            std::cerr << "                                                                                    [DEBUG AST PATH] " << get_ast_path() << std::endl;
        }
    }
}

void ChipsToXmiVisitor::visit(physical_named_output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_named_output_node)" << std::endl;
    std::cerr << "[DEBUG Visitor] Output name: " << node.get_identifier() << std::endl;
    
    // Récupérer les paramètres
    expressions_node* params = node.get_parameters();
    
    // Balise ouvrante <outputs avec attributs
    out() << "      <outputs\n";
    writeAttribute("          xsi:type", "chips.outputs.logical:int_output");
    out() << "\n";
    writeAttribute("          name", node.get_identifier());
    out() << ">\n";
    
    // Traiter les paramètres (expressions)
    if (params)
    {
        const auto& param_list = params->get_expressions();
        std::cerr << "[DEBUG Visitor] Nombre de paramètres: " << param_list.size() << std::endl;
        
        for (const auto& expr : param_list)
        {
            if (expr)
            {
                // Extraire la valeur/nom du paramètre
                std::string param_name = getExpressionValue(*expr);
                std::cerr << "[DEBUG Visitor] Paramètre: " << param_name << std::endl;
                
                // C'est probablement une variable, chercher dans la table des symboles
                std::string variable_path = get_ast_path_by_name(param_name);
                
                out() << "        <expression\n";
                writeAttribute("            xsi:type", "chips.xvalues.primitive:int_variable_expression");
                out() << "\n";
                writeAttribute("            variable", variable_path);
                out() << "/>\n";
            }
        }
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun paramètre pour l'output" << std::endl;
    }
    
    // Balise fermante
    out() << "      </outputs>\n";
}

void ChipsToXmiVisitor::visit(named_outputs_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(named_outputs_node)" << std::endl;
    out() << "      <!-- named_outputs_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(named_output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(named_output_node)" << std::endl;
    std::cerr << "[DEBUG Visitor] Output name: " << node.get_identifier() << std::endl;
    
    // Récupérer les paramètres
    expressions_node* params = node.get_parameters();
    
    // Balise ouvrante <outputs avec attributs
    out() << "      <outputs\n";
    writeAttribute("          xsi:type", "chips.outputs.logical:int_output");
    out() << "\n";
    writeAttribute("          name", node.get_identifier());
    out() << ">\n";
    
    // Traiter les paramètres (expressions)
    if (params)
    {
        const auto& param_list = params->get_expressions();
        std::cerr << "[DEBUG Visitor] Nombre de paramètres: " << param_list.size() << std::endl;
        
        for (const auto& expr : param_list)
        {
            if (expr)
            {
                // Extraire la valeur/nom du paramètre
                std::string param_name = getExpressionValue(*expr);
                std::cerr << "[DEBUG Visitor] Paramètre: " << param_name << std::endl;
                
                // C'est probablement une variable, chercher dans la table des symboles
                std::string variable_path = get_ast_path_by_name(param_name);
                
                out() << "        <expression\n";
                writeAttribute("            xsi:type", "chips.xvalues.primitive:int_variable_expression");
                out() << "\n";
                writeAttribute("            variable", variable_path);
                out() << "/>\n";
            }
        }
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun paramètre pour l'output" << std::endl;
    }
    
    // Balise fermante
    out() << "      </outputs>\n";
}

void ChipsToXmiVisitor::visit(actuator_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(actuator_node)" << std::endl;
    out() << "      <!-- actuator_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(statements_node)" << std::endl;
    out() << "      <!-- statements_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(rhs_assignment_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(rhs_assignment_node)" << std::endl;
    out() << "      <!-- rhs_assignment_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(assignment_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(assignment_node)" << std::endl;
    out() << "      <!-- assignment_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(this_attribute_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(this_attribute_node)" << std::endl;
    out() << "      <!-- this_attribute_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(function_call_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(function_call_statement_node)" << std::endl;
    out() << "      <!-- function_call_statement_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(if_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(if_node)" << std::endl;
    out() << "      <!-- if_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(if_else_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(if_else_node)" << std::endl;
    
    out() << "        <statements\n";
    writeAttribute("            xsi:type", "chips.statements.primitive:if_else");
    out() << ">\n";
    
    // Condition
    if (auto if_part = node.get_if_node())
    {
        if (auto cond = if_part->get_condition())
        {
            std::cerr << "[DEBUG Visitor] if_else: traitement de la condition" << std::endl;
            std::string cond_var_name = getExpressionValue(*cond);
            std::string cond_var_path = get_ast_path_by_name(cond_var_name);
            
            out() << "          <condition\n";
            writeAttribute("              xsi:type", "chips.xvalues.primitive:bool_variable_expression");
            out() << "\n";
            writeAttribute("              variable", cond_var_path);
            out() << "/>\n";
        }
        
        // Section if
        out() << "          <if_section>\n";
        if (auto if_stmts = if_part->get_statements())
        {
            std::cerr << "[DEBUG Visitor] if_else: traitement if_section" << std::endl;
            // Changer le tag pour if_statements
            std::string old_tag = m_statement_tag;
            m_statement_tag = "if_statements";
            
            int index = 0;
            for (auto &st : if_stmts->get_statements())
            {
                if (st)
                {
                    std::string segment = "/@if_statements." + std::to_string(index++);
                    push_ast_path(segment);
                    st->accept(*this);
                    pop_ast_path(segment);
                }
            }
            
            // Restaurer le tag
            m_statement_tag = old_tag;
        }
        out() << "          </if_section>\n";
    }
    
    // Section else
    out() << "          <else_section>\n";
    if (auto else_stmts = node.get_else_node())
    {
        std::cerr << "[DEBUG Visitor] if_else: traitement else_section" << std::endl;
        // Changer le tag pour else_statements
        std::string old_tag = m_statement_tag;
        m_statement_tag = "else_statements";
        
        int index = 0;
        for (auto &st : else_stmts->get_statements())
        {
            if (st)
            {
                std::string segment = "/@else_statements." + std::to_string(index++);
                push_ast_path(segment);
                st->accept(*this);
                pop_ast_path(segment);
            }
        }
        
        // Restaurer le tag
        m_statement_tag = old_tag;
    }
    out() << "          </else_section>\n";
    
    out() << "        </statements>\n";
}

void ChipsToXmiVisitor::visit(loop_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(loop_node)" << std::endl;
    out() << "      <!-- loop_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(block_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(block_node)" << std::endl;
    out() << "      <!-- block_node TODO -->\n";
    (void)node;
}


void ChipsToXmiVisitor::visit(statement_node &node) {
    std::cerr << "[DEBUG Visitor] visit(statement_node) - classe abstraite" << std::endl;
    // Dispatch vers les sous-classes concrètes
    if (auto df = dynamic_cast<dataflow_full_declaration_node *>(&node)) {
        std::cerr << "--> [Dispatch] dataflow_full_declaration_node détecté" << std::endl;
        df->accept(*this);
    } else if (auto var_assign = dynamic_cast<variable_assignment_node *>(&node)) {
        std::cerr << "--> [Dispatch] variable_assignment_node détecté" << std::endl;
        var_assign->accept(*this);
    } else if (auto ctx_assign = dynamic_cast<context_variable_assignment_node *>(&node)) {
        std::cerr << "--> [Dispatch] context_variable_assignment_node détecté" << std::endl;
        ctx_assign->accept(*this);
    } else {
        out() << "    <!-- statement_node type inconnu -->\n";
    }
}

void ChipsToXmiVisitor::visit(dataflow_full_declaration_node &node) {
    std::cerr << "[DEBUG Visitor] visit(dataflow_full_declaration_node) name=" 
              << node.get_identifier() << std::endl;
    
    std::string type = node.get_privitve_type();
    std::string name = node.get_identifier();
    
    out() << "        <" << m_statement_tag << "\n";
    writeAttribute("xsi:type", "chips.statements.primitive:" + type + "_declaration");
    out() << ">\n";
    
    std::string segment = "/@variable";
    push_ast_path(segment);
    register_variable(name, get_ast_path());
    std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;
    
    out() << "          <variable\n";
    writeAttribute("            name", name);
    out() << "/>\n";
    out() << "        </" << m_statement_tag << ">\n";
    
    // Traiter l'assignation si elle existe (même pour 0/false)
    if (auto rhs = node.get_rhs()) {
        if (auto rhs_expr = rhs->get_rhs()) {
            std::string rhs_value = getExpressionValue(*rhs_expr);
            out() << "        <" << m_statement_tag << "\n";
            writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
            out() << ">\n";
            out() << "          <lvalue\n";
            writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
            out() << "\n";
            writeAttribute("            variable", get_ast_path());
            out() << "/>\n";
            out() << "          <rvalue\n";
            writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
            std::cerr << "[Debug] value ?????????????? " << rhs_value << std::endl;
            if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false") {
                out() << "\n";
                writeAttribute("            value", rhs_value);
            }
            out() << "/>\n";
            out() << "        </" << m_statement_tag << ">\n";
        }
    }
    
    pop_ast_path(segment);
}

void ChipsToXmiVisitor::visit(variable_assignment_node &node) {
    std::cerr << "[DEBUG Visitor] visit(variable_assignment_node) identifier=" 
              << node.get_identifier() << std::endl;
    
    std::string name = node.get_identifier();
    std::string path = get_ast_path_by_name(name);
    std::cerr << "[DEBUG] Variable path: " << path << std::endl;
    
    if (auto expr = node.get_expression()) {
        std::cerr << "[DEBUG] Expression trouvée" << std::endl;
        
        // Vérifier le type d'expression
        if (auto bin_expr = dynamic_cast<binary_expression_node *>(expr)) {
            std::cerr << "[DEBUG] --> Expression binaire détectée!" << std::endl;
        } else if (auto num = dynamic_cast<number_literal_node *>(expr)) {
            std::cerr << "[DEBUG] --> Number literal détecté: " << num->get_int() << std::endl;
        } else if (auto var = dynamic_cast<variable_node *>(expr)) {
            std::cerr << "[DEBUG] --> Variable node détecté" << std::endl;
        } else if (auto suf = dynamic_cast<suffixised_node *>(expr)) {
            std::cerr << "[DEBUG] --> Suffixised node détecté: " << suf->get_identifier() << std::endl;
        } else {
            std::cerr << "[DEBUG] --> Type d'expression inconnu" << std::endl;
        }
        
        std::string value = getExpressionValue(*expr);
        std::cerr << "[DEBUG] Assignment value: " << value << std::endl;
        
        // Déterminer le type de l'expression
        std::string type = "int"; // Default
        if (auto num = dynamic_cast<number_literal_node *>(expr)) {
            type = num->get_type() == FLOAT_EXP ? "float" : 
                   num->get_type() == BOOL_EXP ? "bool" : "int";
        }
        
        out() << "        <" << m_statement_tag << "\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", path);
        out() << "/>\n";
        
        // Traiter la rvalue
        if (auto bin_expr = dynamic_cast<binary_expression_node *>(expr)) {
            std::cerr << "[DEBUG] Génération de la rvalue binaire" << std::endl;
            EXPRESSION_TYPE op_type = bin_expr->get_type();
            
            std::string op_name;
            switch (op_type) {
                case PLUS_EXP:
                    op_name = "plus";
                    std::cerr << "[DEBUG] Opérateur: addition (+)" << std::endl;
                    break;
                case MINUS_EXP:
                    op_name = "minus";
                    std::cerr << "[DEBUG] Opérateur: soustraction (-)" << std::endl;
                    break;
                case TIMES_EXP:
                    op_name = "times";
                    std::cerr << "[DEBUG] Opérateur: multiplication (*)" << std::endl;
                    break;
                case DIV_EXP:
                    op_name = "divide";
                    std::cerr << "[DEBUG] Opérateur: division (/)" << std::endl;
                    break;
                case MOD_EXP:
                    op_name = "modulo";
                    std::cerr << "[DEBUG] Opérateur: modulo (%)" << std::endl;
                    break;
                default:
                    op_name = "plus"; // Default
                    std::cerr << "[DEBUG] Opérateur: inconnu, utilisant plus par défaut" << std::endl;
            }
            
            out() << "          <rvalue\n";
            writeAttribute("            xsi:type", "chips.rvalues.primitive.operators.int:" + op_name);
            out() << ">\n";
            
            // Opérande gauche
            if (auto left = bin_expr->get_lhs()) {
                std::cerr << "[DEBUG] Traitement de l'opérande gauche" << std::endl;
                std::string left_value = getExpressionValue(*left);
                std::cerr << "[DEBUG] Valeur gauche: " << left_value << std::endl;
                
                out() << "            <left_operand\n";
                writeAttribute("              xsi:type", "chips.xvalues.primitive:int_variable_expression");
                out() << "\n";
                // Chercher le chemin si c'est une variable
                std::string left_path = get_ast_path_by_name(left_value);
                writeAttribute("              variable", left_path);
                out() << "/>\n";
            }
            
            // Opérande droite
            if (auto right = bin_expr->get_rhs()) {
                std::cerr << "[DEBUG] Traitement de l'opérande droite" << std::endl;
                std::string right_value = getExpressionValue(*right);
                std::cerr << "[DEBUG] Valeur droite: " << right_value << std::endl;
                
                out() << "            <right_operand\n";
                writeAttribute("              xsi:type", "chips.xvalues.primitive:int_variable_expression");
                out() << "\n";
                // Chercher le chemin si c'est une variable
                std::string right_path = get_ast_path_by_name(right_value);
                writeAttribute("              variable", right_path);
                out() << "/>\n";
            }
            
            out() << "          </rvalue>\n";
        } else {
            // Rvalue simple (nombre, variable)
            out() << "          <rvalue\n";
            writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
            std::cerr << "[Debug] value: " << value << std::endl;
            if (value != "0" && value != "0.0" && value != "false") {
                out() << "\n";
                writeAttribute("            value", value);
            }
            out() << "/>\n";
        }
        
        out() << "        </" << m_statement_tag << ">\n";
    }
}

void ChipsToXmiVisitor::visit(context_variable_assignment_node &node) {
    std::cerr << "[DEBUG Visitor] visit(context_variable_assignment_node) identifier=" 
              << node.get_identifier() << std::endl;
    
    std::string name = node.get_identifier();
    std::string path = get_ast_path_by_name(name);
    
    if (auto expr = node.get_expression()) {
        std::string value = getExpressionValue(*expr);
        std::cerr << "[DEBUG] Context assignment value: " << value << std::endl;
        
        std::string type = "int"; // Default
        if (auto num = dynamic_cast<number_literal_node *>(expr)) {
            type = num->get_type() == FLOAT_EXP ? "float" : 
                   num->get_type() == BOOL_EXP ? "bool" : "int";
        }
        
        out() << "        <" << m_statement_tag << "\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", path);
        out() << "/>\n";
        out() << "          <rvalue\n";
        writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
        std::cerr << "[Debug] value ?????????????? " << value << std::endl;
        if (value != "0" && value != "0.0" && value != "false") {
            out() << "\n";
            writeAttribute("            value", value);
        }
        out() << "/>\n";
        out() << "        </" << m_statement_tag << ">\n";
    }
}

// === EXPRESSIONS ===

void ChipsToXmiVisitor::visit(expression_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(expression_node)" << std::endl;
    out() << "    <!-- expression_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(suffixable_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(suffixable_node)" << std::endl;
    out() << "    <!-- suffixable_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(binary_expression_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(binary_expression_node)" << std::endl;
    out() << "    <!-- binary_expression_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(unary_expression_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(unary_expression_node)" << std::endl;
    out() << "    <!-- unary_expression_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(number_literal_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(number_literal_node)" << std::endl;
    out() << "    <!-- number_literal_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(function_call_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(function_call_node)" << std::endl;
    out() << "    <!-- function_call_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(variable_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(variable_node)" << std::endl;
    out() << "    <!-- variable_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(plugging_expr_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(plugging_expr_node)" << std::endl;
    out() << "    <!-- plugging_expr_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_cast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_cast_node)" << std::endl;
    out() << "    <!-- collective_cast_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_operation_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_operation_node)" << std::endl;
    out() << "    <!-- collective_operation_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(object_virtual_output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(object_virtual_output_node)" << std::endl;
    out() << "    <!-- object_virtual_output_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(object_physical_attribute_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(object_physical_attribute_node)" << std::endl;
    out() << "    <!-- object_physical_attribute_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(cast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(cast_node)" << std::endl;
    out() << "    <!-- cast_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(stop_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(stop_node)" << std::endl;
    out() << "    <!-- stop_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(input_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(input_node)" << std::endl;
    out() << "    <!-- input_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_cast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_cast_node)" << std::endl;
    out() << "    <!-- c_cast_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(context_expression_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(context_expression_node)" << std::endl;
    out() << "    <!-- context_expression_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(integrated_function_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(integrated_function_node)" << std::endl;
    out() << "    <!-- integrated_function_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(context_decl_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(context_decl_node)" << std::endl;
    out() << "    <!-- context_decl_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(suffixes_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(suffixes_node)" << std::endl;
    out() << "    <!-- suffixes_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(suffixised_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(suffixised_node)" << std::endl;
    out() << "    <!-- suffixised_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(paren_expression_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(paren_expression_node)" << std::endl;
    out() << "    <!-- paren_expression_node TODO -->\n";
}

// === COLLECTIVE / CONFIGURATION HELPERS ===

void ChipsToXmiVisitor::visit(c_keywords_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_keywords_node)" << std::endl;
    out() << "    <!-- c_keywords_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(spread_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(spread_node)" << std::endl;
    out() << "    <!-- spread_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collect_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collect_node)" << std::endl;
    out() << "    <!-- collect_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_statements_node)" << std::endl;
    out() << "    <!-- c_statements_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_statement_node)" << std::endl;
    out() << "    <!-- c_statement_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_loop_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_loop_node)" << std::endl;
    out() << "    <!-- c_loop_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_if_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_if_node)" << std::endl;
    out() << "    <!-- c_if_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_if_else_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_if_else_node)" << std::endl;
    out() << "    <!-- c_if_else_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_expressions_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_expressions_node)" << std::endl;
    out() << "    <!-- c_expressions_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_output_node)" << std::endl;
    out() << "    <!-- c_output_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_optionnal_outputs_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_optionnal_outputs_node)" << std::endl;
    out() << "    <!-- c_optionnal_outputs_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_dataflow_defaulted_decls_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_dataflow_defaulted_decls_node)" << std::endl;
    out() << "    <!-- collective_dataflow_defaulted_decls_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_dataflow_defaulted_decl_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_dataflow_defaulted_decl_node)" << std::endl;
    out() << "    <!-- collective_dataflow_defaulted_decl_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_dataflow_full_declaration_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_dataflow_full_declaration_node)" << std::endl;
    out() << "    <!-- collective_dataflow_full_declaration_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(collective_rhs_assignment_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(collective_rhs_assignment_node)" << std::endl;
    out() << "    <!-- collective_rhs_assignment_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_variable_assignment_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_variable_assignment_node)" << std::endl;
    out() << "    <!-- c_variable_assignment_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(c_context_variable_assignment_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(c_context_variable_assignment_node)" << std::endl;
    out() << "    <!-- c_context_variable_assignment_node TODO -->\n";
    (void)node;
}

// === DATAFLOW TYPES & PARAMETERS ===

void ChipsToXmiVisitor::visit(dataflow_type_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(dataflow_type_node)" << std::endl;
    out() << "    <!-- dataflow_type_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(physical_dataflow_parameter_type_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_type_node)" << std::endl;
    out() << "    <!-- physical_dataflow_parameter_type_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(expressions_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(expressions_node)" << std::endl;
    out() << "    <!-- expressions_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(dataflow_parameter_list_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_list_node)" << std::endl;
    out() << "    <!-- dataflow_parameter_list_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(physical_dataflow_parameter_list_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_list_node)" << std::endl;
    out() << "    <!-- physical_dataflow_parameter_list_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(dataflow_parameter_decls_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_decls_node)" << std::endl;
    out() << "    <!-- dataflow_parameter_decls_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(physical_dataflow_parameter_decls_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_decls_node)" << std::endl;
    out() << "    <!-- physical_dataflow_parameter_decls_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(dataflow_parameter_decl_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(dataflow_parameter_decl_node)" << std::endl;
    out() << "    <!-- dataflow_parameter_decl_node TODO -->\n";
    (void)node;
}

void ChipsToXmiVisitor::visit(physical_dataflow_parameter_decl_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_dataflow_parameter_decl_node)" << std::endl;
    out() << "    <!-- physical_dataflow_parameter_decl_node TODO -->\n";
    (void)node;
}

// === FALLBACK ===

void ChipsToXmiVisitor::visit(ast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // TODO : comprendre pourquoi on arrive ici après un noeud with
    out() << "    <!-- ast_node générique -->\n";
}

// === HELPERS ===

void ChipsToXmiVisitor::writeAttribute(const std::string &name, const std::string &value)
{
    if (name == "xsi:type")
    {
        std::string ns = value.substr(0, value.find(':'));
        std::string url = "http://chips." + ns;
        // remplace les . par des /
        size_t dot_pos = ns.find('.');
        if (dot_pos != std::string::npos)
        {
            std::string ns_with_slash = ns;
            ns_with_slash.replace(dot_pos, 1, "/");
            url.replace(7, ns.length(), ns_with_slash);
        }
        m_writer.add_namespace_if_needed(ns, url);
    }
    out() << " " << name << "=\"" << value << "\"";
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

std::string ChipsToXmiVisitor::get_ast_path_by_name(const std::string &name)
{
    // Rechercher dans la table des symboles
    auto it = m_symbol_table.find(name);
    if (it != m_symbol_table.end())
    {
        std::cerr << ">>>>>>>>>[DEBUG PATH] Variable '" << name << "' trouvée dans la table des symboles: " << it->second << std::endl;
        return it->second;
    }
    
    std::cerr << ">>>>>>>>>[WARNING] Variable '" << name << "' NON trouvée dans la table des symboles" << std::endl;
    report_semantic_error("Undefined variable: " + name);
    return name;  // Fallback: retourner juste le nom
}

void ChipsToXmiVisitor::report_semantic_error(const std::string &message)
{
    std::string detail = message;
    if (!m_current_ast_path.empty()) {
        detail += " (path: " + m_current_ast_path + ")";
    }
    m_semantic_errors.push_back(detail);
    std::cerr << "[SEMANTIC ERROR] " << detail << std::endl;
}