//
// Created by kolya on 4/6/21.
//

#include "ConditionElement.h"

std::string ConditionElement::GetText()
{
    if (name_to_check.empty())
    {
        std::string res = "";
        for (auto& child : m_Children)
        {
            res += child->GetText();
        }
        return res;
    }
    else
    {
        //TODO check name
    }
}

ConditionElement::ConditionElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{}
