#include "myUtils.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#define ExePath(name) (TextFormat(".\\%s.exe", name)
#endif

#ifdef linux
#define ExePath(name) (TextFormat("./%s", name))
#endif

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
const Rectangle SIZE_TEXTBOX2 = {550, 250, 200, 30};
const Rectangle MINE_TEXTBOX = {550, 300, 200, 40};
const Rectangle MINE_TEXTBOX2 = {530, 350, 200, 80};
const Rectangle INC_BTN = {700, 350, 30, 30};
const Rectangle DEC_BTN = {700, 390, 30, 30};

extern const Rectangle SLIDER;
extern const Rectangle BACK_BTN;
extern const Rectangle START_BTN;
extern const Rectangle ICON1;
extern const Rectangle ICON2;
