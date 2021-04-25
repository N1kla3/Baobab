//
// Created by kolya on 4/10/21.
//

#include "VariableElement.h"
#include "Baobab.h"

VariableElement::VariableElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{

}

std::string VariableElement::GetText()
{
    auto type = m_Children[0]->GetType();
    if (!m_Owner.lock()->AddVariable(m_Name, type))
    {
        throw std::exception();
    }
    std::string res = GetType() + " " + m_Name;
    if (m_bWithEquality)
    {
        res += " = " + m_Children[1]->GetText();
        if (type != m_Children[1]->GetType())
        {
            throw std::exception();
        }
    }
    return res;
}

void VariableElement::SetWithEquality(bool haveEquality)
{
    m_bWithEquality = haveEquality;
}

void VariableElement::SetName(const std::string& name)
{
    m_Name = name;
}

