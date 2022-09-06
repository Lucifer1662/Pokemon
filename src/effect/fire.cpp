#include "fire.h"



Fire::Fire(int damage, Pokemon* target) : damage(damage), target(target) {}



bool Fire::trigger() {
    target->Damage(damage, PokemonType::Fire);
    duration--;
    return duration == 0;
}

