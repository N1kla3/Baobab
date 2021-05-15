//
// Created by kolya on 3/31/21.
//

#include "StatementElement.h"
#include "Baobab.h"


std::string StatementElement::GetText()
{
    try
    {
        if (!m_Name.empty())
        {
            if (m_Owner.lock()->CanAddThisVariable(m_Name))
            {
                auto res = m_Name + "=" + m_Children[0]->GetText() + ";";
                if (m_Owner.lock()->GetVariableType(m_Name)
                    != m_Children[0]->GetType()) throw "Defined variable not the same type with value";
            }
            else throw "Duplicate variable name";
        }
        else if (!m_Children.empty())
        {
            auto res = m_Children[0]->GetText() + ';';
            m_Type = m_Children[0]->GetType();
            return res;
        }
        return "";
    }
    catch (const char* message)
    {
        std::cerr << message << std::endl;
        std::exit(0);
    }
}

void StatementElement::SetName(const std::string& name)
{
    m_Name = name;
}
