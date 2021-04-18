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
    result += m_Children[i++]->GetText();
    result += ")";

    result += m_Children[i++]->GetText();

    m_Owner.lock()->OpenBody(false);
    return result;
}
