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

int max(int a, int b);

int clamp(int x, int min, int max);

int newGameWindow(struct WindowAttr*, void (*Init)(void), void (*Update)(void), void (*Draw)(void), void (*DeInit)(void));

void DrawTextCentered(const char *text, Rectangle rec, int fontSize, Color color);
