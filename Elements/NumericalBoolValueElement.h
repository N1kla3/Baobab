//
// Created by kolya on 5/15/21.
//

#pragma once

#include "Element.h"

class NumericalBoolValueElement : public Element
{
public:
    NumericalBoolValueElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    virtual std::string GetText() override;

    inline void SetName(const std::string& name);

    inline void SetInt(const std::string& num);

private:
    std::string m_Name;
    std::string m_Int;
};
