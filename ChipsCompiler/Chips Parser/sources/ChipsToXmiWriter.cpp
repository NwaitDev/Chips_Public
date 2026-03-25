#include "ChipsToXmiWriter.hpp"
#include <iostream>

ChipsToXmiWriter::ChipsToXmiWriter(std::ostream& out,
                         std::string xmi_version,
                         std::string xmi_url,
                         std::string schema_version)
    : m_out(out),
      m_xmiVersion(xmi_version),
      m_xmiUrl(xmi_url),
    m_schemaVersion(schema_version),
      m_idCounter(0)
{}

// ============================================================================
// HEADER / FOOTER
// ============================================================================

void ChipsToXmiWriter::xmi_header(const std::string& filename)
{
    std::cerr << "[DEBUG Writer] xmi_header() appelé avec filename: " << filename << std::endl;

    m_out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    m_out << "<chips:program\n  xmi:version=\"" << m_xmiVersion << "\"\n";
    
    // Namespaces de base (toujours présents)
    m_out << "  xmlns:xmi=\"" << m_xmiUrl << "\"\n";
    m_out << "  xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
    m_out << "  xmlns:chips=\"http://chips\"\n";
    
    // Namespaces collectés dynamiquement (triés pour un ordre cohérent)
    std::map<std::string, std::string> sorted_ns(m_namespace_urls.begin(), m_namespace_urls.end());
    for (const auto& [prefix, url] : sorted_ns) {
        m_out << "  xmlns:" << prefix << "=\"" << url << "\"\n";
    }
    
    // xsi:schemaLocation (si des namespaces sont présents)
    if (!m_namespace_urls.empty()) {
        std::string schema_file = (m_schemaVersion.rfind("2", 0) == 0)
            ? "chips2.ecore"
            : "chips1.1.ecore";
        m_out << "  xsi:schemaLocation=\"http://chips " << schema_file;
        
        for (const auto& [prefix, url] : sorted_ns) {
            // Cas spéciaux pour dataflow qui doivent pointer vers system
            std::string schema_fragment;
            if (url == "http://chips/rvalues/dataflow/operators/bool") {
                schema_fragment = "#//rvalues/system/operators/bool";
            } else if (url == "http://chips/rvalues/dataflow/operators/int") {
                schema_fragment = "#//rvalues/system/operators/int";
            } else if (url == "http://chips/rvalues/dataflow/operators/float") {
                schema_fragment = "#//rvalues/system/operators/float";
            } else {
                // Mapping par défaut : extraire le fragment après "http://chips"
                std::string fragment = url.substr(std::string("http://chips").length());
                
                if (!fragment.empty()) {
                    schema_fragment = "#/" + fragment;
                } else {
                    // Pour "definitions" qui n'a pas de sous-chemin
                    schema_fragment = "#//" + prefix;
                }
            }
            
            m_out << "\n                      " << url << " " << schema_file << schema_fragment;
        }
        m_out << "\"\n";
    }
    
    m_out << "  fileName=\"" << filename << "\"";
    m_out << ">\n";
}

void ChipsToXmiWriter::xmi_footer()
{
    std::cerr << "[DEBUG Writer] xmi_footer() appelé" << std::endl;
    m_out << "</chips:program>\n";
}

void ChipsToXmiWriter::copy_namespaces_from(ChipsToXmiWriter& other)
{
    m_used_namespaces = other.m_used_namespaces;
    m_namespace_urls = other.m_namespace_urls;
}

// ============================================================================
// CONVERSION PRINCIPALE
// ============================================================================

void ChipsToXmiWriter::chips_to_xmi(program_node* root)
{
    std::cerr << "\n[DEBUG Writer] ========================================" << std::endl;
    std::cerr << "[DEBUG Writer] chips_to_xmi() DÉMARRÉ" << std::endl;
    std::cerr << "[DEBUG Writer] ========================================" << std::endl;

    m_idCounter = 0;
    m_nodeToId.clear();

    if (!root) {
        std::cerr << "[ERROR Writer] Root node est NULL!" << std::endl;
        return;
    }

    std::cerr << "[DEBUG Writer] Root node valide" << std::endl;

    // Rest of this function commented because outdated relatively to the new and more robust AST data structure

    // Preambles (physical/object definitions)
    // if (root->m_preamble) {
    //     std::cerr << "[DEBUG Writer] Preambles trouvé, appel preambles_to_xmi()" << std::endl;
    //     preambles_to_xmi(root->get_preamble());
    // } else {
    //     std::cerr << "[WARNING Writer] Aucun preambles dans le root!" << std::endl;
    // }
    

    // System (declarations + links)
    // if (root->get_system()) {
    //     std::cerr << "[DEBUG Writer] System trouvé, appel system_to_xmi()" << std::endl;
    //     system_to_xmi(root->get_system());
    // } else {
    //     std::cerr << "[WARNING Writer] Aucun system dans le root!" << std::endl;
    // }

    std::cerr << "[DEBUG Writer] chips_to_xmi() TERMINÉ" << std::endl;
}

