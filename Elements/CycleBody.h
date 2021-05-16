//
// Created by kolya on 5/3/21.
//
#pragma once

#include "Element.h"

class CycleBody : public Element
{
public:
    CycleBody(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    virtual std::string GetText() override;

private:
};
