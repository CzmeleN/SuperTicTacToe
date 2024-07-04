#include "MCS3x3.hpp"

MCS3x3::MCS3x3(TicTacToeData data, int mode) : Bot3x3(data){
    if(mode == easy_mcs_3x3) max_sim = easy_mcs_3x3_max_sim;
    else if(mode == medium_mcs_3x3) max_sim = medium_mcs_3x3_max_sim;
    else max_sim = hard_mcs_3x3_max_sim;
}

MCS3x3::~MCS3x3(){}

std::pair<int, int> MCS3x3::main_fun(){
    std::vector<std::pair<int, int>> possible_moves;
    possible_moves = MCS3x3::generate_possible_moves();
    int n = max_sim / possible_moves.size();

    std::pair<int, int> best_move;
    int best_score = -1;

    for(auto [x, y]: possible_moves){
        data.board[x][y] = data.turn;
        MCS3x3::change_player();

        int score = MCS3x3::make_symulations(n);
        data.board[x][y] = Sign::Empty;
        MCS3x3::change_player();

        if(score > best_score){
            best_score = score;
            best_move = {x, y};
        }
    }

    return best_move;
}

int MCS3x3::make_symulations(int n){
    int win_cnt = 0;
    TicTacToeData data_copy = data;

    for(int i = 0; i < n; i++){
        while(!MCS3x3::game_over()){
            std::vector<std::pair<int, int>> possible_moves;
            possible_moves = MCS3x3::generate_possible_moves();

            int idx = rand() % possible_moves.size();
            auto [x, y] = possible_moves[idx];

            data.board[x][y] = data.turn;
            MCS3x3::change_player();
        }

        //sb won
        if(MCS3x3::game_score() == max_player) win_cnt += 2;
        else if(MCS3x3::game_score() == Sign::Empty) win_cnt += 1;

        //restore data
        data = data_copy;
    }

    return win_cnt;
}

