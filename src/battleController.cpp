#include "battleController.h"
#include "playerInput/playerInput.h"
#include "battle.h"

BattleController::BattleController(Battle* battle, PlayerInput* player1Input,
                 PlayerInput* player2Input)
    : battle(battle),
      player1Input(player1Input),
      player2Input(player2Input) {}



void BattleController::run() {
    battle->StartBattle();
    PlayerInput* currentPlayer = player1Input;
    PlayerInput* nextPlayer = player2Input;
    while (!battle->isOver()) {
        player1Input->makeDecision();
        battle->EndTurn();
        std::swap(currentPlayer, nextPlayer);
    }
}

