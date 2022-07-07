#pragma once
#include <string>
#include "../pokemonTypes.h"
#include "../pokemon.h"
#include "../effect/fire.h"

class Move {
    int max_pp;
    int pp;
    PokemonType type;
    std::string name;

   public:
    virtual void use(Pokemon* attacker, Pokemon* attackee) = 0;
    int getPP() { return pp; }
    int getMaxPP() { return max_pp; }
    PokemonType getType() { return type; }
    const std::string& getName() const { return name; }
};class FireBlast : public Move {
    virtual void use(Pokemon* attacker, Pokemon* attackee) {
        attackee->Damage(attacker->GetAttack(), PokemonType::Fire);
        if (rand() % 5 == 0) {
            attackee->AddEffect(
                std::make_unique<Fire>(attacker->GetAttack(), attackee));
        }
    }
};