// ============================================================================
// PREAMBLES (DEFINITIONS)
// ============================================================================

void ChipsToXmiWriter::preambles_to_xmi(preamble_section_node* pres)
{
    std::cerr << "[DEBUG Writer] preambles_to_xmi() appelé" << std::endl;

    if (!pres) {
        std::cerr << "[ERROR Writer] preamble_section_node est NULL!" << std::endl;
        return;
    }

    const auto& list = pres->m_definitions;
    std::cerr << "[DEBUG Writer] Nombre de définitions: " << list.size() << std::endl;

    m_out << "  <preamble>\n";

    int index = 0;
    for (const auto& definition : list) {
        std::cerr << "[DEBUG Writer] Traitement preamble #" << index++ << std::endl;
        preamble_to_xmi(definition);
    }
    m_out << "  </preamble>\n\n";
}

void ChipsToXmiWriter::preamble_to_xmi(definition_variant definition)
{
    // Rest of this function commented because outdated relatively to the new and more robust AST data structure

    // std::visit([this](auto* def){
    //     std::cerr << "[DEBUG Writer] preamble_to_xmi() appelé" << std::endl;

    //     if (!def) {
    //         std::cerr << "[ERROR Writer] definition est NULL!" << std::endl;
    //         return;
    //     }

    //     std::string id = nodeId((def));

    //     // Essayer de détecter le type réel
    //     if (auto obj = dynamic_cast<object_definition*>(def)) {
    //         std::cerr << "[DEBUG Writer] Type détecté: object_definition" << std::endl;
    //         // auto obj = static_cast<object_definition*>(def);
    //         m_out << "    <definitions xsi:type=\"definitions:object_definition\" "
    //             << "name=\"" << obj->get_identifier() << "\" id=\"" << id << "\">\n";
    //         m_out << "      <!-- TODO: with section -->\n";
    //         m_out << "    </definitions>\n";
    //     }else if (auto func = dynamic_cast<function_definition*>(def)) {
    //         if(auto phys = dynamic_cast<physical_definition*>(func)){
    //             std::cerr << "[DEBUG Writer] Type détecté: physical_definition" << std::endl;
    //             m_out << "    <definitions xsi:type=\"definitions:physical_definition\" "
    //                 << "name=\"" << phys->function_definition::get_identifier() << "\" id=\"" << id << "\">\n";
    //             m_out << "      <!-- TODO: with, init, then, outputs -->\n";
    //             m_out << "    </definitions>\n";
    //         }else if(auto log = dynamic_cast<logical_definition*>(func)){
    //             std::cerr << "[DEBUG Writer] Type détecté: logical_definition" << std::endl;
    //             m_out << "    <definitions xsi:type=\"definitions:logical_definition\" "
    //                 << "name=\"" << log->get_identifier() << "\" id=\"" << id << "\">\n";
    //             m_out << "      <!-- TODO: init, then, outputs -->\n";
    //             m_out << "    </definitions>\n";
    //         }
    //     }else if (auto impl = dynamic_cast<implementation_defintion*>(def)) {
    //         std::cerr << "[DEBUG Writer] Type détecté: implementation_defintion" << std::endl;
    //         // auto impl = static_cast<implementation_defintion*>(def);
    //         m_out << "    <definitions xsi:type=\"definitions:implementation_definition\" "
    //             << "name=\"" << impl->get_identifier() << "\" id=\"" << id << "\">\n";
    //         m_out << "      <!-- TODO: implemented_object, implementing_node, having -->\n";
    //         m_out << "    </definitions>\n";
    //     }else {
    //         std::cerr << "[WARNING Writer] Type de preamble inconnu!" << std::endl;
    //         m_out << "    <definitions xsi:type=\"definitions:unknown\" id=\"" << id << "\">\n";
    //         m_out << "      <!-- Type inconnu -->\n";
    //         m_out << "    </definitions>\n";
    //     }
    // }, definition);
}

// ============================================================================
// SYSTEM
// ============================================================================

void ChipsToXmiWriter::system_to_xmi(system_section_node* sys)
{
//     std::cerr << "[DEBUG Writer] system_to_xmi() appelé" << std::endl;

//     if (!sys) {
//         std::cerr << "[ERROR Writer] system_section_node est NULL!" << std::endl;
//         return;
//     }

//     if (!sys->get_statements()) {
//         std::cerr << "[WARNING Writer] Aucun system_statements!" << std::endl;
//         return;
//     }

//     const auto& stmts = sys->get_statements();
//     std::cerr << "[DEBUG Writer] Nombre de system statements: " << stmts.size() << std::endl;

//     m_out << "  <system>\n";
//     s_statements_to_xmi(sys->get_statements());
//     m_out << "  </system>\n\n";
}

