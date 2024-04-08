#include "board.h"
struct Board board;

void init_board(struct Board *board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board->board[i][j] = 0;
        }
    }
}

void draw_board() {
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xBE, 0x98, 0xFF );
    for (int i = 1; i < 3; i++) {
        for (int j = 0; j < LINE_WIDTH; j++)
        {
            SDL_RenderDrawLine(gRenderer, i * WINDOW_SIZE / 3 + j, 0, i * WINDOW_SIZE / 3 + j, WINDOW_SIZE);
            SDL_RenderDrawLine(gRenderer, 0, i * WINDOW_SIZE / 3 + j, WINDOW_SIZE, i * WINDOW_SIZE / 3 + j);
        }
    }
}

void draw_x(int x, int y) {
    SDL_SetRenderDrawColor( gRenderer, 0xE2, 0xBF, 0xB3, 0xFF );
    for (int i = 0; i < 1.4*LINE_WIDTH; i++) {
        SDL_RenderDrawLine(gRenderer,
                x * WINDOW_SIZE / 3 + PAD + i,
                y * WINDOW_SIZE / 3 + PAD - i + 14,
                (x + 1) * WINDOW_SIZE / 3 - PAD + i,
                (y + 1) * WINDOW_SIZE / 3 - PAD - i + 14);
        SDL_RenderDrawLine(gRenderer,
                (x + 1) * WINDOW_SIZE / 3 - PAD + i,
                y * WINDOW_SIZE / 3 + PAD + i,
                x * WINDOW_SIZE / 3 + PAD + i,
                (y + 1) * WINDOW_SIZE / 3 - PAD + i);
    }
}

void draw_o(int x, int y) {
    SDL_SetRenderDrawColor( gRenderer, 0xF7, 0xDE, 0xD0, 0xFF );
    int cx = x * WINDOW_SIZE / 3 + WINDOW_SIZE / 6;
    int cy = y * WINDOW_SIZE / 3 + WINDOW_SIZE / 6;
    int r = WINDOW_SIZE / 6 - PAD;
    for (int i = 0; i < 1.4*LINE_WIDTH; i++) {
        for (int j = 0; j < 360; j++) {
            double angle = j * PI / 180;
            int x1 = cx + r * cos(angle);
            int y1 = cy + r * sin(angle);
            int x2 = cx + r * cos(angle + PI / 180);
            int y2 = cy + r * sin(angle + PI / 180);
            SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
        }
        
        r += 1;
    }
}

void draw_board_state() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board.board[i][j] == 1) {
                draw_x(i, j);
            } else if (board.board[i][j] == -1) {
                draw_o(i, j);
            }
        }
    }
}

void update_board(int *mPos) {
    int x = mPos[0] / (WINDOW_SIZE / 3);
    int y = mPos[1] / (WINDOW_SIZE / 3);

    if (!board.board[x][y]) {
        board.board[x][y] = 1;
    }
}

void draw_result() {
    SDL_Rect blur = {0, 0, WINDOW_SIZE, WINDOW_SIZE};
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( gRenderer, 0xFE, 0xEC, 0xE2, 0xAA );
    SDL_RenderFillRect(gRenderer, &blur);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("assets/RedditMono-SemiBold.ttf", 100);
    SDL_Color color = {0xFF, 0xBE, 0x98, 0xFF};
    SDL_Surface* surface;
    if (is_winner(board.board, X)) {
        surface = TTF_RenderText_Solid(font, "X WINS!", color);
    } else if (is_winner(board.board, O)) {
        surface = TTF_RenderText_Solid(font, "O WINS!", color);
    } else {
        surface = TTF_RenderText_Solid(font, "DRAW", color);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    SDL_Rect rect = {WINDOW_SIZE / 2 - surface->w / 2, WINDOW_SIZE / 2 - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);
    TTF_Quit();
}
