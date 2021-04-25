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
    void SetNames(const std::vector<std::string>& names);

private:
    std::string m_FunctionName;
    std::vector<std::string> m_Names;
};

