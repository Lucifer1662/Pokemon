#pragma once

Pokemon CreateChimChar() {
    std::vector<std::unique_ptr<Move>> moves;
    moves.push_back(std::make_unique<FireBlast>());
    return Pokemon(100, 20, 80, PokemonType::Fire, std::move(moves), false);
}