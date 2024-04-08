#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include "game.h"
#include "../utils/SDLUtils.h"

#define LINE_WIDTH 10
#define PAD 50
#define PI 3.14159265358979323846264338327950288

struct Board {
    int board[3][3];
};

extern struct Board board;

void process_input(void);
void init_board(struct Board *board);
void draw_board(void);
void draw_x(int x, int y);
void draw_o(int x, int y);
void draw_board_state(void);
void update_board(int *mPos);
void draw_result();

#endif // ! BOARD
