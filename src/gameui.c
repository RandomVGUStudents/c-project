#include "headers/gameui.h"

Texture2D TicTacToe;
Texture2D Minesweeper;

bool popUp = false;
bool unlocked = false;
bool inBounds = false;
GameType selectedGame = GAME_NONE;
int setX = SLIDER.x, setY = SLIDER.y;
int mineRatio = 0;
int winCondition = 3;

void TextureInit() {
    TicTacToe = LoadTexture("assets/images/tictactoe.png");
    if (TicTacToe.id == 0) {
        fprintf(stderr, "Failed to load TicTacToe texture\n");
        exit(EXIT_FAILURE);
    }

    Minesweeper = LoadTexture("assets/images/minesweeper.png");
    if (Minesweeper.id == 0) {
        fprintf(stderr, "Failed to load Minesweeper texture\n");
        exit(EXIT_FAILURE);
    }
}

void DrawSettingsPopup(Vector2 mouse, int maxSize, int minSize) {
    int offsetX = setX - SLIDER.x;
    int offsetY = setY - SLIDER.y;
    int xValue = minSize + (offsetX * (maxSize - minSize)) / (SLIDER.width - SLIDER_HANDLE_SIZE);
    int yValue = minSize + (offsetY * (maxSize - minSize)) / (SLIDER.height - SLIDER_HANDLE_SIZE);

    Rectangle sliderX = {SLIDER.x, SLIDER.y, SLIDER.width, SLIDER_HANDLE_SIZE};
    Rectangle allowedArea = {SLIDER.x - 10, SLIDER.y - 10, SLIDER.width + 20, SLIDER_HANDLE_SIZE + 20};

    DrawRectangleLinesEx(unlocked ? SLIDER : sliderX, 5.0, BLACK);
    DrawRectangleLinesEx(BACK_BTN, 5.0, BLACK);
    DrawRectangleRec(START_BTN, BLACK);
    DrawRectangleRec(INC_BTN, BLACK);
    DrawRectangleLinesEx(DEC_BTN, 5.0, BLACK);
    DrawTextCentered("Game Settings", TEXTBOX, 80, BLACK);
    DrawTextCentered("Board size", SIZE_TEXTBOX, 40, BLACK);
    DrawTextCentered("Back", BACK_BTN, 20, BLACK);
    DrawTextCentered("Start Game", START_BTN, 20, RAYWHITE);
    DrawTextCentered("+", INC_BTN, 20, RAYWHITE);
    DrawTextCentered("-", DEC_BTN, 20, BLACK);
    DrawRectangle(setX, unlocked ? setY : SLIDER.y, SLIDER_HANDLE_SIZE, SLIDER_HANDLE_SIZE, BLACK);

    if (!unlocked) {
        if (CheckCollisionPointRec(mouse, allowedArea))
            inBounds = true;

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && inBounds) {
            setX = clamp(mouse.x, SLIDER.x, SLIDER.x + SLIDER.width - SLIDER_HANDLE_SIZE);
            setY = clamp(mouse.y, SLIDER.y, SLIDER.y + SLIDER.height - SLIDER_HANDLE_SIZE);
        }

        if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            inBounds = false;

        DrawTextCentered(TextFormat("X = %d", xValue), SIZE_TEXTBOX2, 40, BLACK);
        if (yValue == maxSize)
            unlocked = true;
        yValue = xValue;
    } else {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            setX = clamp(mouse.x, SLIDER.x, SLIDER.x + SLIDER.width - SLIDER_HANDLE_SIZE);
            setY = clamp(mouse.y, SLIDER.y, SLIDER.y + SLIDER.height - SLIDER_HANDLE_SIZE);
        }
        DrawTextCentered(TextFormat("X = %d + %di", xValue, yValue), SIZE_TEXTBOX2, 40, BLACK);
    }

    if (selectedGame == GAME_MINESWEEPER) {
        if (CheckCollisionPointRec(mouse, INC_BTN)) {
            DrawRectangleRec(INC_BTN, Fade(RAYWHITE, 0.5));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mineRatio = clamp(mineRatio + 5, 0, 100);
            }
        }

        if (CheckCollisionPointRec(mouse, DEC_BTN)) {
            DrawRectangleRec(DEC_BTN, Fade(BLACK, 0.5));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                mineRatio = clamp(mineRatio - 5, 0, 100);
            }
        }

        DrawTextCentered("Mine ratio", MINE_TEXTBOX, 40, BLACK);
        DrawTextCentered(TextFormat("%d", mineRatio), MINE_TEXTBOX2, 80, BLACK);
    } else {
        if (CheckCollisionPointRec(mouse, INC_BTN)) {
            DrawRectangleRec(INC_BTN, Fade(RAYWHITE, 0.5));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                winCondition = clamp(winCondition + 1, 3, 6);
            }
        }

        if (CheckCollisionPointRec(mouse, DEC_BTN)) {
            DrawRectangleRec(DEC_BTN, Fade(BLACK, 0.5));
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                winCondition = clamp(winCondition - 1, 3, 6);
            }
        }

        DrawTextCentered("To win", MINE_TEXTBOX, 40, BLACK);
        DrawTextCentered(TextFormat("%d", winCondition), MINE_TEXTBOX2, 80, BLACK);
    }

    if (CheckCollisionPointRec(mouse, BACK_BTN)) {
        DrawRectangleRec(BACK_BTN, Fade(BLACK, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedGame = GAME_NONE;
            popUp = false;
        }
    }

    if (CheckCollisionPointRec(mouse, START_BTN)) {
        DrawRectangleRec(START_BTN, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            switch (selectedGame) {
                case GAME_MINESWEEPER:
                    system(TextFormat("%s %d %d %d", EXEPATH("minesweeper"),
                                xValue, yValue, (int) (mineRatio * xValue * yValue * 0.01)));
                    break;
                case GAME_TICTACTOE:
                    system(TextFormat("%s %d %d %d", EXEPATH("tictactoe"),
                                xValue, yValue, winCondition));
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
    Rectangle textBox = {0, 160, 800, 80};

    DrawTexture(Minesweeper, ICON1.x, ICON1.y, WHITE);
    DrawTexture(TicTacToe, ICON2.x, ICON2.y, WHITE);
    DrawTextCentered("Choose a game", textBox, 80, BLACK);

    if (CheckCollisionPointRec(mouse, ICON1)) {
        DrawRectangleRec(ICON1, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedGame = GAME_MINESWEEPER;
            popUp = true;
        }
    } else if (CheckCollisionPointRec(mouse, ICON2)) {
        DrawRectangleRec(ICON2, Fade(RAYWHITE, 0.5));
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedGame = GAME_TICTACTOE;
            popUp = true;
        }
    }
}

void UI() {
    Vector2 mouse = GetMousePosition();

    if (popUp)
        if (selectedGame == GAME_MINESWEEPER)
            DrawSettingsPopup(mouse, 30, 10);
        else
            DrawSettingsPopup(mouse, 20, 3);
    else
        DrawGameSelection(mouse);
}

void DeInit() {
    UnloadTexture(TicTacToe);
    UnloadTexture(Minesweeper);
}

int main() {
    struct WindowAttr window = {
        .title = "Game Selector",
        .width = 800,
        .height = 750,
        .fps = 60,
        .bg = RAYWHITE,
        .fg = BLACK
    };

    newGameWindow(&window, TextureInit, UI, NULL, DeInit);

    return 0;
}