// void ChipsToXmiWriter::s_statements_to_xmi(const std::vector<system_statement_variant>* statements)
// {
//     std::cerr << "[DEBUG Writer] s_statements_to_xmi() appelé" << std::endl;

//     if (!statements) {
//         std::cerr << "[ERROR Writer] s_statements est NULL!" << std::endl;
//         return;
//     }

//     int index = 0;
//     for (const auto& stmt : statements->get_statements()) {
//         std::cerr << "[DEBUG Writer] Traitement statement #" << index++ << std::endl;
//         if (stmt) {
//             precise_system_section_node_to_xmi(stmt.get());
//         } else {
//             std::cerr << "[WARNING Writer] Statement NULL à l'index " << (index-1) << std::endl;
//         }
//     }
// }

// template<recurring_statement recstt>
// void ChipsToXmiWriter::precise_system_section_node_to_xmi(const system_statement<recstt>* node)
// {
//     std::cerr << "[DEBUG Writer] precise_system_section_node_to_xmi() appelé" << std::endl;

//     if (!node) {
//         std::cerr << "[ERROR Writer] s_statement est NULL!" << std::endl;
//         return;
//     }

//     std::string id = nodeId(node);
//     auto stmt_type = node->get_statement_type();

//     std::cerr << "[DEBUG Writer] Statement type: " << stmt_type << std::endl;

//     switch (stmt_type) {
//         case DF_INST_ST: {
//             std::cerr << "[DEBUG Writer] Type: DF_INST_ST (déclaration)" << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:declaration\" id=\"" << id << "\"/>\n";
//             break;
//         }
//         case S_IMPLEMENTS_ST: {
//             std::cerr << "[DEBUG Writer] Type: S_IMPLEMENTS_ST" << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:implements_statement\" id=\"" << id << "\"/>\n";
//             break;
//         }
//         case S_LINK_ST: {
//             std::cerr << "[DEBUG Writer] Type: S_LINK_ST (link/feeding)" << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:link\" id=\"" << id << "\"/>\n";
//             break;
//         }
//         case LOOP_ST: {
//             std::cerr << "[DEBUG Writer] Type: LOOP_ST" << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:loop\" id=\"" << id << "\"/>\n";
//             break;
//         }
//         case IF_ST:
//         case IFELSE_ST: {
//             std::cerr << "[DEBUG Writer] Type: IF/IFELSE_ST" << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:if\" id=\"" << id << "\"/>\n";
//             break;
//         }
//         default: {
//             std::cerr << "[WARNING Writer] Type de statement inconnu: " << stmt_type << std::endl;
//             m_out << "    <system xsi:type=\"chips.statements.system:unknown\" id=\"" << id << "\"/>\n";
//             break;
//         }
//     }
// }

// ============================================================================
// UTILITAIRES
// ============================================================================

std::string ChipsToXmiWriter::nextId(const std::string& prefix)
{
    return prefix + std::to_string(++m_idCounter);
}

std::string ChipsToXmiWriter::nodeId(ast_node* node)
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
    if (m_namespace_urls.find(ns_prefix) == m_namespace_urls.end()) {
        m_namespace_urls[ns_prefix] = url;
        m_used_namespaces.insert(ns_prefix);
    }
}

// ============================================================================
// COLLECTION DES NAMESPACES
// ============================================================================

void ChipsToXmiWriter::collect_namespaces(program_node* root)
{
    if (!root) return;
    
    // Parcourir les preambles
    collect_namespaces_from_preambles(&(root->m_preamble));
    
    // Parcourir le system
    collect_namespaces_from_system(&(root->m_system));
}

void ChipsToXmiWriter::collect_namespaces_from_preambles(preamble_section_node* pres)
{
    if (!pres) return;
    
    // Toujours ajouter le namespace definitions si on a des preambles
    add_namespace_if_needed("definitions", "http://chips/definitions");

    for(const auto& definition : pres->m_definitions){
        collect_namespaces_from_preamble(definition);
    }
}

