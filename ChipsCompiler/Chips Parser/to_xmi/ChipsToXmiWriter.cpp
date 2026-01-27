#include "ChipsToXmiWriter.hpp"

ChipsToXmiWriter::ChipsToXmiWriter(std::ostream& out, 
                                   std::string xmi_version, 
                                   std::string xmi_url)
    : m_out(out), 
      m_xmiVersion(xmi_version), 
      m_xmiUrl(xmi_url),
      m_idCounter(0) 
{}

// ============================================================================
// HEADER / FOOTER
// ============================================================================

void ChipsToXmiWriter::xmi_header(const std::string& filename)
{
    m_out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    m_out << "<chips:program xmi:version=\"" << m_xmiVersion << "\"\n";
    m_out << "    xmlns:xmi=\"" << m_xmiUrl << "\"\n";
    m_out << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
    m_out << "    xmlns:chips=\"http://chips\"\n";
    m_out << "    xmlns:definitions=\"http://chips/definitions\"\n";
    m_out << "    xmlns:chips.statements.system=\"http://chips/statements/system\"\n";
    m_out << "    xmlns:chips.statements.node=\"http://chips/statements/node\"\n";
    m_out << "    xmlns:chips.expressions=\"http://chips/expressions\"\n";
    
    if (!filename.empty()) {
        m_out << "    fileName=\"" << filename << "\"\n";
    }
    
    m_out << ">\n\n";
}

void ChipsToXmiWriter::xmi_footer()
{
    m_out << "\n</chips:program>\n";
}

// ============================================================================
// CONVERSION PRINCIPALE
// ============================================================================

void ChipsToXmiWriter::chips_to_xmi(const chips_node* root)
{
    m_idCounter = 0;
    m_nodeToId.clear();

    if (!root) {
        std::cerr << "Warning: Null root node\n";
        return;
    }

    // Preambles (physical/object definitions)
    if (root->get_preambles()) {
        preambles_to_xmi(root->get_preambles());
    }

    // System (declarations + links)
    if (root->get_system()) {
        system_to_xmi(root->get_system());
    }
}

// ============================================================================
// PREAMBLES (DEFINITIONS)
// ============================================================================

void ChipsToXmiWriter::preambles_to_xmi(const preambles_node* pres)
{
    m_out << "  <preamble>\n";
    
    for (const auto& preamble : pres->get_preamble_list()) {
        preamble_to_xmi(preamble.get());
    }
    
    m_out << "  </preamble>\n\n";
}

void ChipsToXmiWriter::preamble_to_xmi(const preamble_node* preamble)
{
    std::string id = nodeId(preamble);
    
    // Détection du type de preamble (physical, object, implementation, etc.)
    // Pour l'instant : générique
    m_out << "    <definitions xmi:id=\"" << id << "\" ";
    m_out << "xsi:type=\"definitions:physical_definition\">\n";
    
    // TODO: Ajouter contenu (name, parameters, with, init, then, outputs)
    
    m_out << "    </definitions>\n";
}

// ============================================================================
// SYSTEM
// ============================================================================

void ChipsToXmiWriter::system_to_xmi(const system_node* sys)
{
    if (!sys->get_system_statements()) {
        return;
    }

    m_out << "  <system>\n";
    
    s_statements_to_xmi(sys->get_system_statements());
    
    m_out << "  </system>\n\n";
}

void ChipsToXmiWriter::s_statements_to_xmi(const s_statements_node* statements)
{
    for (const auto& stmt : statements->get_statements()) {
        precise_system_node_to_xmi(stmt.get());
    }
}

void ChipsToXmiWriter::precise_system_node_to_xmi(const s_statement_node* node)
{
    std::string id = nodeId(node);
    
    switch (node->get_statement_type()) {
        case DF_INST_ST: {
            // Déclaration système (ex: PhysicalCounter pc)
            m_out << "    <declarations xmi:id=\"" << id << "\" ";
            m_out << "xsi:type=\"chips.statements.system:physical_declaration\"";
            // TODO: ajouter name, type_ref
            m_out << "/>\n";
            break;
        }
        
        case S_IMPLEMENTS_ST: {
            // Implémentation (ex: pc implements ao using abstractObjectByCounter)
            m_out << "    <statements xmi:id=\"" << id << "\" ";
            m_out << "xsi:type=\"chips.statements.system:implements_statement\"";
            // TODO: ajouter physical_node, abstract_node, implementation_ref
            m_out << "/>\n";
            break;
        }
        
        case S_LINK_ST: {
            // Lien (ex: pc.onOffButton <- bp.push)
            m_out << "    <statements xmi:id=\"" << id << "\" ";
            m_out << "xsi:type=\"chips.statements.system:feeding_physical_bool\"";
            // TODO: ajouter source, target
            m_out << "/>\n";
            break;
        }
        
        case LOOP_ST: {
            m_out << "    <statements xmi:id=\"" << id << "\" ";
            m_out << "xsi:type=\"chips.statements.system:loop_statement\"";
            m_out << "/>\n";
            break;
        }
        
        case IF_ST:
        case IFELSE_ST: {
            m_out << "    <statements xmi:id=\"" << id << "\" ";
            m_out << "xsi:type=\"chips.statements.system:if_statement\"";
            m_out << "/>\n";
            break;
        }
        
        default: {
            m_out << "    <!-- Unknown statement type -->\n";
            break;
        }
    }
}

// ============================================================================
// UTILITAIRES
// ============================================================================

std::string ChipsToXmiWriter::nextId(const std::string& prefix)
{
    return prefix + std::to_string(++m_idCounter);
}

std::string ChipsToXmiWriter::nodeId(const ast_node* node)
{
    auto it = m_nodeToId.find(node);
    if (it != m_nodeToId.end()) {
        return it->second;
    }
    
    std::string id = nextId("_");
    m_nodeToId[node] = id;
    return id;
}

void ChipsToXmiWriter::add_namespace_if_needed(const std::string& ns_prefix, 
                                               const std::string& url)
{
    if (m_used_namespaces.find(ns_prefix) == m_used_namespaces.end()) {
        m_used_namespaces.insert(ns_prefix);
        // Note: Les namespaces sont déjà dans xmi_header()
        // Dans une impl avancée, on pourrait dynamiquement les ajouter
    }
}
