#ifndef BOT_H
#define BOT_H

#include "game.h"

int minimax(int board[3][3], enum Player player);

int make_move(int board[3][3]);

#endif // !BOT_H