void ChipsToXmiWriter::collect_namespaces_from_preamble(definition_variant definition)
{

    std::visit([this](auto* def){
        if(!def) return;

        if(auto func = dynamic_cast<const function_definition*>(def)){
            if (dynamic_cast<const physical_definition*>(func)) {
                add_namespace_if_needed("chips.statements.node", "http://chips/statements/node");
                add_namespace_if_needed("chips.statements.primitive", "http://chips/statements/primitive");
                add_namespace_if_needed("chips.outputs.logical", "http://chips/outputs/logical");
                add_namespace_if_needed("chips.outputs.physical", "http://chips/outputs/physical");
                add_namespace_if_needed("chips.parameters.physical", "http://chips/parameters/physical");
                add_namespace_if_needed("chips.xvalues.primitive", "http://chips/xvalues/primitive");
                add_namespace_if_needed("chips.rvalues.primitive", "http://chips/rvalues/primitive");
                add_namespace_if_needed("chips.rvalues.primitive.operators.int", "http://chips/rvalues/primitive/operators/int");
                // TODO: Ajouter d'autres namespaces selon le contenu réel
            }
            else if (dynamic_cast<const logical_definition*>(func)) {
                add_namespace_if_needed("chips.statements.primitive", "http://chips/statements/primitive");
                add_namespace_if_needed("chips.outputs.logical", "http://chips/outputs/logical");
                add_namespace_if_needed("chips.parameters.logical", "http://chips/parameters/logical");
                add_namespace_if_needed("chips.xvalues.primitive", "http://chips/xvalues/primitive");
                add_namespace_if_needed("chips.rvalues.primitive", "http://chips/rvalues/primitive");
                add_namespace_if_needed("chips.rvalues.primitive.operators.int", "http://chips/rvalues/primitive/operators/int");
            }
        }
        
        // En fonction du type de definition, ajouter les namespaces nécessaires
        
        else if (dynamic_cast<const object_definition*>(def)) {
            add_namespace_if_needed("chips.statements.node", "http://chips/statements/node");
        }else if (dynamic_cast<const implementation_defintion*>(def)) {
            add_namespace_if_needed("chips.statements.implementation", "http://chips/statements/implementation");
        }
        else if (dynamic_cast<const collective_function_definition*>(def)) {
            // Namespaces pour les opérations collectives
            add_namespace_if_needed("chips.parameters.collective", "http://chips/parameters/collective");
            add_namespace_if_needed("chips.parameters.logical", "http://chips/parameters/logical");
            add_namespace_if_needed("chips.rvalues.collective", "http://chips/rvalues/collective");
            add_namespace_if_needed("chips.rvalues.collective.operators.bool", "http://chips/rvalues/collective/operators/bool");
            add_namespace_if_needed("chips.rvalues.collective.operators.int", "http://chips/rvalues/collective/operators/int");
            add_namespace_if_needed("chips.rvalues.dataflow.operators.bool", "http://chips/rvalues/dataflow/operators/bool");
            add_namespace_if_needed("chips.rvalues.dataflow.operators.int", "http://chips/rvalues/dataflow/operators/int");
            add_namespace_if_needed("chips.rvalues.primitive", "http://chips/rvalues/primitive");
            add_namespace_if_needed("chips.rvalues.system", "http://chips/rvalues/system");
            add_namespace_if_needed("chips.statements.collective", "http://chips/statements/collective");
            add_namespace_if_needed("chips.statements.primitive", "http://chips/statements/primitive");
            add_namespace_if_needed("chips.xvalues.collective", "http://chips/xvalues/collective");
            add_namespace_if_needed("chips.xvalues.primitive", "http://chips/xvalues/primitive");
        }
    }, definition);
}

void ChipsToXmiWriter::collect_namespaces_from_system(system_section_node* sys)
{
//     if (!sys || !sys->get_system_statements()) return;
    
//     // Toujours ajouter le namespace system si on a des statements
//     add_namespace_if_needed("chips.statements.system", "http://chips/statements/system");
    
//     for (const auto& stmt : sys->get_system_statements()->get_statements()) {
//         if (stmt) {
//             collect_namespaces_from_statement(stmt.get());
//         }
//     }
}

// template<recurring_statement recstt>
// void ChipsToXmiWriter::collect_namespaces_from_statement(const system_statement<recstt>* node)
// {
//     if (!node) return;
    
//     auto stmt_type = node->get_statement_type();
    
//     // Ajouter les namespaces selon le type de statement
//     switch (stmt_type) {
//         case S_LINK_ST:
//         case S_EXPR_PLUG_ST:  // Type réel pour le plugging
//             add_namespace_if_needed("chips.systemspecific.expressions", "http://chips/systemspecific/expressions");
//             add_namespace_if_needed("chips.systemspecific.expressions.feeder", "http://chips/systemspecific/expressions/feeder");
//             break;
//         case S_IMPLEMENTS_ST:
//             add_namespace_if_needed("chips.systemspecific.expressions", "http://chips/systemspecific/expressions");
//             break;
//         default:
//             break;
//     }
// }
