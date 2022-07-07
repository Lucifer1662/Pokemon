#pragma once
#include "player.h"
#include "battleSpot.h"
#include "pokemon.h"

class Battle {
    bool isPlayer1Turn = false;
    Player* player1;
    Player* player2;

    BattleSpot player1_battlespot;
    BattleSpot player2_battlespot;

   public:
    Battle(Player* player1, Player* player2)
        : player1(player1), player2(player2) {}

    void StartBattle() {
        player1_battlespot.ChangePokemon(player1->GetPokemon(0));
        player1_battlespot.ChangePokemon(player2->GetPokemon(0));
    }

    void EndTurn() {
        if (isPlayer1Turn) {
            player1_battlespot.GetPokemon()->ApplyEffects();
        } else {
            player2_battlespot.GetPokemon()->ApplyEffects();
        }
        isPlayer1Turn = !isPlayer1Turn;
    }

    BattleSpot& GetBattleSpot(Player* player) {
        if (player1 == player) {
            return player1_battlespot;
        } else {
            return player2_battlespot;
        }
    }

    bool isOver() { return player1->allFainted() || player1->allFainted(); }

    enum class BattleResult { Player1Wins, Player2Wins, Draw, OnGoing };

    BattleResult Result() {
        if (player1->allFainted() && player2->allFainted())
            return BattleResult::Draw;

        if (!player1->allFainted() && !player2->allFainted())
            return BattleResult::OnGoing;

        if (!player1->allFainted()) return BattleResult::Player1Wins;

        if (!player2->allFainted()) return BattleResult::Player2Wins;
    }
};