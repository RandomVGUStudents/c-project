#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

enum Player {
    X = 1,
    O = -1
};

enum GameState {
    X_WINS = 1,
    DRAW = 0,
    O_WINS = -1,
    ONGOING = -2,
    INVALID = -3
};

bool is_winner(int board[3][3], enum Player player);

bool game_over(int board[3][3]);

enum Player turn(int board[3][3]);

int move(int board[3][3], int x, int y);

#endif // !GAME_H
