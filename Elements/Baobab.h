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
    using var_map = std::unordered_map<std::string, std::tuple<int, std::string>>;
    using var_stack = std::stack<std::stack<var_map>>;

    void WriteTreeTo(const std::string& filePath);
    void AddElement(std::unique_ptr<Element>&& element);

    void AddVisibilityLayer();
    std::stack<var_map>& GetLastStack();
    void RemoveStack();

    var_map& GetFunctionVarMap(const std::string& functionName);
    void AddFunction(const std::string& functionName, const var_map& varMap);

private:
    std::shared_ptr<Element> m_Root;

    std::unordered_map<std::string, var_map> functions{};
    var_stack variables{};

    bool m_bIsHandlingFunction = false;
};

