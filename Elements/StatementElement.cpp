//
// Created by kolya on 3/31/21.
//

#include "StatementElement.h"


std::string StatementElement::GetText() const
{
    if (!m_Children.empty())
    {
        return m_Children[0]->GetText() + ';';
    }
    return "";
}
