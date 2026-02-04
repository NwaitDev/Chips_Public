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

    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:object_definition");
    writeAttribute("name", node.get_identifier());
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

    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:logical_definition");
    writeAttribute("name", node.get_identifier());
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

    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:physical_definition");
    writeAttribute("name", node.get_identifier());
    out() << ">\n";

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

    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:implementation_definition");
    writeAttribute("name", node.get_ident1());
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
    std::string type = "chips.statements.node:chanel_declaration";

    out() << "        <statements\n";
    writeAttribute("          xsi:type", type);
    out() << "\n";
    writeAttribute("          name", name);
    out() << "\n";
    writeAttribute("          type_identifier", type_identifier);
    out() << ">\n";
    out() << "        </statements>\n";
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
    writeAttribute("        type_identifier", name);
    out() << " >\n          <variable>\n            <variable";
    writeAttribute("name", name);
    out() << "/>\n          </variable>\n";
    if (rhs_value != "0" && rhs_value != "0.0" && rhs_value != "false" && rhs_value != "unknown")
    {
        out() << "        </statements>\n        <statements\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type_primitive + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type_primitive + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", get_ast_path());
        out() << "/>\n";
        out() << "          <rvalue\n";
        writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type_primitive);
        out() << "\n";
        writeAttribute("            value", rhs_value);
        out() << "/>\n";
    }
    out() << "        </statements>\n";
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
    out() << "      <outputs\n";
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
    out() << "      </outputs>\n";
}

void ChipsToXmiVisitor::visit(physical_named_output_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(physical_named_output_node)" << std::endl;
    std::cerr << "[DEBUG Visitor] Output name: " << node.get_identifier() << std::endl;
    
    // Récupérer les paramètres
    expressions_node* params = node.get_parameters();
    
    writeAttribute("        xsi:type", "chips.outputs.logical:int_output");
    out() << "\n";
    writeAttribute("        name", node.get_identifier());
    out() << " >\n";
    
    // Traiter les paramètres
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
                
                // Vérifier si c'est un littéral (true, false, nombre, etc.)
                bool is_literal = false;
                std::string variable_path = param_name;
                
                if (auto num = dynamic_cast<number_literal_node *>(expr.get())) {
                    is_literal = true;
                    // Pour les littéraux, on utilise directement la valeur
                    variable_path = param_name;
                } else if (param_name == "true" || param_name == "false") {
                    is_literal = true;
                    variable_path = param_name;
                } else {
                    // C'est probablement une variable, chercher dans la table des symboles
                    variable_path = get_ast_path_by_name(param_name);
                }
                
                out() << "      <expression\n";
                writeAttribute("          xsi:type", "chips.xvalues.primitive:int_variable_expression");
                out() << "\n";
                writeAttribute("          variable", variable_path);
                out() << "/>\n";
            }
        }
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun paramètre pour l'output" << std::endl;
    }
    
    out() << "      </output>\n";
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
    out() << "      <!-- named_output_node TODO -->\n";
    (void)node;
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
    out() << "      <!-- if_else_node TODO -->\n";
    (void)node;
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
        df->accept(*this);
    } else if (auto var_assign = dynamic_cast<variable_assignment_node *>(&node)) {
        var_assign->accept(*this);
    } else if (auto ctx_assign = dynamic_cast<context_variable_assignment_node *>(&node)) {
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
    
    out() << "        <statements";
    writeAttribute("xsi:type", "chips.statements.primitive:" + type + "_declaration");
    out() << ">\n";
    
    std::string segment = "/@variable";
    push_ast_path(segment);
    register_variable(name, get_ast_path());
    std::cerr << "[DEBUG] Variable '" << name << "' enregistrée avec le chemin: " << get_ast_path() << std::endl;
    
    out() << "          <variable\n";
    writeAttribute("            name", name);
    out() << "/>\n";
    out() << "        </statements>\n";
    
    // Traiter l'assignation si elle existe (même pour 0/false)
    if (auto rhs = node.get_rhs()) {
        if (auto rhs_expr = rhs->get_rhs()) {
            std::string rhs_value = getExpressionValue(*rhs_expr);
            out() << "        <statements\n";
            writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
            out() << ">\n";
            out() << "          <lvalue\n";
            writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
            out() << "\n";
            writeAttribute("            variable", get_ast_path());
            out() << "/>\n";
            out() << "          <rvalue\n";
            writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
            out() << "\n";
            writeAttribute("            value", rhs_value);
            out() << "/>\n";
            out() << "        </statements>\n";
        }
    }
    
    pop_ast_path(segment);
}

void ChipsToXmiVisitor::visit(variable_assignment_node &node) {
    std::cerr << "[DEBUG Visitor] visit(variable_assignment_node) identifier=" 
              << node.get_identifier() << std::endl;
    
    std::string name = node.get_identifier();
    std::string path = get_ast_path_by_name(name);
    
    if (auto expr = node.get_expression()) {
        std::string value = getExpressionValue(*expr);
        std::cerr << "[DEBUG] Assignment value: " << value << std::endl;
        
        // Déterminer le type de l'expression
        std::string type = "int"; // Default
        if (auto num = dynamic_cast<number_literal_node *>(expr)) {
            type = num->get_type() == FLOAT_EXP ? "float" : 
                   num->get_type() == BOOL_EXP ? "bool" : "int";
        }
        
        out() << "        <statements\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", path);
        out() << "/>\n";
        out() << "          <rvalue\n";
        writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
        out() << "\n";
        writeAttribute("            value", value);
        out() << "/>\n";
        out() << "        </statements>\n";
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
        
        out() << "        <statements\n";
        writeAttribute("        xsi:type", "chips.statements.primitive:" + type + "_assignment");
        out() << ">\n";
        out() << "          <lvalue\n";
        writeAttribute("            xsi:type", "chips.xvalues.primitive:" + type + "_variable_expression");
        out() << "\n";
        writeAttribute("            variable", path);
        out() << "/>\n";
        out() << "          <rvalue\n";
        writeAttribute("            xsi:type", "chips.rvalues.primitive:direct_" + type);
        out() << "\n";
        writeAttribute("            value", value);
        out() << "/>\n";
        out() << "        </statements>\n";
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
    // Essayer number_literal_node
    if (auto num = dynamic_cast<number_literal_node *>(&expr))
    {
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
        return suf->get_identifier();
    }
    // Essayer function_call_node
    else if (auto fcall = dynamic_cast<function_call_node *>(&expr))
    {
        return fcall->get_identifier() + "()";
    }
    // Essayer variable_node
    else if (auto var = dynamic_cast<variable_node *>(&expr))
    {
        return var->get_identifier();
    }

    // Fallback
    return "unknown";
}

std::string ChipsToXmiVisitor::get_ast_path_by_name(const std::string &name)
{
    // Rechercher dans la table des symboles
    auto it = m_symbol_table.find(name);
    if (it != m_symbol_table.end())
    {
        std::cerr << "[DEBUG] Variable '" << name << "' trouvée dans la table des symboles: " << it->second << std::endl;
        return it->second;
    }
    
    std::cerr << "[WARNING] Variable '" << name << "' NON trouvée dans la table des symboles" << std::endl;
    return name;  // Fallback: retourner juste le nom
}