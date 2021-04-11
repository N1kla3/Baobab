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

void Baobab::AddElement(std::unique_ptr<Element>&& element)
{
    m_Root = std::move(element);
}

void Baobab::AddVisibilityLayer()
{
    if (variables.empty()) return;
    Baobab::var_map new_stack = variables.top();
    for (auto& [name, pair] : new_stack)
    {
        pair.first++;
    }
    variables.push(new_stack);
}

Baobab::var_map& Baobab::GetLastStack()
{
    return variables.top();
}

void Baobab::RemoveStack()
{
    if (variables.empty()) return;
    variables.pop();
}

Baobab::var_map& Baobab::GetFunctionVarMap(const std::string& functionName)
{
    if (functions.find(functionName) != functions.end())
    {
        return functions.at(functionName);
    }
    //TODO default map
}

void Baobab::AddFunction(const std::string& functionName, const Baobab::var_map& varMap)
{
    functions[functionName] = varMap;
}

