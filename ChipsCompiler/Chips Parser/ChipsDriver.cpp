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
        generate_xmi(output);
    }
    return res;
}

void driver::generate_xmi(const std::string& output_file)
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
    
    // Écrire le header XMI
    writer.xmi_header(file);
    
    // Parcourir l'AST avec le visitor
    ast->accept(visitor);
    
    // Écrire le footer XMI
    writer.xmi_footer();
    
    out.close();
    std::cout << "✅ XMI généré: " << output_file << "\n";
}
