//
// Created by kolya on 3/30/21.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

class Element
{
public:
    virtual std::string GetText() const = 0;
    void AddElement(std::unique_ptr<Element>&& element);
protected:
    std::vector<std::unique_ptr<Element>> m_Children{};
};
