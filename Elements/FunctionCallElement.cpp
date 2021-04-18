//
// Created by kolya on 4/16/21.
//

#include "FunctionCallElement.h"
#include "Baobab.h"

std::string FunctionCallElement::GetText()
{
    std::string res = "";
    auto functionType = m_Owner.lock()->GetFunction(m_FunctionName);
    if (functionType.empty())
    {
        throw std::exception();
    }
    else
    {
        m_Type = functionType;
        res += m_FunctionName + "(";
        if (!m_Children.empty())
        {
            bool comma = false;
            for (auto& node : m_Children)
            {
                if (comma) res += ",";
                else comma = true;
                res += node->GetText();
            }
        }
        else if (!m_Names.empty())
        {
            //TODO check params through map, add map
        }
        res += ")";
    }
    return res;
}

void FunctionCallElement::SetFunctionName(const std::string& name)
{
    m_FunctionName = name;
}
void FunctionCallElement::SetNames(const std::vector<std::string>& names)
{
    m_Names = names;
}
