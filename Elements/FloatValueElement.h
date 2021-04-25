//
// Created by kolya on 4/25/21.
//
#pragma once

#include "Element.h"

class FloatValueElement : public Element
{
public:
    FloatValueElement(const std::shared_ptr<Baobab>& owner) : Element(owner){m_Type = "float";}
    virtual std::string GetText() override;
    void SetNums(const std::string& first, const std::string& second);

private:
    std::string m_First;
    std::string m_Second;
};

