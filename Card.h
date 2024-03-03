#pragma once
#include <vector>

#include "Color.h"
#include "Number.h"

class Card
{
public:
	Card();
	Card(char* color, int* number);
	~Card();

	void Debug(int index);
	Color color;
	Number number;
};