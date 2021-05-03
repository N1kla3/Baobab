//
// Created by kolya on 4/26/21.
//
#pragma once

#include "Element.h"

class BodyElement : public Element
{
public:
    BodyElement(const std::shared_ptr<Baobab>& owner)
        : Element(owner){}
    virtual std::string GetText() override;

private:
};

