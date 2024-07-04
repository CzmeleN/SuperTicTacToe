#include "Bot3x3.hpp"

Bot3x3::Bot3x3(TicTacToeData data) : data(data){
    max_player = data.turn;
    min_player = (data.turn == Sign::Cross ? Sign::Circle : Sign::Cross);
}

Bot3x3::~Bot3x3(){};

void Bot3x3::change_player(){
    if(data.turn == Sign::Cross) data.turn = Sign::Circle;
    else data.turn = Sign::Cross;
}

void Bot3x3::print(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
            if(data.board[i][j] == Sign::Circle) std::cout << 'O';
            else if(data.board[i][j] == Sign::Cross) std::cout << 'X';
            else std::cout << '.';
        std::cout << std::endl;
    }
}

Sign Bot3x3::game_score(){
    // verticacl check
    for(int i = 0, j = 0; i < 3; i++)
        if(data.board[i][j] == data.board[i][j + 1] && data.board[i][j + 1] == data.board[i][j + 2] && data.board[i][j + 2] != Sign::Empty)
            return data.board[i][j];

    // horizontal check
    for(int j = 0, i = 0; j < 3; j++)
        if(data.board[i][j] == data.board[i + 1][j] && data.board[i + 1][j] == data.board[i + 2][j] && data.board[i + 2][j] != Sign::Empty)
            return data.board[i][j];
    
    // cross check
    if(data.board[0][0] == data.board[1][1] && data.board[1][1] == data.board[2][2] && data.board[2][2] != Sign::Empty)
        return data.board[0][0];

    if(data.board[0][2] == data.board[1][1] && data.board[1][1] == data.board[2][0] && data.board[2][0] != Sign::Empty)
        return data.board[0][2];

    return Sign::Empty; 
}

std::vector<std::pair<int, int>> Bot3x3::generate_possible_moves(){
    std::vector<std::pair<int, int>> ans;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(data.board[i][j] == Sign::Empty)
                ans.push_back({i, j});
    return ans;
}

bool Bot3x3::game_over(){
    if(Bot3x3::game_score() != Sign::Empty) return true;
    if(Bot3x3::generate_possible_moves().size()) return false;
    return true;
}