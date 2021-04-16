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

bool Baobab::AddFunction(const std::string& functionName, const std::string& functionType)
{
    if (m_Functions.find(functionName) != m_Functions.end())
    {
        return false;
    }
    m_Functions[functionName] = functionType;
    return true;
}

void Baobab::OpenBody(bool openClose)
{
    if (m_Variables.empty()) return;
    Baobab::var_map new_stack = m_Variables.top();
    for (auto& [name, pair] : new_stack)
    {
        pair.first++;
    }
    m_Variables.push(new_stack);
}

bool Baobab::OpenFunctionBody(bool openClose)
{
    if (m_bIsHandlingFunction) return false;
    Baobab::var_map new_stack{};
    m_Variables.push(new_stack);
    return true;
}

bool Baobab::GetIsFunctionBodyNow() const
{
    return m_bIsHandlingFunction;
}

int Baobab::CanAddThisVariable(const std::string& name)
{
    auto map = m_Variables.top();
    if (map.find(name) != map.end())
    {
        int num = map.at(name).first;
        return num;
    }
    else
    {
        return 0;
    }
}

bool Baobab::AddVariable(const std::string& variableName, const std::string& variableType)
{
    auto num = CanAddThisVariable(variableName);
    if (num)
    {
        if (num == 1)
        {
            return false;
        }
        else
        {
            m_Variables.top()[variableName].first--;
            m_Variables.top()[variableName].second = variableType;
            return true;
        }
    }
    else
    {
        m_Variables.top()[variableName] = {1, variableType};
        return true;
    }
}

bool Baobab::CheckVariableForType(const std::string& name, const std::string& type)
{
    if (m_Variables.top().find(name) != m_Variables.top().end())
    {
        if (m_Variables.top().at(name).second == type) return true;
    }
    return false;
}
void Baobab::SetIsFunctionBodyNow(bool flag)
{
    m_bIsHandlingFunction = flag;
}

std::string Baobab::GetFunction(const std::string& functionName) const
{
    if (m_Functions.find(functionName) != m_Functions.end())
    {
        return m_Functions.at(functionName);
    }
    return "";
}
