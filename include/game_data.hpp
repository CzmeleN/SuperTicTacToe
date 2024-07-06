#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include <vector>

enum class Sign {
    Cross,
    Circle,
    Empty
};

// Game state struct
struct TicTacToeData {
    std::vector<std::vector<Sign>> board;
    Sign turn;
    int sector; // In which sector the move needs to be done, 9 - all
    bool super_mode; // Whether the ame is 3x3 or 9x9 (with all the fancy mechanics)
    bool started;
};

// Game data managing class
class GameData {
public:
    GameData() {
        ticTacToeData.board = {
            {Sign::Empty, Sign::Empty, Sign::Empty},
            {Sign::Empty, Sign::Empty, Sign::Empty},
            {Sign::Empty, Sign::Empty, Sign::Empty}
        };
        ticTacToeData.turn = Sign::Cross;
        ticTacToeData.sector = 9;
        ticTacToeData.super_mode = false;
        ticTacToeData.started = false;
    }

    TicTacToeData& getTicTacToeData() {
        return ticTacToeData;
    }

    const TicTacToeData& getTicTacToeData() const {
        return ticTacToeData;
    }

    void resetGame() {
        // TODO
    }

private:
    TicTacToeData ticTacToeData;
};

#endif
