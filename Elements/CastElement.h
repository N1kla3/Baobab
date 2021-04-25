//
// Created by kolya on 4/19/21.
//
#pragma once

#include "Element.h"
#include <unordered_map>

class CastElement : public Element
{
public:
    CastElement(const std::shared_ptr<Baobab>& owner) : Element(owner){}
    virtual std::string GetText() override;
    void SetName(const std::string& name);

private:
    std::string m_Name = "";

    inline static const std::unordered_map<std::string, std::vector<std::string>> CAST_MAP
    {
        {"bool",    {"int", "float"}},
        {"float",   {"int", "bool"}},
        {"int",     {"bool", "float"}},
    };
};

