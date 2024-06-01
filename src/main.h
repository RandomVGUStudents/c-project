#include "utils/myUtils.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define SLIDER_HANDLE_SIZE 20

typedef enum {
    GAME_NONE,
    GAME_MINESWEEPER,
    GAME_TICTACTOE
} GameType;

const Rectangle SLIDER = {100, 200, 400, 400};
const Rectangle BACK_BTN = {175, 650, 200, 50};
const Rectangle START_BTN = {425, 650, 200, 50};
const Rectangle ICON1 = {50, 350, 300, 300};
const Rectangle ICON2 = {450, 350, 300, 300};
const Rectangle TEXTBOX = {0, 60, 800, 80};
const Rectangle SIZE_TEXTBOX = {550, 200, 200, 40};
const Rectangle SIZE_TEXTBOX2 = {550, 260, 200, 20};
const Rectangle MINE_TEXTBOX = {550, 300, 200, 40};
const Rectangle MINE_TEXTBOX2 = {550, 350, 200, 20};

extern const Rectangle SLIDER;
extern const Rectangle BACK_BTN;
extern const Rectangle START_BTN;
extern const Rectangle ICON1;
extern const Rectangle ICON2;
