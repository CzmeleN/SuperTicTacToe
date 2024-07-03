#include "MCS.hpp"

MCS::MCS(TicTacToeData data, int mode) : Bot(data){
    if(mode == easy) max_sim = easy_max_sim;
    else if(mode == medium) max_sim = medium_max_sim;
    else max_sim = hard_max_sim;
}

MCS::~MCS(){}

std::pair<int, int> MCS::main_fun(){
    std::vector<std::pair<int, int>> possible_moves = generate_possible_moves();
    int n = max_sim / possible_moves.size();

    std::pair<int, int> best_move;
    int best_score = -1;

    for(auto [x, y]: possible_moves){
        MCS::put_sign(x, y);
        MCS::change_player();

        int sector_copy = data.sector;
        data.sector = MCS::idx_of_next_subgame(x, y);

        int score = MCS::make_symulations(n);
        MCS::unput_sign(x, y);
        MCS::change_player();
        data.sector = sector_copy;

        if(score > best_score){
            best_score = score;
            best_move = {x, y};
        }
    }

    return best_move;
}

int MCS::make_symulations(int n){
    int win_cnt = 0;
    TicTacToeData data_copy = data;
    std::vector<Sign> subgame_score_copy = subgame_score;

    for(int i = 0; i < n; i++){
        while(!MCS::game_over()){
            std::vector<std::pair<int, int>> possible_moves;
            possible_moves = generate_possible_moves();

            int idx = rand() % possible_moves.size();
            auto [x, y] = possible_moves[idx];

            MCS::put_sign(x, y);
            MCS::change_player();
            data.sector = MCS::idx_of_next_subgame(x, y);
        }

        //sb won
        if(MCS::game_score() == max_player) win_cnt += 2;
        else if(MCS::game_score() == Sign::Empty) win_cnt += 1; 

        //restore data 
        data = data_copy;
        subgame_score = subgame_score_copy;
    }

    return win_cnt;
}

