#include "DrawPileController.h"

DrawPileController::DrawPileController() 
{
    drawPile = new std::vector<Card>();
};

DrawPileController::~DrawPileController() {};

Card DrawPileController::DrawTop(std::vector<Card>& drawPile)
{
    Card topPileCard = drawPile.back();
    drawPile.pop_back();
    return topPileCard;
}

std::vector<Card> DrawPileController::RequestDrawPile()
{
    return *drawPile;
}