#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <raylib.h>
#include "../utils/raylibUtils.h"

#define TOTAL_THICKNESS 0.05
#define TOTAL_PADDING 0.15
#define X_COLOR MAROON
#define O_COLOR SKYBLUE
#define TEXT_SIZE 100

typedef enum {
    X = 1,
    O = -1,
    EMPTY = 0
} Cell;

typedef enum {
    X_WINS = 1,
    DRAW = 0,
    O_WINS = -1,
    ONGOING = -2,
} GameState;

int tictactoe(struct WindowAttr *window, int x, int y, int size);
