//
// Created by kolya on 3/31/21.
//

#pragma once

#include "Element.h"

class MainElement : public Element
{
public:
    MainElement(const std::shared_ptr<Baobab>& owner) : Element(owner){};
    [[nodiscard]] virtual std::string GetText() override;
};
