#pragma once
#include <iostream>
#include "../battleController.h"
#include "../playerController.h"
#include "../battle.h"
#include "../battleSpot.h"
#include "../pokemon.h"
#include "../move/move.h"

struct CmdPlayerInput : public PlayerInput {
    PlayerController& controller;
    Battle& battle;

    CmdPlayerInput(PlayerController& controller, Battle& battle)
        : controller(controller), battle(battle) {}

    void makeDecision() {
        int move;
        std::cin >> move;
        auto& pokemon = *controller.BattleSpotPlayer().GetPokemon();
        std::cout << "Pokemon: "  << pokemon.GetName() << std::endl;
        for (size_t i = 0; i < pokemon.NumberOfMoves(); i++)
            std::cout << i  << ": "  << pokemon.GetMove(i).getName() << std::endl;
        std::cout << "Enter move number" << std::endl;
        controller.UsePokemonMove(move);
    }
};