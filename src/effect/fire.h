#pragma once

class Fire : public Effect {
    int damage;
    Pokemon* target;
    int duration = 5;

   public:
    Fire(int damage, Pokemon* target) : damage(damage), target(target) {}

    bool trigger() {
        target->Damage(damage, PokemonType::Fire);
        duration--;
        return duration == 0;
    }
};