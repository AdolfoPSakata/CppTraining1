#include "Color.h"

Color::Color() {}
Color::Color(const char* colorChar)
{
    m_colorChar = colorChar;
    name = SetName();
}

char Color::GetCharColor() 
{
    return *m_colorChar;
}

void Color::SetCharColor(const char& newColor)
{
    m_colorChar = &newColor;
}

std::string* Color::SetName()
{
    std::string* nameTemp = new std::string;

    if (*m_colorChar == 'r')
        *nameTemp = NAME_RED;

    else if (*m_colorChar == 'g')
        *nameTemp = NAME_GREEN;

    else if (*m_colorChar == 'b')
        *nameTemp = NAME_BLUE;

    else if (*m_colorChar == 'a')
        *nameTemp = NAME_YELLOW;

    else if (*m_colorChar == 'n')
        *nameTemp = NAME_BLACK;

    return nameTemp;
}

std::string Color::GetColorName()
{
    return *name;
}

void Color::Debug()
{
    std::cout << GetColorName();
}

