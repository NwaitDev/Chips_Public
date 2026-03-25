#ifndef CHIPS_TO_XMI_WRITER_HPP
#define CHIPS_TO_XMI_WRITER_HPP

#include <ostream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <filesystem>
#include <vector>


namespace fs = std::filesystem;
using namespace chips;

// Forward declarations
// class ast_node;
// class program_node;
// class preamble_section_node;
// class definition;
// class system_section_node;
// class s_statements;
// class s_statement;

class ChipsToXmiWriter {
public:
    // Constructeur principal
    ChipsToXmiWriter(std::ostream& out,
                     std::string xmi_version = "2.0",
                     std::string xmi_url = "http://www.omg.org/XMI",
                     std::string schema_version = "2");

    // === MÉTHODES PUBLIQUES ===
    
    // Écrit header XMI avec namespaces
    void xmi_header(const std::string& filename = "");
    
    // Écrit footer XMI
    void xmi_footer();
    
    // Collecte tous les namespaces nécessaires en parcourant l'AST
    void collect_namespaces(program_node* root);
    
    // Conversion complète CHIPS → XMI
    void chips_to_xmi(program_node* root);
    
    // Génère un ID unique pour un nœud
    std::string nodeId(ast_node* node);
    
    // Ajoute un namespace dynamiquement
    void add_namespace_if_needed(const std::string& ns_prefix, const std::string& url);

    // Copie les namespaces collectes depuis un autre writer
    void copy_namespaces_from(ChipsToXmiWriter& other);

private:
    // === MÉTHODES PRIVÉES DE CONVERSION ===
    
    // Preambles (definitions)
    void preambles_to_xmi(preamble_section_node* pres);
    void preamble_to_xmi(definition_variant preamble);
    
    // System statements
    void system_to_xmi(system_section_node* sys);
    void s_statements_to_xmi(std::vector<system_statement_variant>* statements);
    template<recurring_statement recstt>
    void precise_system_section_node_to_xmi(system_statement<recstt>* node);
    
    // Collection des namespaces
    void collect_namespaces_from_preambles(preamble_section_node* pres);
    void collect_namespaces_from_preamble(definition_variant preamble);
    void collect_namespaces_from_system(system_section_node* sys);
    template<recurring_statement recstt>
    void collect_namespaces_from_statement(system_statement<recstt>* node);
    
    // Générateur d'ID
    std::string nextId(const std::string& prefix = "_");

    // === MEMBRES PRIVÉS ===
    std::ostream& m_out;
    std::string m_xmiVersion;
    std::string m_xmiUrl;
    std::string m_schemaVersion;
    
    int m_idCounter;
    std::map<ast_node*, std::string> m_nodeToId;
    std::set<std::string> m_used_namespaces;
    std::map<std::string, std::string> m_namespace_urls;  // prefix -> URL
};

#endif // ! CHIPS_TO_XMI_WRITER_HPP
