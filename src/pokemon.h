#pragma once

#include <vector>
#include <memory>
#include "effect/effect.h"
#include "move/move.h"
#include "event.h"
#include "pokemonTypes.h"
#include <string>


class Pokemon {
    int max_health;
    int health;
    int attack;
    int speed;
    bool isFainted;
    PokemonType type;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Effect>> effects = {};
    std::string name;

   public:
    Pokemon(int max_health, int attack, int speed, PokemonType type,
            std::vector<std::unique_ptr<Move>>&& moves, bool isFainted)
        : max_health(max_health),
          health(max_health),
          attack(attack),
          speed(speed),
          type(type),
          isFainted(isFainted),
          moves(std::move(moves)) {}

    Event<int /*amount*/, PokemonType> damageEvent;

    void Damage(int amount, PokemonType attackType) {
        health -= amount * TypeDamageMultiplier(attackType, type);
        health = std::max(health, 0);
        damageEvent.Notify(amount, attackType);
    }

    int GetAttack() { return attack; }

    PokemonType GetType() { return type; }

    void UseMove(int i, Pokemon* target) { moves[i]->use(this, target); }

    void ApplyEffects() {
        for (size_t i = 0; i < effects.size();) {
            bool should_remove = effects[i]->trigger();
            if (should_remove) {
                effects[i] = std::move(effects.back());
                effects.pop_back();
            } else {
                i++;
            }
        }
    }

    void AddEffect(std::unique_ptr<Effect>&& effect) {
        effects.push_back(std::move(effect));
    }

    const Move& GetMove(int i) { return *moves[i]; }
    const size_t NumberOfMoves() { return moves.size(); }

    bool isFainted() { return health <= 0; }

    const std::string& GetName() { return name; }
};