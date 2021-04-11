//
// Created by kolya on 4/6/21.
//

#pragma once

#include "Element.h"

class ExprElement : public Element
{
public:
    ExprElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText()  override;
    void SetType(bool type);
    void SetSignIfHave(const std::string& sign);

private:
    bool m_bType;
    std::string m_Sign;
};

