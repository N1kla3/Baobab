//
// Created by kolya on 4/26/21.
//
#pragma once

#include "Element.h"

class StopElement : public Element
{
public:
    StopElement(const std::shared_ptr<Baobab>& owner)
        : Element(owner){}
    virtual std::string GetText() override;
    void SetWord(const std::string& word);

private:
    std::string m_Word;
};
