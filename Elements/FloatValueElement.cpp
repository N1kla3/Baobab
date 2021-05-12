//
// Created by kolya on 4/25/21.
//

#include "FloatValueElement.h"

std::string FloatValueElement::GetText()
{
    return m_First;
}

void FloatValueElement::SetNums(const std::string& first)
{
    m_First = first;
}
