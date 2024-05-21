#include "raylibUtils.h"

int newGameWindow(struct WindowAttr *window, void (*Update)(void), void (*Draw)(void)) {
    InitWindow(window->width, window->height, window->title);
    SetTargetFPS(window->fps);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(window->bg);
        (*Update)();
        (*Draw)();
        EndDrawing();
    }
    return 0;
}

void DrawTextCentered(const char *text, int x, int y, int fontSize, Color color) {
    Vector2 textPos = { x / 2.0f - MeasureText(text, fontSize) / 2.0f, y / 2.0f - 10 };
    DrawText(text, textPos.x, textPos.y, fontSize, color);
}
