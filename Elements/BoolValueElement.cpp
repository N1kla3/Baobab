//
// Created by kolya on 4/25/21.
//

#include "BoolValueElement.h"

std::string BoolValueElement::GetText()
{
    if (m_Value == "True") return "true";
    else return "false";
}

void BoolValueElement::SetValue(const std::string& value)
{
    m_Value = value;
}
