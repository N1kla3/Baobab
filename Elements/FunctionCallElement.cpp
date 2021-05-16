//
// Created by kolya on 4/16/21.
//

#include "FunctionCallElement.h"
#include "Baobab.h"

std::string FunctionCallElement::GetText()
{
    std::string res = "";
    if (m_FunctionName == "print")
    {
        m_Type = "void";
        if (m_Children.size() == 1)
        {
            auto arg = m_Children[0]->GetText();
            auto type = m_Children[0]->GetType();
            if (type == "std::vector<std::variant<int, float, std::string, bool>>"
                || type == "std::variant<int, float, std::string, bool>")
            {
                throw "Cant print Element";
            }
            res += "std::cout << " + arg;
            return res;
        }
        else throw "Print have one argument";
    }
    else if (m_FunctionName == "at")
    {
        if (m_Children.size() == 3)
        {
            auto one = m_Children[0]->GetText();
            auto oneT = m_Children[0]->GetType();
            if (oneT != "std::vector<std::variant<int, float, std::string, bool>>")
            {
                throw "First should be set";
            }
            auto two = m_Children[1]->GetText();
            auto twoT = m_Children[1]->GetType();
            if (twoT != "int") throw "Index should be int";
            auto three = m_Children[2]->GetText();
            auto threeT = m_Children[2]->GetType();
            if (threeT != "std::string") throw "Type should be in string";
            m_Type = std::string(three.cbegin() + 1, three.cend() -1);
            std::string rres = "std::get<" + m_Type + ">(" + one + "[" + two + "])";
            return rres;
        }
        else throw "Incorrect args for at(set, index, retrieve type) function";
    }
    auto functionTraits = m_Owner.lock()->GetFunction(m_FunctionName);
    if (functionTraits == m_Owner.lock()->empty_function) { throw "Function traits are incorrect"; }
    else
    {
        m_Type = functionTraits.first;
        res += m_FunctionName + "(";
        bool comma = false;
        for (auto& node : m_Children)
        {
            if (comma) res += ",";
            else
                comma = true;
            res += node->GetText();
        }
        res += ")";

        if (functionTraits.second.size() != m_Children.size()) throw "Incorrect arguments size";
        for (int index = 0; index < m_Children.size(); index++)
        {
            if (m_Children[index]->GetType() != functionTraits.second[index]) { throw "Incorrect argument type"; }
        }
    }
    return res;
}

void FunctionCallElement::SetFunctionName(const std::string& name) { m_FunctionName = name; }
