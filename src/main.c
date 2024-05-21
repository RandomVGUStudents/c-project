#include "tictactoe-raylib/tictactoe.h"

int main(int argv, char** args)
{
    struct WindowAttr window = {
        .title = "Tic Tac Toe",
        .width = 800,
        .height = 800,
        .fps = 60,
        .bg = RAYWHITE,
        .fg = BLACK
    };

    return tictactoe(&window, 3, 3, 3);
}
