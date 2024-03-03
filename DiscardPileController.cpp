#include "DiscardPileController.h"

DiscardPileController::DiscardPileController()
{
    discardPile = new std::vector<Card>();
};
DiscardPileController::~DiscardPileController() {};

void DiscardPileController::ReceiveDiscard(Card discard)
{
    this->discardPile->emplace_back(discard);
}

std::vector<Card> DiscardPileController::RequestDiscardPile()
{
    return *discardPile;;
}

void DiscardPileController::ClearPile()
{
    this->discardPile->clear();
}