#include "Random3x3.hpp"

Random3x3::Random3x3(TicTacToeData data) : Bot3x3(data){}
Random3x3::~Random3x3(){}


std::pair<int, int> Random3x3::main_fun(){
    std::vector<std::pair<int, int>> possible_moves = Random3x3::generate_possible_moves();
    int idx = rand() % possible_moves.size();
    return possible_moves[idx];
}