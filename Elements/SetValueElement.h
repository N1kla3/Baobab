//
// Created by kolya on 4/25/21.
//
#pragma once

#include "Element.h"

class SetValueElement : public Element
{
public:
    SetValueElement(const std::shared_ptr<Baobab>& owner) : Element(owner)
    {
        m_Type = "std::vector<std::variant<int, float, std::string, bool>>";
    }
    virtual std::string GetText() override;
};
