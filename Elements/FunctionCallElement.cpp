//
// Created by kolya on 4/16/21.
//

#include "FunctionCallElement.h"
#include "Baobab.h"

std::string FunctionCallElement::GetText()
{
    try
    {
        std::string res = "";
        auto functionTraits = m_Owner.lock()->GetFunction(m_FunctionName);
        if (functionTraits == m_Owner.lock()->empty_function)
        {
            throw "Function traits are incorrect";
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

            if (functionTraits.second.size() != m_Children.size()) throw "Incorrect arguments size";
            for (int index = 0; index < m_Children.size(); index++)
            {
                if (m_Children[index]->GetType() != functionTraits.second[index])
                {
                    throw "Incorrect argument type";
                }
            }
        }
        return res;
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
}

void FunctionCallElement::SetFunctionName(const std::string& name)
{
    m_FunctionName = name;
}
