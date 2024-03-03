#pragma once
#include "Card.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>

#define WILD "WILD"
#define SPECIAL "SPECIAL"
#define COMMON "COMMON"

class FoeBehavior
{
public:
    FoeBehavior();
    ~FoeBehavior();

    enum class Behavior;
    Behavior* contestanBehavior;
    static std::map<std::string, std::vector<int>> usableCards;

    void EvaluateCards(std::vector<Card>& allCardsInHand, Color& currentColor, Number& currentNumber);
    void ClearEvaluatedCards();
    int ChooseAvailableCard();
};