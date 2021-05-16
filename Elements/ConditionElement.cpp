//
// Created by kolya on 4/6/21.
//

#include "ConditionElement.h"
#include "Baobab.h"

std::string ConditionElement::GetText()
{
    std::string res = "";
    if (m_Children.size() == 1)
    {
        res += m_Children[0]->GetText();
        m_Type = m_Children[0]->GetType();
        if (m_Children[0]->GetType() != "bool" && m_Children[0]->GetType() != "int" && m_Children[0]->GetType() != "float")
        { throw "Condition should be bool"; }
    }
    else if (m_Children.size() == 3)
    {
        res += m_Children[0]->GetText() + m_Children[1]->GetText() + m_Children[2]->GetText();
        auto first_type = m_Children[0]->GetType();
        auto second_type = m_Children[2]->GetType();
        if (m_Sign)
        {
            m_Type = "bool";
            if ((first_type == "int" || first_type == "bool")
             &&(second_type == "int" || second_type == "bool"))return res;
            else
                throw "Condition cant be " + first_type;
        }
        else
        {
            m_Type = "bool";
            if ((first_type == "int" || first_type == "float")
                &&(second_type == "int" || second_type == "float"))return res;
            else
                throw "Condition cant be" + first_type;
        }
    }
    return res;
}

ConditionElement::ConditionElement(const std::shared_ptr<Baobab>& owner) : Element(owner) { }

void ConditionElement::SetSign(bool flag) { m_Sign = flag; }
