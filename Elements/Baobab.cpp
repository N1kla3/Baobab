//
// Created by kolya on 3/30/21.
//

#include "Baobab.h"
#include <fstream>

void Baobab::WriteTreeTo(const std::string& filePath)
{
    std::ofstream file;
    file.open(filePath);
    if (file.is_open())
    {
        file << m_Root->GetText();
    }
    file.close();
}

void Baobab::SetupRoot(std::unique_ptr<Element>&& element)
{
    m_Root = std::move(element);
}

bool Baobab::AddFunction(const std::string& functionName)
{
    if (functions.find(functionName) != functions.end())
    {
        return false;
    }
    functions[functionName] = true;
    return true;
}

void Baobab::OpenBody(bool openClose)
{
    if (variables.empty()) return;
    Baobab::var_map new_stack = variables.top();
    for (auto& [name, pair] : new_stack)
    {
        pair.first++;
    }
    variables.push(new_stack);
}

bool Baobab::OpenFunctionBody(bool openClose)
{
    if (m_bIsHandlingFunction) return false;
    Baobab::var_map new_stack{};
    variables.push(new_stack);
    return true;
}

bool Baobab::GetIsFunctionBodyNow() const
{
    return m_bIsHandlingFunction;
}

bool Baobab::CanAddThisVariable(const std::string& name)
{
    auto map = variables.top();
    if (map.find(name) != map.end())
    {
        int num = map.at(name).first;
        if (num != 1) return true;
        return false;
    }
    else
    {
        return true;
    }
}

void Baobab::AddVariable(const std::string& variableName, const std::string& variableType)
{
    variables.top()[variableName] = {1, variableType};
}
