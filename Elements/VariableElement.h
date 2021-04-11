//
// Created by kolya on 4/10/21.
//

#pragma once

#include "Element.h"

class VariableElement : public Element
{
public:
    VariableElement(const std::shared_ptr<Baobab>& owner);
    virtual std::string GetText()  override;
    void SetWithEquality(bool haveEquality);
    void SetName(const std::string& name);

private:
    bool m_bWithEquality;
    std::string m_Name;
};

//TODO get types if needed