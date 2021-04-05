//
// Created by kolya on 3/31/21.
//

#pragma once

#include "Element.h"

class MainElement : public Element
{
public:
    MainElement() : Element(){};
    [[nodiscard]] virtual std::string GetText() const override;

};

