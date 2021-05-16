//
// Created by kolya on 5/16/21.
//

#pragma once

#include "Element.h"

class BodyPartElement : public Element
{
public:
    BodyPartElement(const std::shared_ptr<Baobab>& owner)
        : Element(owner)
    {}
    virtual std::string GetText() override;

private:
};
