//
// Created by kolya on 5/15/21.
//

#pragma once

#include "Element.h"

class NumericalConditionElement : public Element
{
public:
    NumericalConditionElement(const std::shared_ptr<Baobab>& owner)
        : Element(owner)
    {}
    virtual std::string GetText() override;

private:
};

