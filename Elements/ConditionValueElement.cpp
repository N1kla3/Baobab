//
// Created by kolya on 5/15/21.
//

#include "ConditionValueElement.h"
#include "Baobab.h"

std::string ConditionValueElement::GetText()
{
    std::string res = m_bNot ? "!" : "";

    if (!m_Name.empty())
    {
        if (m_Owner.lock()->CheckVariableForType(m_Name, "bool") || m_Owner.lock()->CheckVariableForType(m_Name, "int"))
        {
            res += m_Name;
            m_Type = m_Owner.lock()->GetVariableType(m_Name);
        }
        else
        {
            throw "Variable have incorrect type for condition";
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
    return res;
}

void ConditionValueElement::SetName(const std::string& name) { m_Name = name; }

void ConditionValueElement::SetInt(const std::string& num) { m_Int = num; }

void ConditionValueElement::SetNot(bool flag) { m_bNot = flag; }
