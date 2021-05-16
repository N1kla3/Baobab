//
// Created by kolya on 4/5/21.
//
#pragma once

#include "Element.h"

class FunctionElement : public Element
{
public:
    FunctionElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    [[nodiscard]] virtual std::string GetText() override;
    void SetNames(const std::vector<std::string>& names);

private:
    std::vector<std::string> m_Names{};
};
