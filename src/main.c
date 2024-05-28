#include "main.h"
#include <raylib.h>

Texture2D TicTacToe;
Texture2D Minesweeper;

bool popUp = false;
bool unlocked = false;
bool inBounds = false;
GameType selectedGame = GAME_NONE;
int max = 30, min = 5;
int setX = SLIDER_X, setY = SLIDER_Y;

void TextureInit() {
    TicTacToe = LoadTexture("assets/tictactoe.png");
    if (TicTacToe.id == 0) {
        fprintf(stderr, "Failed to load TicTacToe texture\n");
        exit(EXIT_FAILURE);
    }

    Minesweeper = LoadTexture("assets/minesweeper.png");
    if (Minesweeper.id == 0) {
        fprintf(stderr, "Failed to load Minesweeper texture\n");
        exit(EXIT_FAILURE);
    }
}

void DrawSettingsPopup(Vector2 mouse) {
    int offsetX = setX - SLIDER_X;
    int offsetY = setY - SLIDER_Y;
    int xValue = min + (offsetX * (max - min)) / (SLIDER_WIDTH - SLIDER_HANDLE_SIZE);
    int yValue = min + (offsetY * (max - min)) / (SLIDER_HEIGHT - SLIDER_HANDLE_SIZE);

    Rectangle sliderX = {SLIDER_X, SLIDER_Y, SLIDER_HANDLE_SIZE * offsetX * 0.1, SLIDER_HANDLE_SIZE};
    Rectangle allowedArea = {SLIDER_X - 10, SLIDER_Y - 10, SLIDER_WIDTH + 20, SLIDER_HANDLE_SIZE + 20};
    Rectangle sliderXY = {SLIDER_X, SLIDER_Y, SLIDER_WIDTH, SLIDER_HEIGHT};
    Rectangle startBtn = {START_BTN_X, START_BTN_Y, START_BTN_WIDTH, START_BTN_HEIGHT};

    DrawRectangleLinesEx(unlocked ? sliderXY : sliderX, 5.0, BLACK);
    DrawRectangleRec(startBtn, BLACK);
    DrawTextCentered("Game Settings", 800, 200, 80, BLACK);
    DrawTextCentered("Board size", 1300, 400, 40, BLACK);
    DrawTextCentered("Start Game", 800, 1350, 20, RAYWHITE);

    if (!unlocked) {
        if (CheckCollisionPointRec(mouse, allowedArea)) {
            inBounds = true;
        }

        printf("%b\n", inBounds);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds) {
            setX = CLAMP(mouse.x, SLIDER_X, SLIDER_X + SLIDER_WIDTH - SLIDER_HANDLE_SIZE);
            setY = CLAMP(mouse.y, SLIDER_Y, SLIDER_Y + SLIDER_HEIGHT - SLIDER_HANDLE_SIZE);
        }

        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            inBounds = false;
        }

        DrawTextCentered(TextFormat("X = %d", xValue), 1300, 500, 20, BLACK);
        if (yValue == max) {
            unlocked = true;
        }
    } else {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            setX = CLAMP(mouse.x, SLIDER_X, SLIDER_X + SLIDER_WIDTH - SLIDER_HANDLE_SIZE);
            setY = CLAMP(mouse.y, SLIDER_Y, SLIDER_Y + SLIDER_HEIGHT - SLIDER_HANDLE_SIZE);
        }
        DrawTextCentered(TextFormat("X = %d + %di", xValue, yValue), 1300, 500, 20, BLACK);
    }

    DrawRectangle(setX, unlocked ? setY : SLIDER_Y, SLIDER_HANDLE_SIZE, SLIDER_HANDLE_SIZE, BLACK);

    if (CheckCollisionPointRec(mouse, startBtn)) {
        DrawRectangle(START_BTN_X, START_BTN_Y, START_BTN_WIDTH, START_BTN_HEIGHT, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!unlocked) {
                yValue = xValue;
            }
            switch (selectedGame) {
                case GAME_MINESWEEPER:
                    system(TextFormat("./minesweeper %d %d %d", xValue, yValue, 10));
                    break;
                case GAME_TICTACTOE:
                    system(TextFormat("./tictactoe %d %d %d", xValue, yValue, (int)CLAMP(MAX(xValue, yValue) / 1.5, 3, 5)));
                    break;
                default:
                    break;
            }

            popUp = false;
            unlocked = false;
        }
    }
}

void DrawGameSelection(Vector2 mouse) {
    Rectangle icon1 = {ICON1_X, ICON1_Y, ICON1_WIDTH, ICON1_HEIGHT};
    Rectangle icon2 = {ICON2_X, ICON2_Y, ICON2_WIDTH, ICON2_HEIGHT};

    DrawTexture(Minesweeper, ICON1_X, ICON1_Y, WHITE);
    DrawTexture(TicTacToe, ICON2_X, ICON2_Y, WHITE);
    DrawTextCentered("Choose a game", 800, 400, 80, BLACK);

    if (CheckCollisionPointRec(mouse, icon1)) {
        DrawRectangleRec(icon1, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedGame = GAME_MINESWEEPER;
            popUp = true;
        }
    } else if (CheckCollisionPointRec(mouse, icon2)) {
        DrawRectangleRec(icon2, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedGame = GAME_TICTACTOE;
            popUp = true;
        }
    }
}

void UI() {
    Vector2 mouse = GetMousePosition();

    if (popUp) {
        DrawSettingsPopup(mouse);
    } else {
        DrawGameSelection(mouse);
    }
}

void DeInit() {
    UnloadTexture(TicTacToe);
    UnloadTexture(Minesweeper);
}

int main() {
    struct WindowAttr window = {
        .title = "Game Selector",
        .width = 800,
        .height = 800,
        .fps = 60,
        .bg = RAYWHITE,
        .fg = BLACK
    };

    newGameWindow(&window, TextureInit, UI, NULL, DeInit);

    return 0;
}

