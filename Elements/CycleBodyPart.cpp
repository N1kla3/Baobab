//
// Created by kolya on 5/16/21.
//

#include "CycleBodyPart.h"

std::string CycleBodyPart::GetText()
{
    return m_Children[0]->GetText();
}
