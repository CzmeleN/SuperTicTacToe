#pragma once 
#include <bits/stdc++.h>
#include "../include/game_data.hpp"

class Bot{
public:
    //data that
    TicTacToeData data;
    Sign min_player, max_player;
    std::vector<Sign> subgame_score;

    //constructor and destructor
    Bot(TicTacToeData data);
    ~Bot();

    //metchods for doing move
    void put_sign(int x, int y);
    void unput_sign(int x, int y);

    //metchods for setting game info
    Sign game_score();
    void set_subgame_info();    //invoke this at the beginning to get subgame_score

    //metchods subgames info
    inline int idx_of_subgame(int x, int y);
    int idx_of_next_subgame(int x, int y);
    inline std::pair<int, int> corner_of_subgame(int idx);
    void update_subgame(int idx);

    //metchods for generating moves
    std::vector<std::pair<int, int>> generate_possible_moves();
    std::vector<std::pair<int, int>> generate_possible_moves_in_sector(int idx);

    //miscallenous metchods
    void change_player();
    void print();
    bool game_over();
};