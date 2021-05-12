//
// Created by kolya on 4/26/21.
//

#include "ReturnElement.h"
#include "Baobab.h"

std::string ReturnElement::GetText()
{
    try
    {
        if (m_Owner.lock()->GetIsFunctionBodyNow())
        {
            if (m_Children.size() == 1)
            {
                auto res = m_Children[0]->GetText();
                auto type = m_Children[0]->GetType();
                auto function_type = m_Owner.lock()->GetLastFunctionType();
                if (type != function_type)
                {
                    throw "Return type are incompatible with function";
                }
                return "return " + res + ";";
            }
            else
            {
                if (m_Owner.lock()->GetLastFunctionType() == "void")
                {
                    return "return;";
                }
            }
        }
        else
        {
            return "return 0;";
        }
        throw "TOTAL SHIT";
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
}
