#pragma once 
#include "Bot.hpp"

#define easy_MinMax 1
#define medium_MinMax 2
#define hard_MinMax 3

#define easy_max_sim_MinMax 4
#define medium_max_sim_MinMax 25
#define hard_max_sim_MinMax 70

#define easy_max_deep_MinMax 1
#define medium_max_deep_MinMax 1
#define hard_max_deep_MinMax 2
#define inf 1e9 + 7

class MinMax : public Bot{
public:
    int max_sim, max_deep;

    //constructor and destructor
    MinMax(TicTacToeData data, int mode);
    ~MinMax();

    //metchods
    std::pair<int, int> main_fun();
    int alfa_beta(int deep, int alfa, int beta);
    int heura();
};