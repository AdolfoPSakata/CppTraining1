#pragma once
#include "Contestant.h"
#include "FoeBehavior.h" 

class Foe : public Contestant
{
public:
    Foe();
    Foe(bool isPlayer);
    ~Foe();
   
    FoeBehavior* behavior = new FoeBehavior;
};