#pragma once 
#include "Bot.hpp"

#define easy 1
#define medium 2
#define hard 3
#define easy_max_sim 20
#define medium_max_sim 20
#define hard_max_sim 20
#define easy_max_deep 2
#define medium_max_deep 3
#define hard_max_deep 4
#define inf 1e9 + 7

class MinMax : public Bot{
public:
    int max_sim, max_deep;

    //constructor and destructor
    MinMax(TicTacToeData data, int mode);
    ~MinMax();

    //metchods
    std::pair<int, int> main_fun();
};