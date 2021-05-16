//
// Created by kolya on 4/26/21.
//

#include "StopElement.h"
#include "Baobab.h"

std::string StopElement::GetText() { return m_Word + ";"; }

void StopElement::SetWord(const std::string& word) { m_Word = word; }
