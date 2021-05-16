//
// Created by kolya on 4/6/21.
//

#pragma once

#include "Element.h"

class ConditionElement : public Element
{
public:
    ConditionElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText() override;
    void SetSign(bool flag);

private:
    bool m_Sign;
};
