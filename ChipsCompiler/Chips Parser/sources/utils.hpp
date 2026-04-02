#ifndef __UTILS__
#define __UTILS__

#include "metamodel_enums.hpp"
#include "forward_declarations.hpp"
#include <string>
#include <any>
#include <memory>
#include <stdexcept>

namespace chips {
    std::string dft_to_string(dataflow_type dft);
    std::string expenv_to_string(expression_env expenv);

    template<dataflow_type dft>
    std::string dft_to_string();
    template<expression_env expenv>
    std::string expenv_to_string();
}

#endif