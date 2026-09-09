#include "Dictionary.hpp"

void Dictionary::addLogical(
    ChipsParser::L_function_defContext *key,
    const std::string &name,
    const std::string &value)
{
    logicals_[key][name] = value;
}

void Dictionary::addPhysical(
    ChipsParser::P_function_defContext *key,
    const std::string &name,
    const std::string &value)
{
    physicals_[key][name] = value;
}

void Dictionary::addSpread(
    ChipsParser::Collective_op_defContext *key,
    const std::string &name,
    const std::string &value)
{
    spreads_[key][name] = value;
}

void Dictionary::addCollect(
    ChipsParser::Collective_op_defContext *key,
    const std::string &name,
    const std::string &value)
{
    collects_[key][name] = value;
}

namespace
{

    std::string serializeValue(const Dictionary::Value &values)
    {
        std::string result;
        bool first = true;

        for (const auto &[name, value] : values)
        {
            if (!first)
            {
                result += ", ";
            }

            const auto &type = value;

            result += type;
            result += "& ";
            result += name;

            first = false;
        }

        return result;
    }

} // namespace

std::string Dictionary::serializeL(
    ChipsParser::L_function_defContext *key) const
{
    const auto it = logicals_.find(key);

    if (it == logicals_.end())
    {
        return {};
    }

    return serializeValue(it->second);
}

std::string Dictionary::serializeP(
    ChipsParser::P_function_defContext *key) const
{
    const auto it = physicals_.find(key);

    if (it == physicals_.end())
    {
        return {};
    }

    return serializeValue(it->second);
}

std::string Dictionary::serializeCollective(
    ChipsParser::Collective_op_defContext *key) const
{
    std::string result;

    if (const auto it = spreads_.find(key); it != spreads_.end())
    {
        result += serializeValue(it->second);
    }

    if (const auto it = collects_.find(key); it != collects_.end())
    {
        if (!result.empty())
        {
            result += ", ";
        }

        result += serializeValue(it->second);
    }

    return result;
}

bool Dictionary::lookupL(ChipsParser::L_function_defContext* key, const std::string& name, std::string& outType) const
{
    auto it = logicals_.find(key);
    if (it == logicals_.end())
        return false;

    auto valIt = it->second.find(name);
    if (valIt == it->second.end())
        return false;

    outType = valIt->second;
    return true;
}

bool Dictionary::lookupP(ChipsParser::P_function_defContext* key, const std::string& name, std::string& outType) const
{
    auto it = physicals_.find(key);
    if (it == physicals_.end())
        return false;

    auto valIt = it->second.find(name);
    if (valIt == it->second.end())
        return false;

    outType = valIt->second;
    return true;
}