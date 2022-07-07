#pragma once

#include <vector>
#include "Pokemon.h"
#include <algorithm>

class Player {
    std::vector<Pokemon> pokemons;

   public:
    Player(std::vector<Pokemon>&& pokemons) : pokemons(std::move(pokemons)) {}

    Pokemon* GetPokemon(int i) { return &pokemons[i]; }

    size_t NumberOfPokemon() { return pokemons.size(); }

    bool allFainted() {
        return std::all_of(pokemons.begin(), pokemons.end(),
                           [](auto& p) { p.isFainted() });
    }
};