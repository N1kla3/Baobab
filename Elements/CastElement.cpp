//
// Created by kolya on 4/19/21.
//

#include "CastElement.h"
#include "Baobab.h"

std::string CastElement::GetText()
{
    m_Children[0]->GetText();
    m_Children[1]->GetText();
    m_Type = m_Children[0]->GetType();
    auto second_type = m_Children[1]->GetType();
    if (CAST_MAP.find(m_Type) != CAST_MAP.end())
    {
        for (auto type : CAST_MAP.at(m_Type))
        {
            if (type == second_type)
            {
                std::string res = "(";
                res += m_Type;
                res += ")(";//TODO strange thing
                res += second_type + ")";//TODO type not corrrect
                return res;
            }
        }
        throw "Impossible cast from";
    }
    throw "Impossible cast to";
}
