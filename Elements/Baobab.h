//
// Created by kolya on 3/30/21.
//

#pragma once

#include "Element.h"
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>

class Baobab
{
public:
    void WriteTreeTo(const std::string& filePath);
    void AddElement(std::unique_ptr<Element>&& element);

private:
    std::shared_ptr<Element> m_Root;

    std::unordered_map<std::string, std::vector<std::string>> functions{};
    std::stack<std::stack<std::unordered_map<std::string, int>>> variables{};
};

