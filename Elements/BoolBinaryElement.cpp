//
// Created by kolya on 4/6/21.
//

#include "BoolBinaryElement.h"

std::string BoolBinaryElement::GetText()
{
    if (str == "and")
    {
        return "&&";
    }
    else if (str == "or")
    {
        return "||";
    }
    return str;
}

BoolBinaryElement::BoolBinaryElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{}
