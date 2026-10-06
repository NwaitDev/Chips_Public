#include "metamodel_enums.hpp"
#include <string>

#define UNUSED(x) (void)(x)

using namespace chips;

inline bool is_system_context(expression_env env){
    return env == expression_env::SYSTEM;
} 

inline std::string get_op_prefix(expression_env env){
    if(is_system_context(env)) return "chips.rvalues.dataflow.operators.";
    if(env == expression_env::COLLECTIVE) return "chips.rvalues.collective.operators.";
    return "chips.rvalues.primitive.operators.";
}

inline std::string expenv_to_string(expression_env expenv){
    switch (expenv) {
    case expression_env::PRIMITIVE: return "primitive";
    case expression_env::COLLECTIVE: return "collective";
    case expression_env::SYSTEM: return "system";
      break;
    }
}

inline std::string dft_to_string(dataflow_type dft){
    switch (dft) {

    case dataflow_type::INT: return "int";
    case dataflow_type::FLOAT: return "float";
    case dataflow_type::BOOL: return "bool";
      break;
    }
}
