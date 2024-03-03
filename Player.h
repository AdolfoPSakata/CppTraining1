#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

#include "Card.h"
#include "Hand.h"
#include "Contestant.h"

class Player : public Contestant
{
public:
    Player();
    Player(bool playerStatus);
    ~Player();

    int& GetPlayerInput();
    bool EvaluateInput(Card& discard, Color& currentColor, Number& currentNumber);
};