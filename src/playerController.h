#pragma once
#include "player.h"
#include "battleSpot.h"

class PlayerController {
    Player* player;
    BattleSpot* battleSpot;
    BattleSpot* enemySpot;

   public:
    PlayerController(Player* player, BattleSpot* battleSpot,
                     BattleSpot* enemySpot)
        : player(player), battleSpot(battleSpot), enemySpot(enemySpot) {}

    void SwapPokemon(int i) {
        battleSpot->ChangePokemon(player->GetPokemon(i));
    }

    void UsePokemonMove(int i) {
        battleSpot->GetPokemon()->UseMove(i, enemySpot->GetPokemon());
    }

    Player& Player() { return *player; }
    BattleSpot& BattleSpotPlayer() { return *battleSpot; }
    BattleSpot& BattleSpotEnemy() { return *enemySpot; }
};