
#include "Number.h"

Number::Number(){}
Number::Number(const int* numberValue) : m_numberValue(numberValue) {};

int newValue = -1;

int Number::GetNumberValue()
{
    return *m_numberValue;
}

std::string Number::GetNumberString()
{
    if (*m_numberValue == 10)
        return INVERT_NAME; 
    else if (*m_numberValue == 11)
        return DRAWTWO_NAME;
    else if (*m_numberValue == 12)
        return BLOCK_NAME;
    else if (*m_numberValue == 13)
        return DRAWFOUR_NAME;
    else if (*m_numberValue == 14)
        return CHANGECOLOR_NAME;
    else if (*m_numberValue == -1)
        return "ANY";
    else
        return std::to_string(*m_numberValue);
}


void Number::SetNumberValue()
{
    m_numberValue = &newValue;
}

void Number::Debug()
{
    std::cout << GetNumberString();
}
