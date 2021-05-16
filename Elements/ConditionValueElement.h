//
// Created by kolya on 5/15/21.
//

#pragma once

#include "Element.h"

class ConditionValueElement : public Element
{
public:
    ConditionValueElement(const std::shared_ptr<Baobab>& owner) : Element(owner) {}

    virtual std::string GetText() override;

    void SetName(const std::string& name);
    void SetInt(const std::string& num);
    void SetNot(bool flag);

private:
    std::string m_Name;
    std::string m_Int;
    bool m_bNot;
};
