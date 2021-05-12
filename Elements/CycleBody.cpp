//
// Created by kolya on 5/3/21.
//

#include "CycleBody.h"

std::string CycleBody::GetText()
{
    try
    {
        std::string res = "{";
        for (auto& child : m_Children)
        {
            res += child->GetText();
        }
        res += "}";
        return res;
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
}
