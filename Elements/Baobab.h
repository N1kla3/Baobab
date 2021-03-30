//
// Created by kolya on 3/30/21.
//

#pragma once

#include "Element.h"
#include <memory>
#include <string>

class Baobab
{
public:
    void WriteTreeTo(const std::string& filePath);
    void AddElement(std::unique_ptr<Element>&& element);

private:
    std::unique_ptr<Element> m_Root;
};

