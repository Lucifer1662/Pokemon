
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "event.h"
#include "pokemonTypes.h"
#include "pokemon.h"
#include "move/move.h"
#include "effect/effect.h"
#include "effect/fire.h"
#include "move/move.h"
#include "player.h"
#include "battleSpot.h"
#include "battle.h"
#include "playerController.h"
#include "pokemons/chimchar.h"
#include "playerInput/playerInput.h"
#include "playerInput/cmdPlayerInput.h"
#include "battleController.h"


void main() {
    std::vector<Pokemon> pokemons;

    pokemons.push_back(CreateChimChar());
    Player player1(std::move(pokemons));

    pokemons.push_back(CreateChimChar());
    Player player2(std::move(pokemons));

    Battle battle(&player1, &player2);

    PlayerController playerController1(&player1,
                                       &battle.GetBattleSpot(&player1),
                                       &battle.GetBattleSpot(&player2));
    PlayerController playerController2(&player2,
                                       &battle.GetBattleSpot(&player2),
                                       &battle.GetBattleSpot(&player1));

    CmdPlayerInput player1Input(playerController1, battle);
    CmdPlayerInput player2Input(playerController2, battle);

    BattleController battleController(&battle, &player1Input, &player2Input);

    battleController.run();
}
