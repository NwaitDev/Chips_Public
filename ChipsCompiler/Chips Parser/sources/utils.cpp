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

    template<> std::string dft_to_string<dataflow_type::INT>(){return "int";}
    template<> std::string dft_to_string<dataflow_type::FLOAT>(){return "float";}
    template<> std::string dft_to_string<dataflow_type::BOOL>(){return "bool";}

} // namespace chips
