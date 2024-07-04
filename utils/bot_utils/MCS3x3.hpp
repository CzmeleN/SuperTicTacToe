#pragma once 
#include "Bot3x3.hpp"

#define easy_mcs_3x3 11
#define medium_mcs_3x3 12 
#define hard_mcs_3x3 13

#define easy_mcs_3x3_max_sim 4
#define medium_mcs_3x3_max_sim 18
#define hard_mcs_3x3_max_sim 2500

class MCS3x3 : public Bot3x3{
public:
    int max_sim;

    //constructor and destructor
    MCS3x3(TicTacToeData data, int mode);
    ~MCS3x3();

    //metchods
    std::pair<int, int> main_fun();
    int make_symulations(int n);
};