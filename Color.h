#pragma once
#include <iostream>
#include <string>

#define NAME_RED "RED"
#define NAME_GREEN "GREEN"
#define NAME_BLUE "BLUE"
#define NAME_YELLOW "YELLOW"
#define NAME_BLACK "BLACK"

class Color
{
private:
    const char* m_colorChar;

public:
    Color();
    Color(const char* colorChar);

    std::string *name;

    std::string* SetName();
    std::string GetColorName();
    char GetCharColor();
    void SetCharColor(const char& newColor);
    void Debug();
};