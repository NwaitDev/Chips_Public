#include "ChipsDriver.hpp"
#include "ChipsParser.hpp"
#include <sstream>

driver::driver ()
: trace_parsing (false), trace_scanning (false), skip_semantic_analysis(false), skip_xmi_generation(false)
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

        if (!skip_xmi_generation) {
            // Générer automatiquement le XMI après parsing réussi
            std::filesystem::path p(f);
            std::string output = xmi_output_filename.empty()
                ? "output_" + p.filename().string()
                : xmi_output_filename;

            // Remplacer l'extension par .xmi (uniquement si on utilise le nom par defaut)
            if (xmi_output_filename.empty()) {
                size_t pos = output.find_last_of('.');
                if (pos != std::string::npos) {
                    output = output.substr(0, pos) + ".xmi";
                } else {
                    output += ".xmi";
                }
            }

            std::cout << "📝 Génération XMI: " << output << "\n";
            // Passer juste le nom du fichier (sans le chemin) au writer
            generate_xmi(output, p.filename().string());
        }
    }
    return res;
}

void driver::generate_xmi(const std::string& output_file, const std::string& source_filename)
{
    if (!ast) {
        std::cerr << "❌ Erreur: AST non disponible\n";
        return;
    }

    // Visite unique: bufferise le contenu et verifie les erreurs semantiques
    std::ostringstream body_out;
    ChipsToXmiWriter body_writer(body_out);
    ChipsToXmiVisitor visitor(body_writer, body_out);
    
    // Visiter l'AST pour générer le contenu XMI
    ast->accept(visitor);
    
    if (!skip_semantic_analysis && visitor.has_semantic_errors()) {
        std::cerr << "❌ Erreurs semantiques detectees, XMI non genere." << std::endl;
        for (const auto &err : visitor.semantic_errors()) {
            std::cerr << "  - " << err << std::endl;
        }
        return;
    }
    
    // Ouvrir le fichier de sortie
    std::ofstream out(output_file);
    if (!out) {
        std::cerr << "❌ Impossible de créer le fichier: " << output_file << "\n";
        return;
    }
    
    // Ecrire le XMI final avec tous les namespaces collectes
    ChipsToXmiWriter writer(out);
    writer.copy_namespaces_from(body_writer);
    writer.xmi_header(source_filename);
    out << body_out.str();
    writer.xmi_footer();
    
    out.close();
    std::cout << "✅ XMI généré: " << output_file << "\n";
}
