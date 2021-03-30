//
// Created by kolya on 3/30/21.
//

#include "Baobab.h"
#include <fstream>

void Baobab::WriteTreeTo(const std::string& filePath)
{
    std::ofstream file;
    file.open(filePath);
    if (file.is_open())
    {
        file << m_Root->GetText();
    }
    file.close();
}

void Baobab::AddElement(std::unique_ptr<Element>&& element)
{
    m_Root = std::move(element);
}
