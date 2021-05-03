//
// Created by kolya on 5/3/21.
//

#include "CycleBody.h"

std::string CycleBody::GetText()
{
    std::string res = "{";
    for (auto& child : m_Children)
    {
        res += child->GetText();
    }
    res += "}";
    return res;
}
