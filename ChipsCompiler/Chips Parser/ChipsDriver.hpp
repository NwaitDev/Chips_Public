#ifndef DRIVER_HPP
#define DRIVER_HPP
#include "location.hh"
#include "cpp_sources/ChipsAST.hpp"
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
    void generate_xmi(const std::string& output_file);
    
    std::string file;
    bool trace_parsing;
    void scan_begin ();
    void scan_end ();
    bool trace_scanning;
    yy::location location;
    std::unique_ptr<chips_node> ast;
};

#endif // ! DRIVER_HPP
