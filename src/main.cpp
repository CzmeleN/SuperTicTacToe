#include<bits/stdc++.h> 
#include "../include/game_data.hpp"
#include "bot_src.hpp"

#define game_no 250

//function to generate seed
long seed()
{
    auto t=std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()).count();
}


// basic engine for bot 
int main() {
    //seting rand
    std::srand(seed());

    // making clean data
    std::vector<std::vector<Sign>> board(9, std::vector<Sign>(9, Sign::Empty));
    Sign turn = Sign::Circle;
    int sector = 4;
    bool super_mode = true;
    bool started = true;        //not important for us
    TicTacToeData clean_data = {board, turn, sector, super_mode, started};

    int score_x = 0, score_o = 0, score_tie = 0;
    const int mode1 = 8, mode2 = 9;

    for(int i = 0; i < game_no; i++){
        Bot bot = Bot(clean_data);

        while(!bot.game_over()){
            auto [x, y] = generate_bot_move(bot.data, ((bot.data.turn == Sign::Cross ? 0 : 1) ? mode1 : mode2));
            bot.put_sign(x, y);
            bot.change_player();
            bot.data.sector = bot.idx_of_next_subgame(x, y);

            //debug
            bot.print();
            std::cout << score_x << ' ' << score_o << ' ' << score_tie << std::endl << std::endl;
        }

        // change score
        if(bot.game_score() == Sign::Circle) score_o++;
        else if(bot.game_score() == Sign::Cross) score_x++;
        else score_tie++;

        std::cout << score_x << ' ' << score_o << ' ' << score_tie << std::endl;
    }
}
