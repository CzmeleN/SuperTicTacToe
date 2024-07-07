#pragma once 
#include "Bot3x3.hpp"

class Random3x3 : public Bot3x3{
public:

    //constructor and destructor
    Random3x3(TicTacToeData data);
    ~Random3x3();

    //metchods
    std::pair<int, int> main_fun();
};