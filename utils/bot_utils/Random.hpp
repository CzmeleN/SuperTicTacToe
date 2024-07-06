#pragma once
#include "Bot.hpp"

// implementation of random bot
class Random : public Bot{
public:

    //constructor and destructor
    Random(TicTacToeData data);
    ~Random();

    //metchods
    std::pair<int, int> main_fun();
};