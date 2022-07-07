#pragma once

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
