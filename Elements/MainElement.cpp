//
// Created by kolya on 3/31/21.
//

#include "MainElement.h"
#include "Baobab.h"

std::string MainElement::GetText()
{
    try
    {
        std::string result{};
        result += "\n#include <iostream>";
        result += "\n#include <variant>";
        result += "\n#include <set>";
        result += "\n#include <string>";
        result += "int main(){\n";
        m_Owner.lock()->OpenBody(true);
        for (auto& element_ptr : m_Children)
        {
            result += element_ptr->GetText();
        }
        m_Owner.lock()->OpenBody(false);
        result += " return 0;\n}";
        return result;
    }//TODO watch catch agagin
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::terminate();
    }
}
