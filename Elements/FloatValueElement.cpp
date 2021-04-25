//
// Created by kolya on 4/25/21.
//

#include "FloatValueElement.h"

std::string FloatValueElement::GetText()
{
    return m_First + "." + m_Second + "f";
}

void FloatValueElement::SetNums(const std::string& first, const std::string& second)
{
    m_First = first;
    m_Second = second;
}
