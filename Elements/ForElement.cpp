//
// Created by kolya on 4/18/21.
//

#include "ForElement.h"
#include "Baobab.h"

std::string ForElement::GetText()
{
    try
    {
        std::string result = "for(";
        m_Owner.lock()->OpenBody(true);
        auto i = 0;
        if (m_Children.size() == 4)
        {
            result += m_Children[i]->GetText();
            i++;
        }
        result += ";";
        result += m_Children[i++]->GetText();
        result += ";";
        result += m_Name + " = ";
        result += m_Children[i]->GetText();
        if (m_Owner.lock()->CanAddThisVariable(m_Name))
        {
            if (m_Owner.lock()->GetVariableType(m_Name)
                != m_Children[i++]->GetType())
                throw "Iteration variable not appropriate have type";
        }
        else throw "Variable already exists";
        result += ")";

        result += m_Children[i++]->GetText();

        m_Owner.lock()->OpenBody(false);
        return result;
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::terminate();
    }
}

void ForElement::SetName(const std::string& name)
{
    m_Name = name;
}
