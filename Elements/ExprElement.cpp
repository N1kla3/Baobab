//
// Created by kolya on 4/6/21.
//

#include "ExprElement.h"
#include "Baobab.h"

ExprElement::ExprElement(const std::shared_ptr<Baobab>& owner)
    : Element(owner)
{

}

std::string ExprElement::GetText()
{
    if (!m_Value.empty())
    {
        m_Type = "std::string";
        return m_Value;
    }
    else if (!m_Name.empty())
    {
        if (!m_Owner.lock()->CanAddThisVariable(m_Name)) throw std::exception();
        m_Type = m_Owner.lock()->GetVariableType(m_Name);
        return m_Name;
    }
    else if (!m_Int.empty())
    {
        m_Type = "int";
        return m_Int;
    }
    else if (!m_Sign.empty())
    {
        std::string res{};
        if (m_Sign != "-" ||
            m_Sign != "+" ||
            m_Sign != "*") throw std::exception();
        res += HandleWithSign(m_Sign);
        return res;
    }
    else
    {
        auto res = m_Children[0]->GetText();
        m_Type = m_Children[0]->GetType();
        return res;
    }
}

void ExprElement::SetSignIfHave(const std::string& sign)
{
    m_Sign = sign;
}

void ExprElement::SetValueIfHave(const std::string& value)
{
    m_Value = value;
}

void ExprElement::SetNameIfHave(const std::string& value)
{
    m_Name = value;
}

void ExprElement::SetIntIfHave(const std::string& value)
{
    m_Int = value;
}

std::string ExprElement::HandleWithSign(const std::string& sign)
{
    auto res = m_Children[0]->GetText() + sign + m_Children[1]->GetText();
    auto type = m_Children[0]->GetType();
    if (type != m_Children[1]->GetType())
        throw std::exception();
    if (type == "bool" || type == "std::string" || type == "std::variant<int, float, std::string, bool>"
        || type == "std::vector<std::variant<int, float, std::string, bool>>") throw std::exception();
    m_Type = type;
    return res;
}
