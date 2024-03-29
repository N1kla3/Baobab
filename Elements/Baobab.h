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

    int CanAddThisVariable(const std::string& name);

    bool GetIsFunctionBodyNow() const;
    void SetIsFunctionBodyNow(bool flag);

    bool AddVariable(const std::string& variableName, const std::string& variableType);
    bool IsVariableExists(const std::string& name);
    bool CheckVariableForType(const std::string& name, const std::string& type);
    std::string GetVariableType(const std::string& name);
    bool AddFunction(const std::string& functionName, const std::string& functionType,
                     const std::vector<std::string>& functionParams);

    std::string GetLastFunctionType() const;
    /**
     *
     * @return return empty string if not found
     */
    std::pair<std::string, std::vector<std::string>>& GetFunction(const std::string& functionName);
    std::pair<std::string, std::vector<std::string>> empty_function{};

private:
    std::shared_ptr<Element> m_Root;

    std::unordered_map<std::string, std::pair<std::string, std::vector<std::string>>> m_Functions{
    };
    var_stack m_Variables{};

    std::string m_CurrentFunction;
    bool m_bIsHandlingFunction = false;
};
