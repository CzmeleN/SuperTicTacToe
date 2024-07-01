#include "Bot.hpp"

const int next_subgame[3][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8}
};

Bot::Bot(TicTacToeData data) : data(data), subgame_score(9, Sign::Empty){
    set_subgame_info();
    max_player = data.turn;
    min_player = (data.turn == Sign::Cross ? Sign::Circle : Sign::Cross);
}

Bot::~Bot(){};

void Bot::change_player(){
    if(data.turn == Sign::Cross) data.turn = Sign::Circle;
    else data.turn = Sign::Cross;
}

void Bot::print(){
    int n = (data.super_mode == true ? 9 : 3);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            if(data.board[i][j] == Sign::Circle) std::cout << 'O';
            else if(data.board[i][j] == Sign::Cross) std::cout << 'X';
            else std::cout << '.';
        std::cout << std::endl;
    }
}

int Bot::idx_of_next_subgame(int x, int y){
    int idx = Bot::idx_of_subgame(x, y);
    auto [a, b] = Bot::corner_of_subgame(idx);
    return next_subgame[x - a][y - b];
}

bool Bot::game_over(){
    if(Bot::game_score() != Sign::Empty) return true;

    for(int idx = 0; idx < 9; idx++)
        if(subgame_score[idx] == Sign::Empty && generate_possible_moves_in_sector(idx).size()) return false;
    
    return true;
}

void Bot::put_sign(int x, int y){
    data.board[x][y] = data.turn;
    int idx = Bot::idx_of_subgame(x, y);
    Bot::update_subgame(idx);
}

void Bot::unput_sign(int x, int y){
    data.board[x][y] = Sign::Empty;
    int subgame_idx = Bot::idx_of_subgame(x, y);
    Bot::update_subgame(subgame_idx);
}

void Bot::update_subgame(int idx){
    std::pair<int, int> start = Bot::corner_of_subgame(idx);

    // vertical check
    for(int i = start.first, j = start.second; i < start.first + 3; i++)
        if(data.board[i][j] == data.board[i][j + 1] && data.board[i][j + 1] == data.board[i][j + 2] && data.board[i][j + 2] != Sign::Empty){
            subgame_score[idx] = data.board[i][j];
            return;
        }

    // horizontal chceck
    for(int j = start.second, i = start.first; j < start.second + 3; j++)
        if(data.board[i][j] == data.board[i + 1][j] && data.board[i + 1][j] == data.board[i + 2][j] && data.board[i + 2][j] != Sign::Empty){
            subgame_score[idx] = data.board[i][j];
            return;
        }
    
    // cross check
    if(data.board[start.first][start.second] == data.board[start.first + 1][start.second + 1] && data.board[start.first + 1][start.second + 1] == data.board[start.first + 2][start.second + 2] && data.board[start.first + 2][start.second + 2] != Sign::Empty){
        subgame_score[idx] = data.board[start.first][start.second];
        return;
    }
    if(data.board[start.first][start.second + 2] == data.board[start.first + 1][start.second + 1] && data.board[start.first + 1][start.second + 1] == data.board[start.first + 2][start.second] && data.board[start.first + 2][start.second] != Sign::Empty){
        subgame_score[idx] = data.board[start.first][start.second + 2];
        return;
    }

    //subgame is not over
    subgame_score[idx] = Sign::Empty;
}

void Bot::set_subgame_info(){
    for(int i = 0; i < 9; i++)
        Bot::update_subgame(i);
}


inline std::pair<int, int> Bot::corner_of_subgame(int idx){
    return std::make_pair((idx / 3) * 3, (idx % 3) * 3);
}

inline int Bot::idx_of_subgame(int x, int y){
    return 3 * (x / 3) + y / 3;
}

Sign Bot::game_score(){
    std::vector<std::vector<Sign>> game(3, std::vector<Sign>(3));

    for(int i = 0, itr = 0; i < 3; i++)
        for(int j = 0; j < 3; j++, itr++)
            game[i][j] = subgame_score[itr];

    // vertical check
    for(int i = 0, j = 0; i < 3; i++)
        if(game[i][j] == game[i][j + 1] && game[i][j + 1] == game[i][j + 2] && game[i][j + 2] != Sign::Empty)
            return game[i][j];
    
    // horizontal chceck
    for(int i = 0, j = 0; j < 3; j++)
        if(game[i][j] == game[i + 1][j] && game[i + 1][j] == game[i + 2][j] && game[i + 2][j] != Sign::Empty)
            return game[i][j];

    //cross check
    if(game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[2][2] != Sign::Empty)  
        return game[0][0];
    if(game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[2][0] != Sign::Empty)
        return game[2][0];

    // game is not over
    return Sign::Empty;
}



std::vector<std::pair<int, int>> Bot::generate_possible_moves(){
    std::vector<std::pair<int, int>> v;

    if(data.sector != 9 && subgame_score[data.sector] == Sign::Empty){
        v = generate_possible_moves_in_sector(data.sector);
    }

    if(data.sector == 9 || v.size() == 0){
        for(int i = 0; i < 9; i++){
            if(subgame_score[i] != Sign::Empty) continue;

            //generating possible moves in sector
            std::vector<std::pair<int, int>> vs;
            vs = generate_possible_moves_in_sector(i);

            //marging two vectors
            v.insert(v.end(), vs.begin(), vs.end());
        }
    }

    return v;
}

std::vector<std::pair<int, int>> Bot::generate_possible_moves_in_sector(int idx){
    std::vector<std::pair<int, int>> ans;
    std::pair<int, int> start = Bot::corner_of_subgame(idx);
    for(int i = start.first; i < start.first + 3; i++)
        for(int j = start.second; j < start.second + 3; j++)
            if(data.board[i][j] == Sign::Empty)
                ans.push_back({i, j});

    return ans;
}