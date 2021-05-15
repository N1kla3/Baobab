//
// Created by kolya on 4/25/21.
//

#include "SetValueElement.h"

std::string SetValueElement::GetText()
{
    try
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
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::exit(0);
    }
}
