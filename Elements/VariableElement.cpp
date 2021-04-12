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
{//TODO add weak ptr checking
    m_Type = m_Children[0]->GetType();
    if (!m_Owner.lock()->AddVariable(m_Name, m_Type))
    {
        throw std::exception();
    }
    std::string res = GetType() + " " + m_Name;
    if (m_bWithEquality)
    {
        if (m_Children.size() == 2)
        {
             if (m_Type != m_Children[1]->GetType())
             {
                 throw std::exception();
             }
        }
        else
        {
            if (m_Owner.lock()->CheckVariableForType(m_SecondName, m_Type))
            {
                throw std::exception();
            }
            res += " =" + m_SecondName;
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

void VariableElement::SetSecondName(const std::string& name)
{
    m_SecondName = name;
}
