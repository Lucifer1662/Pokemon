#pragma once
struct PlayerInput;

struct BattleController {
    Battle* battle;
    PlayerInput* player1Input;
    PlayerInput* player2Input;

    BattleController(Battle* battle, PlayerInput* player1Input,
                     PlayerInput* player2Input);

   public:
    void run();
};