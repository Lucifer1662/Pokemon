#pragma once


class BattleSpot {
    Pokemon* pokemon;

   public:
    void ChangePokemon(Pokemon* p) { pokemon = p; }
    Pokemon* GetPokemon() { return pokemon; }
};
