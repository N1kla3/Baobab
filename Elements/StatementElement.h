//
// Created by kolya on 3/31/21.
//

#pragma once

#include "Element.h"

class StatementElement : public Element
{
public:
    [[nodiscard]] virtual std::string GetText()  override;

};

