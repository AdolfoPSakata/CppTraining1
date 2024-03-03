#include <iostream>
#include "Foe.h"

Foe::Foe() {}
Foe::Foe(bool playerStatus)
 {
    *isPlayer = playerStatus;
    *calledUno = false;
 }

Foe::~Foe() {};



