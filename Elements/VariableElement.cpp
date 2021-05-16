//
// Created by kolya on 4/10/21.
//

#include "VariableElement.h"
#include "Baobab.h"

VariableElement::VariableElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}

std::string VariableElement::GetText()
{
    auto text = m_Children[0]->GetText();
    m_Type = m_Children[0]->GetType();
    if (!m_Owner.lock()->AddVariable(m_Name, m_Type)) { throw "Variable already defined"; }
    std::string res = GetType() + " " + m_Name;
    if (m_bWithEquality)
    {
        res += " = " + m_Children[1]->GetText();
        if (m_Type != m_Children[1]->GetType()) { throw "Defined type not match values type"; }
    }
    return res;
}

void VariableElement::SetWithEquality(bool haveEquality) { m_bWithEquality = haveEquality; }

void VariableElement::SetName(const std::string& name) { m_Name = name; }
