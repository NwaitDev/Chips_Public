#ifndef _DICTIONARY
#define _DICTIONARY

#include <map>
#include <string>
#include <variant>
#include <utility>

class Dictionary {
public:
    using Type = std::variant<chips_int, chips_float, chips_bool>;

    using Entry = std::pair<Type, std::string>;
    using Values = std::map<std::string, Entry>;

private:
    std::map<ChipsParser::L_function_defContext*, Values> logicals_;
    std::map<ChipsParser::P_function_defContext*, Values> physicals_;
    std::map<ChipsParser::Collective_op_defContext*, Values> spreads_;
    std::map<ChipsParser::Collective_op_defContext*, Values> collects_;
};

#endif