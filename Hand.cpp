#include "Hand.h"
#include <iostream>


Hand::Hand(){}
Hand::~Hand() {}

std::vector<Card>* playerHand = new std::vector<Card>();

void Hand::StoreCards(Card cardToStore)
{
    playerHand.emplace_back(cardToStore);
}

Card Hand::Discard(const int& index)
{
    Card currentDiscard = playerHand.at(index);
    playerHand.erase(playerHand.begin() + index);
    std::cout << "DISCARD: " << currentDiscard.number.GetNumberString() << " " << currentDiscard.color.GetColorName() << std::endl;
    return currentDiscard;
}

Card& Hand::PeekCard(const int& index)
{
    Card currentCard = playerHand.at(index);
    return currentCard;
}

void Hand::Draw(Card drawCard)
{
    StoreCards(drawCard);
}