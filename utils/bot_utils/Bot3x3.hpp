#pragma once 
#include <bits/stdc++.h>
#include "../include/game_data.hpp"

class Bot3x3{
public:
    TicTacToeData data;
    Sign min_player, max_player;
    
    Bot3x3(TicTacToeData data);
    ~Bot3x3();

    //metchods
    std::vector<std::pair<int, int>> generate_possible_moves();
    void change_player();
    void print();
    bool game_over();
    Sign game_score();
};