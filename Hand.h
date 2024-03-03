#pragma once
#include <vector>
#include "Card.h"

class Hand
{
public:
    Hand();
   ~Hand();

   std::vector<Card> playerHand;

    void StoreCards(Card cardToStore);
    void Draw(Card drawCard);
    Card Discard(const int& index);
    Card& PeekCard(const int& index);
};