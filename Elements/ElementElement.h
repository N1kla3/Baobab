//
// Created by kolya on 4/25/21.
//
#pragma once

#include "Element.h"

class ElementElement : public Element
{
public:
    ElementElement(const std::shared_ptr<Baobab>& owner) : Element(owner){}
    virtual std::string GetText() override;
    void SetValue(const std::string& value);
    void SetName(const std::string& name);

private:
    std::string m_Value = "";
    std::string m_Name = "";
};
