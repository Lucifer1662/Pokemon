#pragma once
#include "effect.h"
#include "../pokemon.h"

class Fire : public Effect {
    int damage;
    Pokemon* target;
    int duration = 5;

   public:
    Fire(int damage, Pokemon* target);

    bool trigger() ;
};