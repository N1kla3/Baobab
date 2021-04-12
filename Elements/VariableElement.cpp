//
// Created by kolya on 4/10/21.
//

#include "VariableElement.h"
#include "Baobab.h"

VariableElement::VariableElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{

}

std::string VariableElement::GetText()
{//TODO add weak ptr checking
    m_Type = m_Children[0]->GetType();
    auto& stack = m_Owner.lock()->GetLastStack();
    if (stack.find(m_Name) != stack.end())
    {
         if (stack.at(m_Name).first == 1)
         {
             throw std::exception();//TODO lang exceptions
         }
         else
         {
             stack.at(m_Name).first--;
         }
    }
    if (m_bWithEquality)
    {
        if (m_Children.size() == 2)
        {
             if (m_Type != m_Children[1]->GetType())
             {
                 throw std::exception();
             }
        }
        else
        {
            auto map = m_Owner.lock()->GetLastStack();
            if (map.find(m_SecondName) != map.end())
            {
                if (GetType() != map.at(m_SecondName).second)
                {
                    throw std::exception();
                }
            }
        }
    }//TODO function stack
    return "";
}

void VariableElement::SetWithEquality(bool haveEquality)
{
    m_bWithEquality = haveEquality;
}

void VariableElement::SetName(const std::string& name)
{
    m_Name = name;
}

void VariableElement::SetSecondName(const std::string& name)
{
    m_SecondName = name;
}
