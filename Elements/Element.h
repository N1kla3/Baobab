//
// Created by kolya on 3/30/21.
//

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Baobab;

class Element
{
public:
    Element(const std::shared_ptr<Baobab>& owner);
    [[nodiscard]] virtual std::string GetText() = 0;
    [[nodiscard]] virtual std::string GetType() const { return m_Type; }
    void AddElement(std::unique_ptr<Element>&& element);
    virtual ~Element(){}

protected:
    std::vector<std::unique_ptr<Element>> m_Children{};
    std::weak_ptr<Baobab> m_Owner;
    std::string m_Type = "None";
};
