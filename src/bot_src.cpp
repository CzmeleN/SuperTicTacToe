#include "bot_src.hpp"

std::pair<int, int> generate_bot_move(TicTacToeData data, int mode){
    if(data.super_mode) return generate_bot_move9x9(data, mode);
    return generate_bot_move3x3(data, mode);
}

std::pair<int, int> generate_bot_move9x9(TicTacToeData data, int mode){
    if(mode == 0){
        Random agent = Random(data);
        return agent.main_fun();
    }
    else if(mode == 1 || mode == 2 || mode == 3){
        MinMax agent = MinMax(data, mode);
        return agent.main_fun();
    }
    else if(mode == 4 || mode == 5 || mode == 6){
        MCTS agent = MCTS(data, mode);
        return agent.main_fun();
    }
    else if(mode == 7 || mode == 8 || mode == 9){
        MCS agent = MCS(data, mode);
        return agent.main_fun();
    }
    else{ 
        std::cout << "game mode is wrong" << std::endl;
        exit(69);
    }
    
    return {-1, -1}; 
}

std::pair<int, int> generate_bot_move3x3(TicTacToeData data, int mode){ //TODO
    if(mode == 10){
        Random3x3 agent = Random3x3(data);
        return agent.main_fun();
    }
    else if(mode == 11 || mode == 12 || mode == 13){
        MCS3x3 agent = MCS3x3(data, mode);
        return agent.main_fun();
    }
    else{
        std::cout << "game mode is wrong" << std::endl;
        exit(69);
    }

    return {-1, -1};
}