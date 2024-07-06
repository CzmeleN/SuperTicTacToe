#include "MinMax.hpp"

MinMax::MinMax(TicTacToeData data, int mode) : Bot(data){
    if(mode == easy_MinMax){
        max_sim = easy_max_sim_MinMax;
        max_deep = easy_max_deep_MinMax;
    }
    else if(mode == medium_MinMax){
        max_sim = medium_max_sim_MinMax;
        max_deep = medium_max_deep_MinMax;
    }
    else{
        max_sim = hard_max_sim_MinMax;
        max_deep = hard_max_deep_MinMax;
    }
}

MinMax::~MinMax(){}

std::pair<int, int> MinMax::main_fun(){
    std::vector<std::pair<int, int>> possible_moves;
    possible_moves = generate_possible_moves();

    int best_score = -1;
    std::pair<int, int> best_move;
    int alfa = -inf, beta = inf;
    int sector_copy = data.sector;

    for(auto [x, y]: possible_moves){
        MinMax::put_sign(x, y);
        MinMax::change_player();
        data.sector = MinMax::idx_of_next_subgame(x, y);

        int score = MinMax::alfa_beta(0, alfa, beta);
        if(score > best_score){
            best_score = score;
            best_move = {x, y};
        }

        unput_sign(x, y);
        change_player();
        data.sector = sector_copy;
    }

    return best_move;
}

int MinMax::heura(){
    int win_cnt = 0;
    TicTacToeData data_copy = data;
    std::vector<Sign> subgame_score_copy = subgame_score;

    for(int i = 0; i < max_sim; i++){
        while(!MinMax::game_over()){
            std::vector<std::pair<int, int>> possible_moves;
            possible_moves = generate_possible_moves();

            int idx = rand() % possible_moves.size();
            auto [x, y] = possible_moves[idx];

            MinMax::put_sign(x, y);
            MinMax::change_player();
            data.sector = MinMax::idx_of_next_subgame(x, y);
        }

        if(MinMax::game_score() == max_player) win_cnt += 2;
        else if(MinMax::game_score() == Sign::Empty) win_cnt += 1;

        data = data_copy;
        subgame_score = subgame_score_copy;
    }

    return win_cnt;
}


int MinMax::alfa_beta(int deep, int alfa, int beta){
    if(deep == max_deep || MinMax::game_over()){
        return MinMax::heura();
    }

    if(data.turn == max_player){ //max player
        int best_score = -inf;
        std::vector<std::pair<int, int>> possible_moves;
        possible_moves = generate_possible_moves();
        int sector_copy = data.sector;

        for(auto [x, y]: possible_moves){
            MinMax::put_sign(x, y);
            MinMax::change_player();
            data.sector = MinMax::idx_of_next_subgame(x, y);

            int score = alfa_beta(deep + 1, alfa, beta);
            best_score = std::max(score, best_score);

            MinMax::unput_sign(x, y);
            MinMax::change_player();
            data.sector = sector_copy;

            if(best_score > beta)
                break;

            alfa = std::max(alfa, best_score);
        }

        return best_score;
    }
    else{ //min player
        int best_score = inf;
        std::vector<std::pair<int, int>> possible_moves;
        possible_moves = generate_possible_moves();
        int sector_copy = data.sector;

        for(auto [x, y]: possible_moves){
            MinMax::put_sign(x, y);
            MinMax::change_player();
            data.sector = MinMax::idx_of_next_subgame(x, y);

            int score = alfa_beta(deep + 1, alfa, beta);
            best_score = std::min(score, best_score);

            MinMax::unput_sign(x, y);
            MinMax::change_player();
            data.sector = sector_copy;

            if(best_score < alfa)
                break;

            beta = std::min(beta, best_score);
        }

        return best_score;
    }    
}