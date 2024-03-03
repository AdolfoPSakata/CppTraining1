#pragma once
#include "Card.h"

class DrawPileController
{
public:
    DrawPileController();
    ~DrawPileController();

    std::vector<Card>* drawPile;

    std::vector<Card>  RequestDrawPile();
    Card DrawTop(std::vector<Card>& drawPile);
};