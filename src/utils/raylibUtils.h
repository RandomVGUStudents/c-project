#pragma once
#include <raylib.h>

struct WindowAttr {
    char *title;
    int width;
    int height;
    int fps;
    Color bg;
    Color fg;
};

int newGameWindow(struct WindowAttr*, void (*Init)(void), void (*Update)(void), void (*Draw)(void), void (*DeInit)(void));

void DrawTextCentered(const char *text, int x, int y, int fontSize, Color color);
