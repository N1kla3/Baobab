//
// Created by kolya on 4/18/21.
//

#include "BranchElement.h"
#include "Baobab.h"

std::string BranchElement::GetText()
{
    try
    {
        std::string result = "";
        result += "if (";
        result += m_Children[0]->GetText();
        result += ")";
        m_Owner.lock()->OpenBody(true);
        result += m_Children[1]->GetText();
        m_Owner.lock()->OpenBody(false);
        if (m_Children.size() == 3)
        {
            result += " else ";
            result += m_Children[2]->GetText();
        }
        return result;
    }
    catch (const char* message)
    {
        std::cerr << message;
        std::terminate();
    }
}
