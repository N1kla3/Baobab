//
// Created by kolya on 3/30/21.
//

#pragma once

#include <string>
#include <vector>
#include <memory>

class Baobab;

class Element
{
public:
    Element(const std::shared_ptr<Baobab>& owner);
    [[nodiscard]] virtual std::string GetText() const = 0;
    void AddElement(std::unique_ptr<Element>&& element);
protected:
    std::vector<std::unique_ptr<Element>> m_Children{};
    std::weak_ptr<Baobab> m_Owner;
};
