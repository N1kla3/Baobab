//
// Created by kolya on 4/6/21.
//

#include "ConditionElement.h"
#include "Baobab.h"

std::string ConditionElement::GetText()
{
    std::string res = "";
    try
    {
        if (m_Children.size() == 1)
        {
            res += m_Children[0]->GetText();
            if (m_Children[0]->GetType() != "bool")
            {
                throw "Condition should be bool";
            }
        }
        else if (m_Children.size() == 3)
        {
            res += m_Children[0]->GetText()
                   + m_Children[1]->GetText()
                   + m_Children[2]->GetText();
            auto first_type = m_Children[0]->GetType();
            auto second_type = m_Children[2]->GetType();
            if (m_Sign)
            {
                if (first_type == "int" || first_type == "bool") return res;
                else throw "Condition cant be" + first_type;
            }
            else
            {
                if (first_type == "float" || first_type == "int") return res;
                else throw "Condition cant be" + first_type;
            }
        }
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::terminate();
    }
    return res;
}

ConditionElement::ConditionElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{
    m_Type = "bool";
}

void ConditionElement::SetSign(bool flag)
{
    m_Sign = flag;
}
