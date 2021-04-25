//
// Created by kolya on 4/16/21.
//

#include "FunctionCallElement.h"
#include "Baobab.h"

std::string FunctionCallElement::GetText()
{
    std::string res = "";
    auto functionTraits = m_Owner.lock()->GetFunction(m_FunctionName);
    if (functionTraits == m_Owner.lock()->empty_function)
    {
        throw std::exception();
    }
    else
    {
        m_Type = functionTraits.first;
        res += m_FunctionName + "(";
        bool comma = false;
        for (auto& node : m_Children)
        {
            if (comma) res += ",";
            else comma = true;
            res += node->GetText();
        }
        res += ")";

        if (functionTraits.second.size() != m_Children.size()) throw std::exception();
        for (int index = 0; index < m_Children.size(); index++)
        {
            if (m_Children[index]->GetType() != functionTraits.second[index])
            {
                throw std::exception();
            }
        }
    }
    return res;
}

void FunctionCallElement::SetFunctionName(const std::string& name)
{
    m_FunctionName = name;
}
