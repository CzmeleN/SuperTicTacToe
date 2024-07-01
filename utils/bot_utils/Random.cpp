#include "Random.hpp"

Random::Random(TicTacToeData data) : Bot(data) {}
Random::~Random(){} 

std::pair<int, int> Random::main_fun(){
    std::vector<std::pair<int, int>> possible_moves = Random::generate_possible_moves();
    int idx = rand() % possible_moves.size();
    return possible_moves[idx];
}