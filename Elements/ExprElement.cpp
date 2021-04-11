//
// Created by kolya on 4/6/21.
//

#include "ExprElement.h"

ExprElement::ExprElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{

}

std::string ExprElement::GetText()
{
    if (m_bType)
    {
        return "(" + m_Children[0]->GetText() + m_Sign + m_Children[1]->GetText() + ")";
    }
    else //TODO check types
    {
        return "(" + m_Children[0]->GetText();
    }
}

void ExprElement::SetType(bool type)
{
    m_bType = type;
}

void ExprElement::SetSignIfHave(const std::string& sign)
{
    m_Sign = sign;
}
