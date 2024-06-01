#include "myUtils.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int clamp(int x, int min, int max) {
    return x < min ? min : (x > max ? max : x);
}

int newGameWindow(struct WindowAttr *window, void (*Init)(void), void (*Update)(void), void (*Draw)(void), void (*DeInit)(void)) {
    InitWindow(window->width, window->height, window->title);
    if (Init) {
        Init();
    }
    SetTargetFPS(window->fps);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(window->bg);
        if (Update) {
            (*Update)();
        }
        if (Draw) {
            (*Draw)();
        }
        EndDrawing();
    }
    if (DeInit) {
        DeInit();
    }
    return 0;
}

void DrawTextCentered(const char *text, Rectangle rec, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    while (textWidth + 5 > rec.width || fontSize > rec.height) {
        fontSize--;
        textWidth = MeasureText(text, fontSize);
    }
    Vector2 textPos = { rec.x + rec.width / 2.0 - textWidth / 2.0, rec.y + (rec.height - fontSize) / 2.0 };
    DrawText(text, textPos.x, textPos.y, fontSize, color);
}
