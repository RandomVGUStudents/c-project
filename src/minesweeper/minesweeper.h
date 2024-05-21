#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include "../utils/raylibUtils.h"

#define CELL_SIZE 30

typedef enum {
    menu,
    gameplay,
    nah_id_win,
    stand_proud_youre_strong
} game_state;

typedef struct tile {
    Vector2 location;
    bool is_opened;
    bool is_mine;
    bool is_flagged;
    bool is_hovered;
    int nearby_mine;
    Rectangle tile_rect;
} tile;

void minesweeper(struct WindowAttr *window, int row, int column, int mine_count);

#endif