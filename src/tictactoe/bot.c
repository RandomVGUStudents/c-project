#include "bot.h"

int minimax(int board[3][3], enum Player player) {
    if (is_winner(board, player)) {
        return player;
    }

    if (game_over(board)) {
        return 0;
    }

    if (player == X) {
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = X;
                    best = best > minimax(board, O) ? best : minimax(board, O);
                    board[i][j] = 0;
                }
            }
        }

        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = O;
                    best = best < minimax(board, X) ? best : minimax(board, X);
                    board[i][j] = 0;
                }
            }
        }

        return best;
    }
}

int make_move(int board[3][3]) {
    int best_move[2] = {0, 0};
    enum Player player = turn(board);

    if (player == X) {
        int best_val = -1000;
        int val;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = X;
                    val = minimax(board, O);
                    board[i][j] = 0;
                    if (val > best_val) {
                        best_val = val;
                        best_move[0] = i;
                        best_move[1] = j;
                    }
                }
            }
        }
    } else {
        int best_val = 1000;
        int val;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = O;
                    val = minimax(board, X);
                    board[i][j] = 0;
                    if (val < best_val) {
                        best_val = val;
                        best_move[0] = i;
                        best_move[1] = j;
                    }
                }
            }
        }
    }

    return move(board, best_move[0], best_move[1]);
}
