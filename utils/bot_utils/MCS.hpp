#pragma once 
#include "Bot.hpp"

#define easy 7
#define medium 8
#define hard 9
#define easy_max_sim 150
#define medium_max_sim 750
#define hard_max_sim 15000

// implementation of monte carlo simulaton for bot
class MCS : public Bot{
public:
    int max_sim;

    //constructor and destructor
    MCS(TicTacToeData data, int mode);
    ~MCS();

    //metchods
    std::pair<int, int> main_fun();
    int make_symulations(int n);
};

