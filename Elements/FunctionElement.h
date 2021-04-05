//
// Created by kolya on 4/5/21.
//
#pragma once

#include "Element.h"

class FunctionElement : public Element
{
public:
    [[nodiscard]]virtual std::string GetText() const override;

    std::vector<std::string> names{};

    
};

