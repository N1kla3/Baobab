//
// Created by kolya on 4/5/21.
//

#include "TypeElement.h"

TypeElement::TypeElement(const std::shared_ptr<Baobab>& owner, const std::string& typeName)
    : Element(owner), m_TypeName(typeName)
{}

std::string TypeElement::GetText()
{
    auto result = m_TypeName;
    if (m_TypeName == "string") result = "std::string";
    else if (m_TypeName == "element")
        result = "std::variant<int, float, std::string, bool>";
    else if (m_TypeName == "set")
        result = "std::vector<std::variant<int, float, std::string, bool>>";
    m_Type = result;
    return result;
}
