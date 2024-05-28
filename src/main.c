#include "utils/raylibUtils.h"
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>

Texture2D TicTacToe;
Texture2D Minesweeper;

void TextureInit() {
    TicTacToe = LoadTexture("assets/tictactoe.png");
    Minesweeper = LoadTexture("assets/minesweeper.png");
}

void UI() {
    DrawTexture(Minesweeper, 50, 350, WHITE);
    DrawTexture(TicTacToe, 450, 350, WHITE);
    DrawTextCentered("Choose a game", 800, 400, 80, BLACK);

    int hoverX = GetMouseX();
    int hoverY = GetMouseY();

    if (hoverX >= 50 && hoverX <= 350 && hoverY >= 350 && hoverY <= 650) {
        DrawRectangle(50, 350, 300, 300, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            system("./minesweeper");
        }
    } else if (hoverX >= 450 && hoverX <= 750 && hoverY >= 350 && hoverY <= 650) {
        DrawRectangle(450, 350, 300, 300, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            system("./tictactoe");
        }
    }
}

int main(int argc, char** argv) {
    struct WindowAttr window = {
        .title = "Game Selector",
        .width = 800,
        .height = 800,
        .fps = 60,
        .bg = RAYWHITE,
        .fg = BLACK
    };

    newGameWindow(&window, TextureInit, UI, NULL);

    return 0;
}

