#include "DeckManager.h"

DeckManager::DeckManager(){}
DeckManager::~DeckManager(){}

void DeckManager::Init()
{
	allCards = CreateDeck();
}

char* DeckManager::GetSuit(int suitIndex)
{
	char* currentSuitPtr = &suitsList[suitIndex];
	return currentSuitPtr;
}

const int& DeckManager::GetCardsPerSuit()
{
	return (MAX_CARDS - MAX_WILD_CARDS) / MAX_SUITS;
}

std::vector<Card>* DeckManager::CreateDeck()
{
	std::vector<Card>* cardVectorPrt = new std::vector<Card>();

	for (int suitIndex = 0; suitIndex < MAX_SUITS; suitIndex++)
	{
		char* currentSuitPtr = &suitsList[suitIndex];
		for (int i = 0; i < DeckManager::GetCardsPerSuit() - 1; i++)
		{
			int* currentNumberPrt;
			
			if (i >= 12)
				currentNumberPrt = &numberList[i - (sizeof(numberList) / sizeof(int))];
			else
				currentNumberPrt = &numberList[i];
				
			cardVectorPrt->emplace_back(currentSuitPtr, currentNumberPrt);
			
			currentNumberPrt = NULL;
		}
		currentSuitPtr = NULL;
	}

	for (int wildCardType = 0; wildCardType < MAX_WILD_TYPES; wildCardType++)
	{
		int* currentNumberPrt;
		char* currentSuitPtr = &suitsList[MAX_SUITS];
		
		for (int wildCartIndex = 0; wildCartIndex  < MAX_WILD_CARDS / MAX_WILD_TYPES; wildCartIndex++)
		{
			currentNumberPrt = &wildCardList[wildCardType];
			cardVectorPrt->emplace_back(currentSuitPtr, currentNumberPrt);
		}

		currentNumberPrt = NULL;
	}

	DeckManager::ShuffleDeck(*cardVectorPrt);

	return cardVectorPrt;
}

void DeckManager::ShuffleDeck(std::vector<Card>& array)
{
	int size = array.size();
	srand(time(0));

	for (int i = size - 1; i > 0; --i) {

		int j = rand() % (i + 1);
		Card swapingCard = array[i];
		
		array[i] = array[j];
		array[j] = swapingCard;
	}	
}

Card& DeckManager::FirstCard()
{
	do
	{
		Card topPileCard = allCards->back();
		if (topPileCard.color.GetCharColor() != 'n')
		{
			allCards->pop_back();
			return topPileCard;
		}
	}while(true);
}

Card& DeckManager::DealCards()
{
	Card topPileCard = allCards->back();
	allCards->pop_back();
	return topPileCard;
}

void DeckManager::SendToDiscard(Card discard)
{
	discardController->discardPile->emplace_back(discard);
}

Card* DeckManager::GetLastDiscard()
{
	return &discardController->discardPile->back();
}

void DeckManager::SendToDrawPile(DiscardPileController& discard, DrawPileController& draw)
{
	draw.RequestDrawPile() = discard.RequestDiscardPile();
}
