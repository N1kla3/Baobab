//
// Created by kolya on 5/16/21.
//

#pragma once

#include "Element.h"

class CycleBodyPart : public Element
{
public:
    CycleBodyPart(const std::shared_ptr<Baobab>& owner)
        : Element(owner)
    {}
    virtual std::string GetText() override;
};

