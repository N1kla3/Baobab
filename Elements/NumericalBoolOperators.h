//
// Created by kolya on 5/15/21.
//
#pragma once

#include "Element.h"

class NumericalBoolOperators : public Element
{
public:
    NumericalBoolOperators(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    virtual std::string GetText() override;
    void SetOp(const std::string& op);

private:
    std::string m_Op;
};
