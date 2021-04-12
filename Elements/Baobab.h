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
    using var_map = std::unordered_map<std::string, std::pair<int, std::string>>;
    using var_stack = std::stack<var_map>;

    void WriteTreeTo(const std::string& filePath);
    void SetupRoot(std::unique_ptr<Element>&& element);

    void OpenBody(bool openClose);
    bool OpenFunctionBody(bool openClose);

    bool CanAddThisVariable(const std::string& name);

    bool GetIsFunctionBodyNow() const;

    void AddVariable(const std::string& variableName, const std::string& variableType);
    bool AddFunction(const std::string& functionName);

private:
    std::shared_ptr<Element> m_Root;

    std::unordered_map<std::string, bool> functions{};
    var_stack variables{};

    bool m_bIsHandlingFunction = false;
};

