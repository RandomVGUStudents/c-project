#include "utils/raylibUtils.h"
#include <stdlib.h>
#include <stdio.h>

void UI() {
    DrawRectangle(50, 350, 300, 300, RED);
    DrawRectangle(450, 350, 300, 300, BLUE);
    DrawTextCentered("Choose a game", 800, 400, 80, BLACK);

    int hoverX = GetMouseX();
    int hoverY = GetMouseY();

    if (hoverX >= 50 && hoverX <= 350 && hoverY >= 350 && hoverY <= 650) {
        DrawRectangle(50, 350, 300, 300, Fade(WHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            system("./minesweeper");
        }
    } else if (hoverX >= 450 && hoverX <= 750 && hoverY >= 350 && hoverY <= 650) {
        DrawRectangle(450, 350, 300, 300, Fade(WHITE, 0.5));
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

    newGameWindow(&window, UI, NULL);

    return 0;
}

