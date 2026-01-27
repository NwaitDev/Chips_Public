#include "ChipsToXmiVisitor.hpp"
#include <iostream>

// === PROGRAM & CONTEXT ===

void ChipsToXmiVisitor::visit(chips_node &node)
{
    std::cerr << "\n[DEBUG Visitor] ========================================" << std::endl;
    std::cerr << "[DEBUG Visitor] visit(chips_node) DÉMARRÉ" << std::endl;
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

    int index = 0;
    for (auto &pre : node.get_preamble_list())
    {
        std::cerr << "[DEBUG Visitor] Traitement preamble #" << index++ << std::endl;
        if (pre) {
            pre->accept(*this);
        } else {
            std::cerr << "[WARNING Visitor] Preamble NULL à l'index " << (index-1) << std::endl;
        }
    }

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

    // Parcourir les déclarations système
    if (auto statements = node.get_system_statements())
    {
        std::cerr << "[DEBUG Visitor] System statements trouvé, " 
                  << statements->get_statements().size() << " statements" << std::endl;
        for (auto &st : statements->get_statements())
        {
            if (st) {
                st->accept(*this);
            }
        }
    }
    else
    {
        std::cerr << "[WARNING Visitor] Aucun system statements!" << std::endl;
    }

    out() << "  </system>\n";
}

// === SYSTEM STATEMENTS ===

void ChipsToXmiVisitor::visit(s_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(s_statements_node) appelé" << std::endl;
    for (auto &st : node.get_statements())
    {
        if (st) {
            st->accept(*this);
        }
    }
}

void ChipsToXmiVisitor::visit(const s_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(const s_statements_node) appelé" << std::endl;
    for (auto &st : node.get_statements())
    {
        if (st) {
            st->accept(*this);
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
            if (auto impl = dynamic_cast<implements_node*>(&node))
                impl->accept(*this);
            break;
        case S_LINK_ST:
            if (auto link = dynamic_cast<link_node*>(&node))
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
        with->accept(*this);
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

    // TODO: Visiter sections
    out() << "      <!-- TODO: init, then, outputs -->\n";

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

    // Visiter les sections (with, init, then, outputs, sensors)
    if (auto with = node.get_with()) {
        std::cerr << "[DEBUG Visitor] Physical a une section with" << std::endl;
        with->accept(*this);
    }

    if (auto outputs = node.get_outputs()) {
        std::cerr << "[DEBUG Visitor] Physical a des outputs" << std::endl;
        outputs->accept(*this);
    }

    if (auto init = node.get_init()) {
        std::cerr << "[DEBUG Visitor] Physical a une section init" << std::endl;
        init->accept(*this);
    }

    if (auto then = node.get_then()) {
        std::cerr << "[DEBUG Visitor] Physical a une section then" << std::endl;
        then->accept(*this);
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

    if (auto statements = node.get_statements()) {
        std::cerr << "[DEBUG Visitor] With section a des statements" << std::endl;
        statements->accept(*this);
    }

    out() << "      </with>\n";
}

void ChipsToXmiVisitor::visit(with_statements_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_statements_node) - " 
              << node.get_statements().size() << " statements" << std::endl;

    for (auto &st : node.get_statements())
    {
        if (st) {
            st->accept(*this);
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
    out() << "        <!-- with_two_identifier_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(with_context_statement_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(with_context_statement_node)" << std::endl;
    out() << "        <!-- with_context_statement_node TODO -->\n";
}

void ChipsToXmiVisitor::visit(init_section_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(init_section_node)" << std::endl;
    out() << "      <init>\n";
    out() << "        <!-- TODO: statements -->\n";
    out() << "      </init>\n";
}

void ChipsToXmiVisitor::visit(then_section_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(then_section_node)" << std::endl;
    out() << "      <then>\n";
    out() << "        <!-- TODO: statements -->\n";
    out() << "      </then>\n";
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

// === FALLBACK ===

void ChipsToXmiVisitor::visit(ast_node &node)
{
    std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    out() << "    <!-- ast_node générique -->\n";
}

// === HELPERS ===

void ChipsToXmiVisitor::writeAttribute(const std::string &name, const std::string &value)
{
    out() << " " << name << "=\"" << value << "\"";
}

void ChipsToXmiVisitor::endEmptyElement()
{
    out() << " />\n";
}
