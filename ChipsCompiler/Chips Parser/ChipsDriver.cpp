#include "ChipsDriver.hpp"
#include "ChipsParser.hpp"

driver::driver ()
: trace_parsing (false), trace_scanning (false)
{}

int driver::parse (const std::string &f)
{
    file = f;
    location.initialize (&file);
    scan_begin ();
    yy::parser theparser(*this);
    theparser.set_debug_level (trace_parsing);
    int res = theparser.parse ();
    scan_end ();
    if(res == 0 && ast){
        ast->hello();
        
        // Générer automatiquement le XMI après parsing réussi
        std::filesystem::path p(f);
        std::string output = "output_" + p.filename().string();
        // Remplacer l'extension par .xmi
        size_t pos = output.find_last_of('.');
        if (pos != std::string::npos) {
            output = output.substr(0, pos) + ".xmi";
        } else {
            output += ".xmi";
        }
        
        std::cout << "📝 Génération XMI: " << output << "\n";
        // Passer juste le nom du fichier (sans le chemin) au writer
        generate_xmi(output, p.filename().string());
    }
    return res;
}

void driver::generate_xmi(const std::string& output_file, const std::string& source_filename)
{
    if (!ast) {
        std::cerr << "❌ Erreur: AST non disponible\n";
        return;
    }
    
    // Ouvrir le fichier de sortie
    std::ofstream out(output_file);
    if (!out) {
        std::cerr << "❌ Impossible de créer le fichier: " << output_file << "\n";
        return;
    }
    
    // Créer le writer et le visitor
    ChipsToXmiWriter writer(out);
    ChipsToXmiVisitor visitor(writer, out);
    
    // PREMIÈRE PASSE: Collecter les namespaces nécessaires
    writer.collect_namespaces(dynamic_cast<chips_node*>(ast.get()));
    
    // Écrire le header XMI avec les namespaces collectés
    writer.xmi_header(source_filename);
    
    // DEUXIÈME PASSE: Parcourir l'AST avec le visitor pour générer le contenu
    ast->accept(visitor);
    
    // Écrire le footer XMI
    writer.xmi_footer();
    
    out.close();
    std::cout << "✅ XMI généré: " << output_file << "\n";
}
