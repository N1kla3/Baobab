//
// Created by kolya on 4/5/21.
//

#include "FunctionElement.h"
#include "Baobab.h"
#include <fstream>

std::string FunctionElement::GetText()
{
    if (m_Owner.lock()->GetIsFunctionBodyNow()) { throw "Cant create function in function"; }
    std::string res = "";
    if (!m_Owner.lock()->OpenFunctionBody(true)) throw "Cant create function in function";
    auto param_size = m_Names.size() - 1;
    auto children_size = m_Children.size();
    auto return_size = children_size - param_size - 1;
    std::string return_type;
    if (return_size) return_type += m_Children[children_size - 2]->GetText();
    else
        return_type += "void";
    res += return_type;
    m_Type = return_type;
    std::vector<std::string> param_types;
    for (int index = 0; index < param_size; index++) { param_types.push_back(m_Children[index]->GetText()); }
    if (!m_Owner.lock()->AddFunction(m_Names[0], return_type, param_types)) { throw "Function already exists " + m_Names[0]; }
    res += " " + m_Names[0] + "(";
    for (int i = 0; i < param_size; i++)
    {
        if (i != 0) res += ",";
        auto name = m_Names[1 + i];
        auto type = m_Children[i]->GetText();
        if (m_Owner.lock()->AddVariable(name, type)) { res += type + " " + name; }
        else
            throw "Cant add variable with name" + name;
    }
    res += ")";
    WriteToFile("functions.h", res + ";\n");
    res += m_Children[children_size - 1]->GetText();
    m_Owner.lock()->OpenFunctionBody(false);
    WriteToFile("functions.cpp", res);
    return "";
}

void FunctionElement::SetNames(const std::vector<std::string>& names) { m_Names = names; }

void FunctionElement::WriteToFile(const std::string& file, const std::string& value)
{
    std::ofstream stream(file, std::ios::app);
    if (stream.is_open())
    {
        stream << value;
    }
    stream.close();
}

