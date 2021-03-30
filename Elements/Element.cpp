//
// Created by kolya on 3/30/21.
//

#include "Element.h"

void Element::AddElement(std::unique_ptr<Element>&& element)
{
    m_Children.push_back(element);
}
