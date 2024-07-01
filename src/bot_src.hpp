#pragma once 
#include <bits/stdc++.h>
#include "../include/game_data.hpp"
#include "../utils/bot_utils/Bot.hpp"
#include "../utils/bot_utils/MCS.hpp"
#include "../utils/bot_utils/Random.hpp"
#include "../utils/bot_utils/MinMax.hpp"

/*
    return values:
        generate_bot_move returns coordinates (x, y) for place to put sign

    assumptions:
        if bot can't do move in the given sector (data.sector file: game_data.hpp) it will change sector on 9 (do move in any sector)
        if you try to make a move on a board where the game is over, you will get undefined behavior. (just don't do it)

    modes:
        0 - bot 9x9 random

        1 - bot 9x9 min_max easy
        2 - bot 9x9 min_max medium
        3 - bot 9x9 min_max hard

        4 - bot 9x9 mcts easy
        5 - bot 9x9 mcts medium
        6 - bot 9x9 mcts hard

        7 - bot mcs easy
        8 - bot mcs medium
        9 - bot mcs hard
*/

std::pair<int, int> generate_bot_move(TicTacToeData data, int mode);
std::pair<int, int> generate_bot_move9x9(TicTacToeData data, int mode);
std::pair<int, int> generate_bot_move3x3(TicTacToeData data, int mode); //TODO