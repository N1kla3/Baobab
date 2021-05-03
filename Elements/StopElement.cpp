//
// Created by kolya on 4/26/21.
//

#include "StopElement.h"
#include "Baobab.h"

std::string StopElement::GetText()
{
    if (m_Owner.lock()->GetIsFunctionBodyNow())
    {
        return m_Word + ";";
    }
    throw std::exception();
}

void StopElement::SetWord(const std::string& word)
{
    m_Word = word;
}
