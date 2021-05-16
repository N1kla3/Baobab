//
// Created by kolya on 4/26/21.
//

#include "BodyElement.h"

std::string BodyElement::GetText()
{
    std::string res = "";
    res += "{";
    for (auto& child : m_Children) { res += child->GetText(); }
    res += "}";
    return res;
}
