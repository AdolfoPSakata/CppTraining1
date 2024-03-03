#include "Contestant.h"

Contestant::Contestant() {
    hand = new Hand();
}
Contestant::~Contestant(){}


Card Contestant::Discard(const int& index)
{
   return hand->Discard(index);
}

void Contestant::Draw(Card drawCard)
{
    hand->Draw(drawCard);
}

bool& Contestant::GetPlayerStatus()
{
    return *isPlayer;
}


