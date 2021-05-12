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

bool Baobab::AddFunction(const std::string& functionName, const std::string& functionType,
                         const std::vector<std::string>& functionParams)
{
    if (m_Functions.find(functionName) != m_Functions.end())
    {
        return false;
    }
    m_Functions[functionName].first = functionType;
    m_Functions[functionName].second = functionParams;
    m_CurrentFunction = functionName;
    return true;
}

void Baobab::OpenBody(bool openClose)
{
    if (openClose)
    {
        if (m_Variables.empty()) m_Variables.push(Baobab::var_map{});
        Baobab::var_map new_stack = m_Variables.top();
        for (auto& [name, pair] : new_stack)
        {
            pair.first++;
        }
        m_Variables.push(new_stack);
    }
    else
    {
        m_Variables.pop();
    }
}

bool Baobab::OpenFunctionBody(bool openClose)
{
    if (openClose)
    {
        if (m_bIsHandlingFunction) return false;
        m_bIsHandlingFunction = true;
        Baobab::var_map new_stack{};
        m_Variables.push(new_stack);
        return true;
    }
    else
    {
        m_Variables.pop();
        m_bIsHandlingFunction = false;
        return true;
    }
}

bool Baobab::GetIsFunctionBodyNow() const
{
    return m_bIsHandlingFunction;
}

int Baobab::CanAddThisVariable(const std::string& name)
{
    auto& map = m_Variables.top();
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

std::pair<std::string, std::vector<std::string>>& Baobab::GetFunction(const std::string& functionName)
{
    if (m_Functions.find(functionName) != m_Functions.end())
    {
        return m_Functions.at(functionName);
    }
    return empty_function;
}

std::string Baobab::GetVariableType(const std::string& name)
{
    if (m_Variables.top().find(name) != m_Variables.top().end())
    {
        auto type = m_Variables.top().at(name).second;
        return type;
    }
    return "None";
}

std::string Baobab::GetLastFunctionType() const
{
    if (m_Functions.find(m_CurrentFunction) != m_Functions.end())
    {
        return m_Functions.at(m_CurrentFunction).first;
    }
    return empty_function.first;
}
