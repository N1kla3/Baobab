//
// Created by kolya on 5/3/21.
//

#include "NamespaceBody.h"
#include "Baobab.h"

std::string NamespaceBody::GetText()
{
    try
    {
        std::string res = "{";
        m_Owner.lock()->OpenBody(true);
        for (auto& child : m_Children)
        {
            res += child->GetText();
        }
        m_Owner.lock()->OpenBody(false);
        res += "}";
        return res;
    }
    catch (const char* message)
    {
        std::cout << message;
        std::terminate();
    }
}
