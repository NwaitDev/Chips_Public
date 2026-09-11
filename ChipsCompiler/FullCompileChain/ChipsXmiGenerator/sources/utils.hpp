#ifndef __UTILS__
#define __UTILS__

#include "metamodel_enums.hpp"
#include "forward_declarations.hpp"
#include <string>
#include <any>
#include <memory>
#include <cxxabi.h>
#include <stdexcept>

namespace chips {
    std::string dft_to_string(dataflow_type dft);
    std::string expenv_to_string(expression_env expenv);
    std::string bt_to_string(block_type bt);
    std::string dfk_to_string(dataflow_kind dfk);
    dataflow_type ne_to_dft(node_element ne);

    template<dataflow_type dft>
    std::string dft_to_string();
    template<expression_env expenv>
    std::string expenv_to_string();
    template<node_element ne>
    dataflow_type ne_to_dft();
    template<block_type bt>
    std::string bt_to_string();
    template<dataflow_kind dfk>
    std::string dfk_to_string();

    std::string any_demangle(const std::type_info& ti);

    bool is_function_output(std::any& value);

    template<dataflow_kind K, dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const function_parameter<K, T>* /* */) noexcept{
        return T;
    }

    template<dataflow_kind K, dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const function_parameter<K, T>& /* */) noexcept{
        return T;
    }

    template<dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const collective_parameter<T>* /* */) noexcept{
        return T;
    }

    template<dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const collective_parameter<T>& /* */) noexcept{
        return T;
    }

    template<dataflow_kind K, dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const function_output<K, T>* /* */) noexcept{
        return T;
    }

    template<dataflow_kind K, dataflow_type T>
    constexpr dataflow_type get_dataflow_type(const function_output<K, T>& /* */) noexcept{
        return T;
    }

    inline std::string collective_type_to_string(const collective_function_type& type){
        switch(type){
            case collective_function_type::COLLECT: return "collect";
            case collective_function_type::SPREAD: return "spread";
            default: return "unknown";
        }
    }
}

#endif