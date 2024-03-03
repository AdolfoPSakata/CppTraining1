#include <iostream>
#include "Card.h"

Card::Card() {};

Card::Card(char* color, int* number)
{
	Color newColor(color);
	Number newNumber(number);
	this->color = newColor;
	this->number = newNumber;
};

Card::~Card() {};

void Card::Debug(int index) 
{
	std::cout << "[" << index << "] - " <<  color.GetColorName() << " " << number.GetNumberValue() << std::endl;
}


