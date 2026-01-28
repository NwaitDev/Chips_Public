#include "ChipsToXmiVisitor.hpp"

// === PROGRAM & CONTEXT ===
void ChipsToXmiVisitor::visit(chips_node &node)
{
    // Contenu après xmi_header() → directement les enfants
    if (auto pres = node.get_preambles())
    {
        pres->accept(*this);
    }
    if (auto sys = node.get_system())
    {
        sys->accept(*this);
    }
    // Fin gérée par Writer
}

void ChipsToXmiVisitor::visit(preambles_node &node)
{
    out() << "  <preamble>\n";
    for (auto &pre : node.get_preamble_list())
    {
        pre->accept(*this);
    }
    out() << "  </preamble>\n";
}

void ChipsToXmiVisitor::visit(preamble_node &node)
{
    // Ne rien générer ici - les sous-classes concrètes 
    // (object_definition, function_definition, etc.) 
    // généreront leurs propres balises <definitions>
    // via leurs visiteurs spécifiques
}

void ChipsToXmiVisitor::visit(system_node &node)
{
    // Parcourir les déclarations système
    if (auto statements = node.get_system_statements())
    {
        for (auto &st : statements->get_statements())
        {
            st->accept(*this);
        }
    }
}

// === SYSTEM STATEMENTS ===
void ChipsToXmiVisitor::visit(s_statements_node &node)
{
    for (auto &st : node.get_statements())
    {
        st->accept(*this);
    }
}

void ChipsToXmiVisitor::visit(const s_statements_node &node)
{
    for (auto &st : node.get_statements())
    {
        st->accept(*this);
    }
}

void ChipsToXmiVisitor::visit(s_statement_node &node)
{
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
        out() << "    <SStatement />\n";
    }
}

void ChipsToXmiVisitor::visit(implements_node &node)
{
    out() << "    <Implements />\n";
}

void ChipsToXmiVisitor::visit(link_node &node)
{
    out() << "    <Link />\n";
}

void ChipsToXmiVisitor::visit(plugging_node &node)
{
    out() << "    <Plugging />\n";
}

void ChipsToXmiVisitor::visit(s_loop_node &node)
{
    out() << "    <Loop />\n"; // TODO: ident1, ident2, statements
}

void ChipsToXmiVisitor::visit(s_if_node &node)
{
    out() << "    <If />\n"; // TODO: condition, statements
}

void ChipsToXmiVisitor::visit(s_if_else_node &node)
{
    out() << "    <IfElse />\n"; // TODO: if_node, else_statements
}

void ChipsToXmiVisitor::visit(functionnal_block_instanciation_node &node)
{
    out() << "    <FunctionalBlockInstanciation />\n"; // TODO: ident1, suffixes, ident2
}

// === DECLARATION CONTEXT ===
void ChipsToXmiVisitor::visit(object_definition_node &node)
{
    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:object_definition");
    writeAttribute("name", node.get_identifier());
    out() << ">\n";
    
    // Visiter la section "with" si elle existe
    if (auto with = node.get_with())
    {
        with->accept(*this);
    }
    
    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(function_definition_node &node)
{
    out() << "    <FunctionDefinition />\n";
}

void ChipsToXmiVisitor::visit(logical_function_definition_node &node)
{
    out() << "    <LogicalFunctionDefinition />\n";
}

void ChipsToXmiVisitor::visit(physical_function_definition_node &node)
{
    out() << "    <definitions";
    writeAttribute("xsi:type", "definitions:physical_definition");
    writeAttribute("name", node.get_identifier());
    out() << ">\n";
    
    // Visiter les sections (with, init, then, outputs, sensors)
    if (auto with = node.get_with())
        with->accept(*this);
    
    if (auto outputs = node.get_outputs())
        outputs->accept(*this);
        
    if (auto init = node.get_init())
        init->accept(*this);
        
    if (auto then = node.get_then())
        then->accept(*this);
    
    out() << "    </definitions>\n";
}

void ChipsToXmiVisitor::visit(collective_operation_definition_node &node)
{
    out() << "    <CollectiveOperationDefinition />\n";
}

void ChipsToXmiVisitor::visit(implementation_definition_node &node)
{
    out() << "    <ImplementationDefinition />\n";
}

void ChipsToXmiVisitor::visit(node_mappings_node &node)
{
    out() << "    <NodeMappings />\n";
}

void ChipsToXmiVisitor::visit(c_signature_node &node)
{
    out() << "    <CSignature />\n";
}

void ChipsToXmiVisitor::visit(output_node &node)
{
    out() << "    <Output />\n";
}

// === WITH / SECTIONS ===
void ChipsToXmiVisitor::visit(with_section_node &node)
{
    out() << "    <WithSection />\n";
}

void ChipsToXmiVisitor::visit(with_statements_node &node)
{
    for (auto &st : node.get_statements())
    {
        st->accept(*this);
    }
}

void ChipsToXmiVisitor::visit(with_statement_node &node)
{
    out() << "    <WithStatement />\n";
}

void ChipsToXmiVisitor::visit(with_two_identifier_node &node)
{
    out() << "    <WithTwoIdentifier />\n";
}

void ChipsToXmiVisitor::visit(with_context_statement_node &node)
{
    out() << "    <WithContextStatement />\n";
}

void ChipsToXmiVisitor::visit(init_section_node &node)
{
    out() << "    <InitSection />\n";
}

void ChipsToXmiVisitor::visit(then_section_node &node)
{
    out() << "    <ThenSection />\n";
}

// === EXPRESSIONS ===
void ChipsToXmiVisitor::visit(expression_node &node)
{
    out() << "    <Expression />\n";
}

void ChipsToXmiVisitor::visit(suffixable_node &node)
{
    out() << "    <Suffixable />\n";
}

void ChipsToXmiVisitor::visit(binary_expression_node &node)
{
    out() << "    <BinaryExpression />\n";
}

void ChipsToXmiVisitor::visit(unary_expression_node &node)
{
    out() << "    <UnaryExpression />\n";
}

void ChipsToXmiVisitor::visit(number_literal_node &node)
{
    out() << "    <NumberLiteral />\n";
}

void ChipsToXmiVisitor::visit(function_call_node &node)
{
    out() << "    <FunctionCall />\n";
}

void ChipsToXmiVisitor::visit(variable_node &node)
{
    out() << "    <Variable />\n";
}

void ChipsToXmiVisitor::visit(object_virtual_output_node &node)
{
    out() << "    <ObjectVirtualOutput />\n";
}

void ChipsToXmiVisitor::visit(object_physical_attribute_node &node)
{
    out() << "    <ObjectPhysicalAttribute />\n";
}

void ChipsToXmiVisitor::visit(cast_node &node)
{
    out() << "    <Cast />\n";
}

void ChipsToXmiVisitor::visit(suffixes_node &node)
{
    out() << "    <Suffixes />\n";
}

void ChipsToXmiVisitor::visit(suffixised_node &node)
{
    out() << "    <Suffixised />\n";
}

void ChipsToXmiVisitor::visit(paren_expression_node &node)
{
    out() << "    <ParenExpression />\n";
}

// === FALLBACK ===
void ChipsToXmiVisitor::visit(ast_node &node)
{
    out() << "    <GenericNode />\n";
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