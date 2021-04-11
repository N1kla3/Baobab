//
// Created by kolya on 4/6/21.
//

#pragma once

#include "Element.h"

class BoolBinaryElement : public Element
{
public:
    BoolBinaryElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText()  override;
    std::string str;
};

