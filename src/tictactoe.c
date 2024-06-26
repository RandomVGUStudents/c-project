#include "headers/tictactoe.h"

struct WindowAttr window = {
    .title = "Tic Tac Toe",
    .fps = 60,
    .bg = RAYWHITE,
    .fg = BLACK
};
char *board;
int sizeX;
int sizeY;
int thickness;
int inARow;
int cellSize;
Cell currentTurn;
int gameOver;

void initGame() {
    board = malloc(sizeX * sizeY * sizeof(char));
    if (!board) {
        return;
    }
    for (int i = 0; i < sizeX * sizeY; i++) {
        board[i] = EMPTY;
    }

    gameOver = 0;
    currentTurn = X;

    thickness = cellSize * TOTAL_THICKNESS;
}

/**
 * Set the board with the current player.
 *
 * The function sets the board with the current player and changes the player.
 *
 * @param x Coordinate x
 * @param y Coordinate y
 *
 */

void setBoard(int x, int y) {
    board[y * sizeX + x] = currentTurn;
    currentTurn = -currentTurn;
}

/**
 * Draw the player in the cell. It will draw X or O.
 *
 * @param player The player to draw
 * @param x Coordinate x
 * @param y Coordinate y
 * @param hover If the cell is hovered
 *
 */

void draw(Cell player, int x, int y, int hover) {
    if (player == X) {
        int padding = cellSize * TOTAL_PADDING;

        Vector2 start1 = {x * cellSize + padding, y * cellSize + padding};
        Vector2 end1 = {(x + 1) * cellSize - padding, (y + 1) * cellSize - padding};
        Vector2 start2 = {(x + 1) * cellSize - padding, y * cellSize + padding};
        Vector2 end2 = {x * cellSize + padding, (y + 1) * cellSize - padding};

        Color drawColor = X_COLOR;
        if (hover) {
            drawColor = Fade(X_COLOR, 0.25);
        }

        DrawLineEx(start1, end1, thickness, drawColor);
        DrawLineEx(start2, end2, thickness, drawColor);
    } else if (player == O) {
        int radius = cellSize / 2;

        Color drawColor = O_COLOR;
        if (hover) {
            drawColor = Fade(O_COLOR, 0.25);
        }

        for (int i = 0; i < thickness; i++) {
            DrawCircleLines(x * cellSize + cellSize / 2, y * cellSize + cellSize / 2, radius - i - radius * TOTAL_PADDING, drawColor);
        }
    }
}

/**
 * Draw the current state of the board.
 *
 * Draw the whole board with the current state of the game.
 *
 */

void drawState() {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            draw(board[j * sizeX + i], i, j, 0);
        }
    }
}

int drawResult(Cell winner) {
    Color color = window.bg;
    color = ColorAlpha(color, 0.75);
    DrawRectangle(0, 0, window.width, window.height, color);
    char* text;

    switch (winner) {
        case X:
            text = "X WINS!";
            break;
        case O:
            text = "O WINS!";
            break;
        default:
            text = "DRAW!";
            break;
    }

    DrawTextCentered(text, (Rectangle) {0, 0, window.width, window.height - 100}, TEXT_SIZE, window.fg);
    DrawTextCentered("Press R for Restart, ESC to quit", (Rectangle) {0, 0, window.width, window.height + 100}, TEXT_SIZE, window.fg);
    return 0;
}

/**
 * Check if the player is winning.
 *
 * Check if the player is winning in the current state of the board. It checks
 * for horizontal, vertical and diagonal wins.
 *
 * @param player The player to check
 * @return If the player is winning
 *
 */

bool areYouWinningSon(Cell player) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (board[j * sizeX + i] == player) {
                int count = 1;
                bool case1 = i + inARow <= sizeX + 1;
                bool case2 = j + inARow <= sizeY + 1;
                bool case3 = i - inARow >= -1;

                if (case1) {
                    for (int k = 1; k < inARow; k++) {
                        if (board[j * sizeX + i + k] == player) {
                            count++;
                        }
                    }

                    if (count == inARow) {
                        return true;
                    }
                }

                if (case2) {
                    count = 1;
                    for (int k = 1; k < inARow; k++) {
                        if (board[(j + k) * sizeX + i] == player) {
                            count++;
                        }
                    }
                    if (count == inARow) {
                        return true;
                    }

                    if (case1) {
                        count = 1;
                        for (int k = 1; k < inARow; k++) {
                            if (board[(j + k) * sizeX + i + k] == player) {
                                count++;
                            }
                        }
                        if (count == inARow) {
                            return true;
                        }
                    }

                    if (case3) {
                        count = 1;
                        for (int k = 1; k < inARow; k++) {
                            if (board[(j + k) * sizeX + i - k] == player) {
                                count++;
                            }
                        }
                        if (count == inARow) {
                            return true;
                        }

                    }
                }
            }
        }
    }

    return false;
}

int gameState() {
    if (areYouWinningSon(X)) {
        return X_WINS;
    } else if (areYouWinningSon(O)) {
        return O_WINS;
    }

    for (int i = 0; i < sizeX * sizeY; i++) {
        if (board[i] == EMPTY) {
            return ONGOING;
        }
    }

    return DRAW;
}

// Handle some input
void Update(void) {
    if (gameState() != ONGOING) {
        gameOver = true;
    }

    if (IsKeyPressed(KEY_R)) {
        free(board);
        initGame();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        gameOver = true;
        free(board);
    }
}

// Draw the icon when the mouse is hovering
void Draw(void) {
    for (int i = 1; i < sizeX; i++) {
        DrawRectangle(i * cellSize - (thickness >> 1), 0, thickness, window.height, window.fg);
    }

    for (int i = 1; i < sizeY; i++) {
        DrawRectangle(0, i * cellSize - (thickness >> 1), window.width, thickness, window.fg);
    }

    int hoverX = GetMouseX() / cellSize;
    int hoverY = GetMouseY() / cellSize;

    drawState();

    if (board[hoverY * sizeX + hoverX] == EMPTY && !gameOver) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            setBoard(hoverX, hoverY);
        } else {
            draw(currentTurn, hoverX, hoverY, 1);
        }
    }


    if (gameOver) {
        drawResult(gameState());
    }
}

void DeInit(void) {
    free(board);
}

void tictactoe(int x, int y, int size) {
    sizeX = x;
    sizeY = y;
    inARow = size;
    cellSize = MAX_WINDOW_SIZE / max(sizeX, sizeY);
    window.width = sizeX * cellSize;
    window.height = sizeY * cellSize;
    newGameWindow(&window, initGame, Update, Draw, DeInit);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        fprintf(stderr, "Error: Please launch the game with the Game UI.\n");
        return EXIT_FAILURE;
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);
    int arg3 = atoi(argv[3]);


    tictactoe(arg1, arg2, arg3);

    return 0;
}
