#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "DrawPileController.h"
#include "DiscardPileController.h"
#include "Card.h"

#define INVERT 10
#define DRAWTWO 11
#define BLOCK 12
#define DRAWFOUR 13
#define CHANGECOLOR 14

#define RED 'r'
#define GREEN 'g'
#define BLUE 'b'
#define YELLOW 'a'
#define BLACK 'n'

class DeckManager
{
public:
    const int INITIAL_CARDS = 7;
    const int MAX_CARDS = 108;
    const int MAX_SUITS = 4;
    const int MAX_WILD_CARDS = 8;
    const int MAX_WILD_TYPES = 2;
    const int MAX_SPECIAL_CARDS = 24;

    DeckManager();
    ~DeckManager();

    std::vector<Card>* allCards = new std::vector<Card>();
    Card topCard;
    
    void Init();
    char* GetSuit(int suitIndex);
    void SendToDrawPile(DiscardPileController& discard, DrawPileController& draw);
    Card* GetLastDiscard();
    void SendToDiscard(Card discard);
    std::vector<Card>* CreateDeck();
    Card& DealCards();
    Card& FirstCard();
private:

    char suitsList[5] = { RED, GREEN, BLUE, YELLOW, BLACK};
    int numberList[12] = { 1,2,3,4,5,6,7,8,9,INVERT,DRAWTWO,BLOCK };
    int wildCardList[2] = { DRAWFOUR, CHANGECOLOR };
    
    DiscardPileController* discardController = new DiscardPileController();
	DrawPileController* drawController = new DrawPileController();

    void ShuffleDeck(std::vector<Card>& array);
    void CheckTopCardSkill(Card discard);
    const int& GetCardsPerSuit();
};