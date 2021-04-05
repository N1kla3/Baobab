//
// Created by kolya on 4/5/21.
//

#include "TypeElement.h"

TypeElement::TypeElement(const std::shared_ptr<Baobab>& owner, const std::string& typeName)
    : Element(owner), m_TypeName(typeName)
{}

std::string TypeElement::GetText() const
{
    if      (m_TypeName == "string") return "std::string";
    else if (m_TypeName == "element") return "std::variant<int, float, std::string, bool>";
    else if (m_TypeName == "set") return "std::vector<std::variant<int, float, std::string, bool>";
    else return m_TypeName;
}
