
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

template <typename... Args>
class Event {
    using Listeners = std::list<std::function<void(Args...)>>;
    using It = Listerners::It;
    Listeners listeners;
    bool currentlyExecuting = true;

   public:
    template <typename Func>
    It Add(Func&& func) {
        listeners.push_back(std::forward<Func>(func));
        return std::prev(listeners.end());
    }

    void Remove(It it) { listeners.erase(it); }

    void Notify(Args... args) {
        for (auto it = listeners.begin(); it != listeners.end(); it++) {
            (*it)(std::forward<Args>(args)...);
        }
    }
};

enum class PokemonType { Fire = 0, Water = 1, Grass = 2 };

enum Effectiveness {
    Normal = 0,
    Effective,
    Super_Effective,
    Not_Very_Effective,
    No_Effect
};

std::vector<std::vector<Effectiveness>> effectiveness = {
    {Normal, Not_Very_Effective, Super_Effective},
    {Super_Effective, Normal, Not_Very_Effective},
    {Not_Very_Effective, Super_Effective, Normal},
};

std::vector<double> damageEffectiveness = {1, 1.5, 2, 0.5, 0};

double TypeDamageMultiplier(PokemonType p1, PokemonType p2) {
    return damageEffectiveness[effectiveness[(int)p1][(int)p2]];
}

class Pokemon {
    int max_health;
    int health;
    int attack;
    int speed;
    bool isFainted;
    PokemonType type;
    std::vector<std::unique_ptr<Move>> moves;
    std::vector<std::unique_ptr<Effect>> effects = {};

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

    bool isFainted() { return health <= 0; }
};

class Move {
    int max_pp;
    int pp;
    PokemonType type;

   public:
    virtual void use(Pokemon* attacker, Pokemon* attackee) = 0;
    int getPP() { return pp; }
    int getMaxPP() { return max_pp; }
    PokemonType getType() { return type; }
};

struct Effect {
    virtual bool trigger() = 0;
    virtual ~Effect() = default;
};

class Fire : public Effect {
    int damage;
    Pokemon* target;
    int duration = 5;

   public:
    Fire(int damage, Pokemon* target) : damage(damage), target(target) {}

    bool trigger() {
        target->Damage(damage, PokemonType::Fire);
        duration--;
        return duration == 0;
    }
};

class FireBlast : public Move {
    virtual void use(Pokemon* attacker, Pokemon* attackee) {
        attackee->Damage(attacker->GetAttack(), PokemonType::Fire);
        if (rand() % 5 == 0) {
            attackee->AddEffect(
                std::make_unique<Fire>(attacker->GetAttack(), attackee));
        }
    }
};

class Player {
    std::vector<Pokemon> pokemons;

   public:
    Player(std::vector<Pokemon>&& pokemons) : pokemons(std::move(pokemons)) {}

    Pokemon* GetPokemon(int i) { return &pokemons[i]; }

    bool allFainted() {
        return std::all_of(pokemons.begin(), pokemons.end(),
                           [](auto& p) { p.isFainted() });
    }
};

class BattleSpot {
    Pokemon* pokemon;

   public:
    void ChangePokemon(Pokemon* p) { pokemon = p; }
    Pokemon* GetPokemon() { return pokemon; }
};

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

class PlayerController {
    Player* player;
    BattleSpot* battlespot;
    BattleSpot* enemyspot;
   public:

    PlayerController(Player* player, BattleSpot* battlespot,
                     BattleSpot* enemyspot)
        : player(player), battlespot(battlespot), enemyspot(enemyspot) {}

    void SwapPokemon(int i) {
        battlespot->ChangePokemon(player->GetPokemon(i));
    }

    void UsePokemonMove(int i) {
        battlespot->GetPokemon()->UseMove(i, enemyspot->GetPokemon());
    }
};

Pokemon CreateChimChar() {
    std::vector<std::unique_ptr<Move>> moves;
    moves.push_back(std::make_unique<FireBlast>());
    return Pokemon(100, 20, 80, PokemonType::Fire, std::move(moves), false);
}

struct PlayerInput {
    virtual void makeDecision();
    virtual ~PlayerInput() = default;
};

struct CmdPlayerInput {
    PlayerController& controller;
    

    void makeDecision() {
        int move;
        std::cin >> move;
        controller.UsePokemonMove(move);
    }
};

struct BattleController{
    Battle* battle;
    PlayerInput* player1Input;
    PlayerInput* player2Input;

    public:


    void run(){
        battle->StartBattle();
        while(!battle->isOver()){

            battle->EndTurn();
        }
    }

};

void main() {
    std::vector<Pokemon> pokemons;


    pokemons.push_back(CreateChimChar());
    Player player1(std::move(pokemons));



    pokemons.push_back(CreateChimChar());
    Player player2(std::move(pokemons));

    Battle battle(&player1, &player2);

    PlayerController playerController1(&player1, &battle.GetBattleSpot(&player1),  &battle.GetBattleSpot(&player2));
    PlayerController playerController2(&player2, &battle.GetBattleSpot(&player2),  &battle.GetBattleSpot(&player1));




    battle.StartBattle();

    battle.EndTurn();
}
