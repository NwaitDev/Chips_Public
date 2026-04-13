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

    std::string any_demangle(const std::type_info& ti) {
        int status = 0;
        std::unique_ptr<char, void(*)(void*)> demangled(
            abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status),
            std::free
        );
        return (status == 0 && demangled) ? demangled.get() : ti.name();
    };

    template<> std::string dft_to_string<dataflow_type::INT>(){return "int";}
    template<> std::string dft_to_string<dataflow_type::FLOAT>(){return "float";}
    template<> std::string dft_to_string<dataflow_type::BOOL>(){return "bool";}
    template<> std::string expenv_to_string<expression_env::PRIMITIVE>(){return "primitive";}
    template<> std::string expenv_to_string<expression_env::COLLECTIVE>(){return "collective";}
    template<> std::string expenv_to_string<expression_env::SYSTEM>(){return "system";}

    bool is_function_output(std::any& value){
        // if(auto* p = std::any_cast<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>(&value))
        //     return true;
        // if(auto* p = std::any_cast<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(&value))
        //     return true;
        // if(auto* p = std::any_cast<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(&value))
        //     return true;
        // if(auto* p = std::any_cast<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>(&value))
        //     return true;
        // if(auto* p = std::any_cast<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(&value))
        //     return true;
        // if(auto* p = std::any_cast<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(&value))
        //     return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>>(&value))
            return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>>(&value))
            return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>>(&value))
            return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>>(&value))
            return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>>(&value))
            return true;
        if(auto* p = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>>(&value))
            return true;
        return false;
    }

    
} // namespace chips
