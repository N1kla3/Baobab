//
// Created by kolya on 4/6/21.
//

#pragma once

#include "Element.h"

class ExprElement : public Element
{
public:
    ExprElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText() override;
    void SetSignIfHave(const std::string& sign);
    void SetValueIfHave(const std::string& value);
    void SetNameIfHave(const std::string& value);
    void SetIntIfHave(const std::string& value);

    std::string HandleWithSign(const std::string& sign);

private:
    std::string m_Sign;
    std::string m_Value;
    std::string m_Name;
    std::string m_Int;
};
