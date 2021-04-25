//
// Created by kolya on 4/25/21.
//
#pragma once

#include "Element.h"

class BoolValueElement : public Element
{
public:
    BoolValueElement(const std::shared_ptr<Baobab>& owner) : Element(owner){m_Type = "bool";}
    virtual std::string GetText() override;
    void SetValue(const std::string& value);

private:
    std::string m_Value;
};

