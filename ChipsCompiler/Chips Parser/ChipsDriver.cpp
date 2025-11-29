

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
    std::cout << "AST généré avec succès!" << std::endl;
    ast->node_print();
  }
  return res;
}