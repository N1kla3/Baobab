//
// Created by kolya on 5/3/21.
//
#pragma once

#include "Element.h"

class NamespaceBody : public Element
{
public:
    NamespaceBody(const std::shared_ptr<Baobab>& owner) : Element(owner) {}
    virtual std::string GetText() override;

private:
};
