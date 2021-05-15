//
// Created by kolya on 5/15/21.
//

#include "NumericalBoolOperators.h"

std::string NumericalBoolOperators::GetText()
{
    return m_Op;
}

void NumericalBoolOperators::SetOp(const std::string& op)
{
    m_Op = op;
}
