#include "ChipsToXmiVisitor.hpp"
#include "ast_lrxvalues.hpp"

namespace {
    std::string dft_to_string(dataflow_type dft){
        switch(dft){
            case dataflow_type::INT: return "int";
            case dataflow_type::FLOAT: return "float";
            case dataflow_type::BOOL: return "bool";
        }
        return "unknown";
    }

    std::string expenv_to_string(expression_env env){
        switch(env){
            case expression_env::PRIMITIVE: return "primitive";
            case expression_env::COLLECTIVE: return "collective";
            case expression_env::SYSTEM: return "system";
        }
        return "unknown";
    }
}

template<dataflow_type dft, expression_env expenv>
void ChipsToXmiVisitor::visit(direct<dft, expenv>& node){
    std::cerr << "[DEBUG Visitor] visit(direct<" << dft_to_string(dft) << ", " << expenv_to_string(expenv) << ")" << std::endl;
    out() <<       "        <rvalue\n";
    writeAttribute("            xsi:type","chips.rvalues."+expenv_to_string(expenv)+":direct_"+dft_to_string(dft));
    out() << "\n";
    writeAttribute("            value", std::to_string(node.get_value()));
    out() << " />\n";
}

void ChipsToXmiVisitor::visit(ast_node& node){
    // std::cerr << "[DEBUG Visitor] visit(ast_node) - fallback générique" << std::endl;
    // out() << "    <!-- ast_node générique -->\n";

    if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
        visit(*dir);
    if(auto* dir = dynamic_cast<direct<dataflow_type::BOOL, expression_env::SYSTEM>*>(&node))
        visit(*dir);
    
    if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::PRIMITIVE>*>(&node))
        visit(*pl);
    if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::PRIMITIVE>*>(&node))
        visit(*pl);
    if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::COLLECTIVE>*>(&node))
        visit(*pl);
    if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::COLLECTIVE>*>(&node))
        visit(*pl);
    if(auto* pl = dynamic_cast<plus<dataflow_type::INT, expression_env::SYSTEM>*>(&node))
        visit(*pl);
    if(auto* pl = dynamic_cast<plus<dataflow_type::FLOAT, expression_env::SYSTEM>*>(&node))
        visit(*pl);
    //TODO: regarder pour regler ce probleme
}


void ChipsToXmiVisitor::writeAttribute(const std::string& name, const std::string& value){
    std::string normalized = name;
    while (!normalized.empty() && (normalized.front() == ' ' || normalized.front() == '\t')){
        normalized.erase(normalized.begin());
    }

    if(normalized == "xsi:type"){
        ensure_namespace_for_type(value);
    }
    out() << " " << name << "=\"" << value << "\"";
}

void ChipsToXmiVisitor::ensure_namespace_for_prefix(const std::string& ns_prefix){
    if (ns_prefix.empty()){
        return;
    }

    std::string suffix = ns_prefix;
    if (suffix.rfind("chips.", 0) == 0){
        suffix = suffix.substr(6);
    }

    size_t pos = 0;
    while ((pos = suffix.find('.', pos)) != std::string::npos){
        suffix.replace(pos, 1, "/");
        pos++;
    }

    std::string url = suffix.empty() || suffix[0] != '/'
                          ? "http://chips/" + suffix
                          : "http://chips" + suffix;
    m_writer.add_namespace_if_needed(ns_prefix, url);
}

void ChipsToXmiVisitor::ensure_namespace_for_type(const std::string& type_value){
    size_t colon_pos = type_value.find(':');
    if (colon_pos == std::string::npos){
        return;
    }
    ensure_namespace_for_prefix(type_value.substr(0, colon_pos));
}