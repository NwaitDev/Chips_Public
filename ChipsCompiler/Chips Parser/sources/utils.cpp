#include "utils.hpp"

namespace chips
{

    std::string dft_to_string(dataflow_type dft){
        switch(dft){
            case dataflow_type::INT: return "int";
            case dataflow_type::FLOAT: return "float";
            case dataflow_type::BOOL: return "bool";
        }
        return "unknown";
    }

    std::string expenv_to_string(expression_env expenv){
        switch(expenv){
            case expression_env::PRIMITIVE: return "primitive";
            case expression_env::COLLECTIVE: return "collective";
            case expression_env::SYSTEM: return "system";
        }
        return "unknown";
    }

    template<> std::string dft_to_string<dataflow_type::INT>(){return "int";}
    template<> std::string dft_to_string<dataflow_type::FLOAT>(){return "float";}
    template<> std::string dft_to_string<dataflow_type::BOOL>(){return "bool";}
    template<> std::string expenv_to_string<expression_env::PRIMITIVE>(){return "primitive";}
    template<> std::string expenv_to_string<expression_env::COLLECTIVE>(){return "collective";}
    template<> std::string expenv_to_string<expression_env::SYSTEM>(){return "system";}

} // namespace chips
