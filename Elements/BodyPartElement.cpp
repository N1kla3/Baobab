//
// Created by kolya on 5/16/21.
//

#include "BodyPartElement.h"

std::string BodyPartElement::GetText()
{
    return m_Children[0]->GetText();
}
