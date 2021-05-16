//
// Created by kolya on 4/18/21.
//
#pragma once

#include "Element.h"

class WhileElement : public Element
{
public:
    WhileElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    virtual std::string GetText() override;
};
