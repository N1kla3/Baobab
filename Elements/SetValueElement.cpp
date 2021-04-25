//
// Created by kolya on 4/25/21.
//

#include "SetValueElement.h"

std::string SetValueElement::GetText()
{
    std::string res = "{";
    bool comma = false;
    for (auto& el : m_Children)
    {
        if (comma) res += ",";
        else comma = true;
        res += el->GetText();
    }
    res += "}";
    return res;
}
