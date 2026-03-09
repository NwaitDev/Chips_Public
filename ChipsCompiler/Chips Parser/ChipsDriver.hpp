#ifndef DRIVER_HPP
#define DRIVER_HPP
#include "location.hh"
#include "cpp_sources/ChipsAST.hpp"
#include "cpp_sources/parserXmetamodel/ast_classes_headers/forward_declarations.hpp"
#include "to_xmi/ChipsToXmiWriter.hpp"
#include "to_xmi/ChipsToXmiVisitor.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

class driver
{
public:
    driver();
    int result;
    int parse (const std::string& f);
    
    // Nouvelle méthode pour générer le XMI
    void generate_xmi(const std::string& output_file, const std::string& source_filename);
    
    std::string file;
    std::string xmi_output_filename;
    bool skip_semantic_analysis;
    bool skip_xmi_generation;
    bool trace_parsing;
    std::string schema_version;
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;
    yy::location location;
    std::unique_ptr<chips::program_node> ast;
};

#endif // ! DRIVER_HPP
