//
// Created by kolya on 4/5/21.
//

#pragma once

#include "Element.h"

class TypeElement : public Element
{
public:
    TypeElement(const std::shared_ptr<Baobab>& owner, const std::string& typeName);
    [[nodiscard]]virtual std::string GetText()  override;

private:
    std::string m_TypeName;
    std::string m_Type;
};

