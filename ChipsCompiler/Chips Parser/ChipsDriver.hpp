# ifndef DRIVER_HPP
# define DRIVER_HPP
# include <string>
# include "location.hh"
# include "cpp_sources/ChipsAST.hpp"


class driver
{
public:
  driver();

  int result;
  int parse (const std::string& f);
  std::string file;
  bool trace_parsing;
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  yy::location location;
  std::unique_ptr<chips_node> ast;
};
#endif // ! DRIVER_HPP