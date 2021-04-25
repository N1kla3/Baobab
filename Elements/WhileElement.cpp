//
// Created by kolya on 4/18/21.
//

#include "WhileElement.h"
#include "Baobab.h"

std::string WhileElement::GetText()
{
    std::string result = "while(";
    result += m_Children[0]->GetText();
    result += ")";
    m_Owner.lock()->OpenBody(true);
    result += m_Children[1]->GetText();
    m_Owner.lock()->OpenBody(false);
    return result;
}
//TODO (!!!) namespaceBody, body, cycleBody,
//TODO (!!!) exceptions messages
//TODO (!!!) visitor
//TODO (!!!) file writing
//TODO (!!!) documentation