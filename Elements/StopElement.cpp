//
// Created by kolya on 4/26/21.
//

#include "StopElement.h"
#include "Baobab.h"

std::string StopElement::GetText()
{
    try
    {
        if (m_Owner.lock()->GetIsFunctionBodyNow())
        {
            return m_Word + ";";
        }
        throw "TODO";//TODO REFORGE IN CYCLE
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
}

void StopElement::SetWord(const std::string& word)
{
    m_Word = word;
}
