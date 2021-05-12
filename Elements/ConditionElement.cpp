//
// Created by kolya on 4/6/21.
//

#include "ConditionElement.h"
#include "Baobab.h"

std::string ConditionElement::GetText()
{
    if (!num.empty()) return num;
    if (name_to_check.empty())
    {//TODO REFORGE IT
        std::string res = "(";
        for (auto& child : m_Children)
        {
            res += " " + child->GetText() + " ";
        }
        return res + ")";
    }
    else
    {
        if (m_Owner.lock()->CheckVariableForType(name_to_check, "bool"))
        {
            std::string res = "(";
            if (!negative.empty())
            {
                res += "!";
            }
            res += name_to_check;
            return res + ")";
        }
        throw std::exception();
    }
}

ConditionElement::ConditionElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{
    m_Type = "bool";
}
