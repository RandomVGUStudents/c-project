#include "game.h"

bool is_winner(int board[3][3], enum Player player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

bool game_over(int board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

enum Player turn(int board[3][3]) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sum += board[i][j];
        }
    }

    if (sum) {
        return O;
    } else {
        return X;
    }
}

int move(int board[3][3], int x, int y) {
    if (board[x][y]) {
        return INVALID;
    }
    enum Player player = turn(board);
    board[x][y] = player;
    if (is_winner(board, player)) {
        return player;
    } else if (game_over(board)) {
        return DRAW;
    } else {
        return ONGOING;
    }
}
