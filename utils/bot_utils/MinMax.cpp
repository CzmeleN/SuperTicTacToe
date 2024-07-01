#include "MinMax.hpp"

MinMax::MinMax(TicTacToeData data, int mode) : Bot(data){
    if(mode == easy){
        max_sim = easy_max_sim;
        max_deep = easy_max_deep;
    }
    else if(mode == medium){
        max_sim = medium_max_sim;
        max_deep = medium_max_deep;
    }
    else{
        max_sim = hard_max_sim;
        max_deep = hard_max_deep;
    }
}

MinMax::~MinMax(){}