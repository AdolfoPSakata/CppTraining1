#pragma once
#include <iostream>
#include <string>

#define INVERT_NAME "INVERT"
#define DRAWTWO_NAME "DRAW 2"
#define BLOCK_NAME "BLOCK"
#define DRAWFOUR_NAME "DRAW 4"
#define CHANGECOLOR_NAME "CHANGE COLOR"

class Number
{
private:
    const int* m_numberValue;

public:
    Number();
    Number(const int* numberValue);

    int GetNumberValue();
    void SetNumberValue();
    std::string GetNumberString();
    void Debug();
};