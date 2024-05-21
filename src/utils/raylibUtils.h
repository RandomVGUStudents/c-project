#include <raylib.h>

struct WindowAttr {
    char *title;
    int width;
    int height;
    int fps;
    Color bg;
    Color fg;
};

int newGameWindow(struct WindowAttr*, void (*Update)(void), void (*Draw)(void));

void DrawTextCentered(const char *text, int x, int y, int fontSize, Color color);
