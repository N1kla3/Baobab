//
// Created by kolya on 4/16/21.
//
#pragma once

#include "Element.h"

class FunctionCallElement : public Element
{
public:
    FunctionCallElement(const std::shared_ptr<Baobab>& owner) : Element(owner){}
    virtual std::string GetText() override;
    void SetFunctionName(const std::string& name);

private:
    std::string m_Type;
    std::string m_FunctionName;
};

