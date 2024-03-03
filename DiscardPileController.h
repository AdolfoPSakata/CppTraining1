#pragma once
#include "Card.h"

class DiscardPileController
{
public:
    DiscardPileController();
    ~DiscardPileController();

    std::vector<Card>* discardPile;

    std::vector<Card> RequestDiscardPile();
    void ReceiveDiscard(Card discard);
    void ClearPile();
};