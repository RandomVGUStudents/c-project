#include "utils/raylibUtils.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) ((a > b) ? a : b)
#define CLAMP(x, min, max) ((x < min) ? min : ((x > max) ? max : x))

// Constants
#define SLIDER_X 100
#define SLIDER_Y 200
#define SLIDER_WIDTH 400
#define SLIDER_HEIGHT 400
#define START_BTN_X 300
#define START_BTN_Y 650
#define START_BTN_WIDTH 200
#define START_BTN_HEIGHT 50
#define ICON1_X 50
#define ICON1_Y 350
#define ICON1_WIDTH 300
#define ICON1_HEIGHT 300
#define ICON2_X 450
#define ICON2_Y 350
#define ICON2_WIDTH 300
#define ICON2_HEIGHT 300
#define SLIDER_HANDLE_SIZE 10

typedef enum {
    GAME_NONE,
    GAME_MINESWEEPER,
    GAME_TICTACTOE
} GameType;
