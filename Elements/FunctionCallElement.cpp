//
// Created by kolya on 4/16/21.
//

#include "FunctionCallElement.h"
#include "Baobab.h"

std::string FunctionCallElement::GetText()
{
    std::string res = "";
    auto functionType = m_Owner.lock()->GetFunction(m_FunctionName);
    if (functionType.empty())
    {
        throw std::exception();
    }
    else
    {
        m_Type = functionType;

    }
    return res;
}

void FunctionCallElement::SetFunctionName(const std::string& name)
{
    m_FunctionName = name;
}
