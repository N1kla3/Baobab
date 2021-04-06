//
// Created by kolya on 4/6/21.
//

#pragma once

#include "Element.h"

class ConditionElement : public Element
{
public:
    ConditionElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText() const override;

    std::string name_to_check{};
    int num;
};

