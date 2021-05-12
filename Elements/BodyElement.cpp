//
// Created by kolya on 4/26/21.
//

#include "BodyElement.h"

std::string BodyElement::GetText()
{
    std::string res = "";
    res += "{";
    for (auto& child : m_Children)
    {
        try
        {
            res += child->GetText();
        }
        catch (const char* message)
        {
            std::cout << message;
            std::terminate();
        }
    }
    res += "}";
    return res;
}
