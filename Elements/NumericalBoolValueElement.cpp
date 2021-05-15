//
// Created by kolya on 5/15/21.
//

#include "NumericalBoolValueElement.h"
#include "Baobab.h"

std::string NumericalBoolValueElement::GetText()
{
    std::string res = "";
    try
    {
        if (!m_Name.empty())
        {
            if (m_Owner.lock()->CheckVariableForType(m_Name, "float")
                || m_Owner.lock()->CheckVariableForType(m_Name, "int"))
            {
                res += m_Name;
                m_Type = m_Owner.lock()->GetVariableType(m_Name);
            }
            else
            {
                throw "Variable have incorrect type for equality condition";
            }
        }
        else if (!m_Int.empty())
        {
            res += m_Int;
            m_Type = "int";
        }
        else if (!m_Children.empty())
        {
            res += m_Children[0]->GetText();
            m_Type = m_Children[0]->GetType();
        }
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
    return res;
}

void NumericalBoolValueElement::SetName(const std::string& name)
{
    m_Name = name;
}

void NumericalBoolValueElement::SetInt(const std::string& num)
{
    m_Int = num;
}
