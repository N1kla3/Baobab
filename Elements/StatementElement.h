//
// Created by kolya on 3/31/21.
//

#pragma once

#include "Element.h"

class StatementElement : public Element
{
public:
    StatementElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    [[nodiscard]] virtual std::string GetText() override;
    void SetName(const std::string& name);

private:
    std::string m_Name;
};
