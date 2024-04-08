#include "tictactoe.h"

bool in_game = false;
bool bot = true;
enum GameState game_state = ONGOING;
int mPos[2] = {0, 0};

void new_game() {
    game_state = ONGOING;
    init_board(&board);
}

void process_input(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                in_game = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        in_game = false;
                        break;
                    case SDLK_F2:
                        new_game();
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (game_state != ONGOING) {
                    break;
                }
                SDL_GetMouseState(&mPos[0], &mPos[1]);
                int x = mPos[0] / (WINDOW_SIZE / 3);
                int y = mPos[1] / (WINDOW_SIZE / 3);
                game_state = move(board.board, x, y);
                if (game_state == ONGOING && bot) {
                    game_state = make_move(board.board);
                }
                if (game_state == INVALID) {
                    game_state = ONGOING;
                }
                break;
        }
    }
}

void game_loop() {
    in_game = SDLUtils_init(WINDOW_SIZE, WINDOW_SIZE, "Tic Tac Toe");
    while (in_game) {
        process_input();
        SDL_SetRenderDrawColor( gRenderer, 0xFE, 0xEC, 0xE2, 0xFF );
        SDL_RenderClear( gRenderer );

        draw_board();
        draw_board_state();

        if (game_state != ONGOING && game_state != INVALID) {
            draw_result();
        }

        SDL_RenderPresent( gRenderer );
    }
    SDLUtils_quit();
}
