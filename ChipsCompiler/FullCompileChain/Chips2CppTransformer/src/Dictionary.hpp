#pragma once

#include <map>
#include <string>

#include "antlr4-runtime.h"
#include "ChipsParser.h"

#include <variant>
#include <utility>

class Dictionary {
public:
   using Value = std::map<std::string,std::string>;

    void addLogical(ChipsParser::L_function_defContext* key,const std::string& name,const std::string& value);

    void addPhysical(ChipsParser::P_function_defContext* key,const std::string& name,const std::string& value);

    void addSpread(ChipsParser::Collective_op_defContext* key,const std::string& name,const std::string& value);

    void addCollect(ChipsParser::Collective_op_defContext* key, const std::string& name, const std::string& value);

    std::string serializeL(ChipsParser::L_function_defContext* key) const;

    std::string serializeP(ChipsParser::P_function_defContext* key) const;

    std::string serializeCollective(ChipsParser::Collective_op_defContext* key) const;
    
    bool lookupL(ChipsParser::L_function_defContext* key, const std::string& name, std::string& outType) const;
    bool lookupP(ChipsParser::P_function_defContext* key, const std::string& name, std::string& outType) const;
    bool lookupSpread(ChipsParser::Collective_op_defContext* key, const std::string& name, std::string& outType) const;
    bool lookupCollect(ChipsParser::Collective_op_defContext* key, const std::string& name, std::string& outType) const;

private:
    std::map<ChipsParser::L_function_defContext*, Value> logicals_;
    std::map<ChipsParser::P_function_defContext*, Value> physicals_;
    std::map<ChipsParser::Collective_op_defContext*, Value> spreads_;
    std::map<ChipsParser::Collective_op_defContext*, Value> collects_;
};
