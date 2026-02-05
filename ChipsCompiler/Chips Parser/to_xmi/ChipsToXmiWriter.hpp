#ifndef CHIPS_TO_XMI_WRITER_HPP
#define CHIPS_TO_XMI_WRITER_HPP

#include <ostream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <filesystem>
#include "../cpp_sources/ChipsAST.hpp"
#include "../cpp_sources/chips_overall_system.hpp"
#include "../cpp_sources/chips_declaration_ctx.hpp"

namespace fs = std::filesystem;

// Forward declarations
class ast_node;
class chips_node;
class preambles_node;
class preamble_node;
class system_node;
class s_statements_node;
class s_statement_node;

class ChipsToXmiWriter {
public:
    // Constructeur principal
    ChipsToXmiWriter(std::ostream& out, 
                     std::string xmi_version = "2.0", 
                     std::string xmi_url = "http://www.omg.org/XMI");

    // === MÉTHODES PUBLIQUES ===
    
    // Écrit header XMI avec namespaces
    void xmi_header(const std::string& filename = "");
    
    // Écrit footer XMI
    void xmi_footer();
    
    // Collecte tous les namespaces nécessaires en parcourant l'AST
    void collect_namespaces(const chips_node* root);
    
    // Conversion complète CHIPS → XMI
    void chips_to_xmi(const chips_node* root);
    
    // Génère un ID unique pour un nœud
    std::string nodeId(const ast_node* node);
    
    // Ajoute un namespace dynamiquement
    void add_namespace_if_needed(const std::string& ns_prefix, const std::string& url);

    // Copie les namespaces collectes depuis un autre writer
    void copy_namespaces_from(const ChipsToXmiWriter& other);

private:
    // === MÉTHODES PRIVÉES DE CONVERSION ===
    
    // Preambles (definitions)
    void preambles_to_xmi(const preambles_node* pres);
    void preamble_to_xmi(const preamble_node* preamble);
    
    // System statements
    void system_to_xmi(const system_node* sys);
    void s_statements_to_xmi(const s_statements_node* statements);
    void precise_system_node_to_xmi(const s_statement_node* node);
    
    // Collection des namespaces
    void collect_namespaces_from_preambles(const preambles_node* pres);
    void collect_namespaces_from_preamble(const preamble_node* preamble);
    void collect_namespaces_from_system(const system_node* sys);
    void collect_namespaces_from_statement(const s_statement_node* node);
    
    // Générateur d'ID
    std::string nextId(const std::string& prefix = "_");

    // === MEMBRES PRIVÉS ===
    std::ostream& m_out;
    std::string m_xmiVersion;
    std::string m_xmiUrl;
    
    int m_idCounter;
    std::map<const ast_node*, std::string> m_nodeToId;
    std::set<std::string> m_used_namespaces;
    std::map<std::string, std::string> m_namespace_urls;  // prefix -> URL
};

#endif // ! CHIPS_TO_XMI_WRITER_HPP
