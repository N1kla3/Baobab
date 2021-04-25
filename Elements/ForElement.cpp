//
// Created by kolya on 4/18/21.
//

#include "ForElement.h"
#include "Baobab.h"

std::string ForElement::GetText()
{
    std::string result = "for(";
    m_Owner.lock()->OpenBody(true);
    auto i = 0;
    if (m_Children.size() == 4)
    {
        result += m_Children[i]->GetText();
        i++;
    }
    result += ";";
    result += m_Children[i++]->GetText();
    result += ";";
    result += m_Name + " = ";
    result += m_Children[i]->GetText();
    if (m_Owner.lock()->CanAddThisVariable(m_Name))
    {
        if (m_Owner.lock()->GetVariableType(m_Name)
            != m_Children[i++]->GetType())
            throw std::exception();
    }
    else throw std::exception();
    result += ")";

    result += m_Children[i++]->GetText();

    m_Owner.lock()->OpenBody(false);
    return result;
}

void ForElement::SetName(const std::string& name)
{
    m_Name = name;
}
