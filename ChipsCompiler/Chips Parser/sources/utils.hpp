#ifndef __UTILS__
#define __UTILS__

#include "metamodel_enums.hpp"
#include <string>

namespace chips {
    std::string dft_to_string(dataflow_type dft);

    template<dataflow_type dft>
    std::string dft_to_string();
}

#endif