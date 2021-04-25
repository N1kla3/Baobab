//
// Created by kolya on 4/25/21.
//

#include "ParamElement.h"
#include "Baobab.h"

std::string ParamElement::GetText()
{
    if (m_Name.empty())
    {
        m_Type = m_Children[0]->GetType();
        return m_Children[0]->GetText();
    }
    else
    {
        if (m_Owner.lock()->CanAddThisVariable(m_Name))
        {
            m_Type = m_Owner.lock()->GetVariableType(m_Name);
            return m_Name;
        }
        else throw std::exception();
    }
}

void ParamElement::SetName(const std::string& name)
{
    m_Name = name;
}
