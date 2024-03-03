#include "Player.h"


#define INVERT 10
#define DRAWTWO 11
#define BLOCK 12
#define DRAWFOUR 13
#define CHANGECOLOR 14
#define NAME_BLACK 'n'

Player::Player(){}
Player::Player(bool playerStatus)
{
    *isPlayer = playerStatus;
	*calledUno = false;
}
Player::~Player() {}

int& Player::GetPlayerInput()
{
	int input;
	std::cin >> input;
	return input;
}

bool Player::EvaluateInput(Card& discard, Color& currentColor, Number& currentNumber)
{
	int numberOnDiscard = currentNumber.GetNumberValue();
	char colorOnDiscard = currentColor.GetCharColor();
		
	int cardNumber = discard.number.GetNumberValue();
	char colorChar = discard.color.GetCharColor();

	if (numberOnDiscard == DRAWFOUR)
	{
		if (cardNumber == DRAWFOUR)
			return true;
		else
			return false;
	}
	else if (numberOnDiscard == DRAWTWO)
	{
		if (cardNumber == DRAWTWO)
			return true;
		else
			return false;
	}
	else if ((colorChar == colorOnDiscard) || (cardNumber == numberOnDiscard))
	{
		return true;
	}
	else if (colorChar == NAME_BLACK)
		return true;
	else
		return false;
	
}

