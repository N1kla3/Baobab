//
// Created by kolya on 3/31/21.
//

#include "MainElement.h"

std::string MainElement::GetText() const
{
    std::string result{};
    result += "\n#include <iostream>";
    result += "\n#include <variant>";
    result += "\n#include <set>";
    result += "\n#include <string>";
    result += "int main(){\n";
    for (auto& element_ptr : m_Children)
    {
        result += element_ptr->GetText();
    }
    result += "\n}";
    return result;
}
