//
// Created by kolya on 4/25/21.
//
#pragma once

#include "Element.h"

class ParamElement : public Element
{
public:
    ParamElement(const std::shared_ptr<Baobab>& owner) : Element(owner){}
    virtual std::string GetText() override;
    void SetName(const std::string& name);

private:
    std::string m_Name;
};

