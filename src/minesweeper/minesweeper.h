#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include "../utils/myUtils.h"

#define CELL_SIZE 30
#define GOJO_SIZE 100
#define BORDER_SIZE 5

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

void minesweeper(int row, int column, int mine_count);
