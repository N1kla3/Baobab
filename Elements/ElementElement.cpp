//
// Created by kolya on 4/25/21.
//

#include "ElementElement.h"
#include "Baobab.h"

std::string ElementElement::GetText()
{
    m_Type = "std::variant<int, float, std::string, bool>";
    if (!m_Value.empty())
    {
        return m_Value;
    }
    else if (!m_Name.empty())
    {
        std::array<std::string, 4> types{"int", "float", "std::string", "bool"};
        for (auto val : types)
        {
            if (m_Owner.lock()->CheckVariableForType(m_Name, val))
            {
                return m_Name;
            }
        }
        throw std::exception();
    }
    else
    {
        return m_Children[0]->GetText();
    }
}

void ElementElement::SetValue(const std::string& value)
{
    m_Value = value;
}

void ElementElement::SetName(const std::string& name)
{
    m_Name = name;
}
