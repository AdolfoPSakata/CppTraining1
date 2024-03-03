#include "FoeBehavior.h"

#define INVERT 10
#define DRAWTWO 11
#define BLOCK 12
#define DRAWFOUR 13
#define CHANGECOLOR 14

std::map<std::string, std::vector<int>> FoeBehavior::usableCards = std::map<std::string, std::vector<int>>
{
	{WILD, std::vector<int>()},
	{SPECIAL, std::vector<int>()},
	{COMMON, std::vector<int>()}
};


enum class FoeBehavior::Behavior
{
	Agressive,
	Moderate,
	Easy
};


FoeBehavior::FoeBehavior()
{
	//Behavior enum count
	int i = rand() % 3;
	contestanBehavior = new FoeBehavior::Behavior();
	*contestanBehavior = (FoeBehavior::Behavior)i;
};

FoeBehavior::~FoeBehavior(){};


void FoeBehavior::EvaluateCards(
	std::vector<Card>& allCardsInHand, Color& currentColor, Number& currentNumber)
{
	int numberOnDiscard = currentNumber.GetNumberValue();
	char colorOnDiscard = currentColor.GetCharColor();

	for (int i = 0; i < allCardsInHand.size(); i++)
	{
		int cardNumber = allCardsInHand[i].number.GetNumberValue();
		char colorChar = allCardsInHand[i].color.GetCharColor();

		if (numberOnDiscard == DRAWFOUR)
		{
			if(cardNumber == DRAWFOUR)
				usableCards.find(WILD)->second.emplace_back(i);
			
			return;
		}

		else if (numberOnDiscard == DRAWTWO)
		{
			if (cardNumber == DRAWTWO)
				usableCards.find(SPECIAL)->second.emplace_back(i);
			
			return;
		}
		else if ((colorChar == colorOnDiscard) || (cardNumber == numberOnDiscard))
		{
			usableCards.find(COMMON)->second.emplace_back(i);
		}
		else if (colorChar == 'n')
		{
			usableCards.find(WILD)->second.emplace_back(i);
		}
	}
}

void FoeBehavior::ClearEvaluatedCards()
{
	usableCards.at(WILD).clear();
	usableCards.at(SPECIAL).clear();
	usableCards.at(COMMON).clear();
}

int FoeBehavior::ChooseAvailableCard()
{
	std::cout << usableCards.at(WILD).size() << std::endl;
	std::cout << usableCards.at(SPECIAL).size() << std::endl;
	std::cout << usableCards.at(COMMON).size() << std::endl;
	if (usableCards.at(WILD).size() > 0 )
		return usableCards.at(WILD)[0];

	else if (usableCards.at(SPECIAL).size() > 0)
		return usableCards.at(SPECIAL)[0];

	else if (usableCards.at(COMMON).size() > 0)
		return usableCards.at(COMMON)[0];

	else
		return -1;
}

