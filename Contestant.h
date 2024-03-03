#pragma once
#include "Card.h"
#include "Hand.h"

class Contestant
{
public:
    Contestant();
    ~Contestant();
    
    Hand* hand;
    bool* isPlayer = new bool;
    bool* calledUno = new bool;

    Card Discard(const int& index);
    bool& GetPlayerStatus();
    void Draw(Card drawCard);
    void Shout();
};