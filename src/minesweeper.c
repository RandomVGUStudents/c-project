#include "headers/minesweeper.h"

Texture2D unopened_tile;
Texture2D opened_tile;
Texture2D flagged_tile;
Texture2D mine_tile;
Texture2D gojo_default;
Texture2D gojo_win;
Texture2D gojo_lose;
Texture2D logo;
Music bgm;
Sound victory;
Sound death;

struct WindowAttr window = {
    .title = "Minesweeper",
    .fps = 60,
    .bg = RAYWHITE,
    .fg = BLACK
};

tile **grid;
game_state status;
bool mute = false;

int row;
int column;
int mine_count;
int flagged;

void init_grid() { //initialize the grid
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            grid[i][j].location.x = j * CELL_SIZE;
            grid[i][j].location.y = i * CELL_SIZE;
            grid[i][j].is_opened = false;
            grid[i][j].is_flagged = false;
            grid[i][j].is_mine = false;
            grid[i][j].is_hovered = false;
            grid[i][j].nearby_mine = 0;
        }
    }

    int mineplaced = 0;
    while (mineplaced < mine_count) { // Iterate until mineplaced equals MINE_COUNT
        int x = GetRandomValue(0, row - 1);
        int y = GetRandomValue(0, column - 1);
        if (!grid[x][y].is_mine) { // If no mine, then place the mine
            grid[x][y].is_mine = true;
            mineplaced++;
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (!grid[i][j].is_mine) { //if mine then ignore
                int count = 0;
                for (int k = i - 1; k <= i + 1; k++) { //row above, same, below
                    for (int l = j - 1; l <= j + 1; l++) { //column left, same, right
                        if (k >= 0 && k < row && l >= 0 && l < column) { // Check if neighboring cell is within the grid
                            if (grid[k][l].is_mine) {
                                count++;
                            }
                        }
                    }
                }
                grid[i][j].nearby_mine = count; // Assign the count of neighboring mines to the current cell
            }
        }
    }

    flagged = 0;
}

void draw_grid() {
    ClearBackground((Color){235, 235, 235, 255});
    Rectangle total_mine = {(window.width + GOJO_SIZE) / 2.0 + BORDER_SIZE,
        row * CELL_SIZE, (window.width - GOJO_SIZE) / 2.0 - BORDER_SIZE, GOJO_SIZE / 2.0 + BORDER_SIZE};
    DrawTextCentered(TextFormat("Total mines: %d", mine_count), total_mine, 30, BLACK); //TODO
    Rectangle flagged_count = {total_mine.x, total_mine.y + total_mine.height, total_mine.width, total_mine.height};
    DrawTextCentered(TextFormat("Flagged count: %d", flagged), flagged_count, 30, BLACK); //TODO

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            Rectangle source_rec = {0, 0, CELL_SIZE, CELL_SIZE};
            if (grid[i][j].is_opened) { //is it opened, if yes then draw the content
                if (grid[i][j].is_mine) {
                    DrawTextureRec(mine_tile, source_rec, grid[i][j].location, WHITE);
                } else { //opened safe tile
                    source_rec.x = grid[i][j].nearby_mine * 33;
                    DrawTextureRec(opened_tile, source_rec, grid[i][j].location, WHITE);
                }
            } else if (grid[i][j].is_flagged) { //flagged tile
                DrawTextureRec(flagged_tile, source_rec, grid[i][j].location, WHITE);
            } else {
                DrawTextureRec(unopened_tile, source_rec, grid[i][j].location, grid[i][j].is_hovered ? DARKGRAY : WHITE);
            }
        }
    }
}

void domain_expansion(int x, int y) {//flood fill, open tile
    if (x < 0
        || x >= row
        || y < 0
        || y >= column
        || grid[x][y].is_mine == true
        || grid[x][y].is_opened == true) { //if the button is not in bound or is a mine, then stop the show
        return;
    } else { 
        if(grid[x][y].nearby_mine != 0) {
            grid[x][y].is_opened = true;
        } else {
            grid[x][y].is_opened = true;
            domain_expansion(x+1,y);//north
            domain_expansion(x+1,y+1);//north-east
            domain_expansion(x,y+1);//east
            domain_expansion(x-1,y+1);//south-east
            domain_expansion(x-1,y);//south
            domain_expansion(x-1,y-1);//south-west
            domain_expansion(x,y-1);//west
            domain_expansion(x+1,y-1);//north-west
        }
    }
}

void update_grid() {
    Vector2 mouse_location = GetMousePosition();
    int x = (int) (mouse_location.y / CELL_SIZE); //check which row it is, i.e height/size per tile
    int y = (int) (mouse_location.x / CELL_SIZE); //check which column it is
    //DrawText(TextFormat("tile [%d;%d] ",x,y),0,300,50,BLACK); //test

    for (int i = 0; i < row; i++) { //resetting the hovered tile
        for (int j = 0; j < column; j++) {
            if(grid[i][j].is_hovered) {
                grid[i][j].is_hovered = false;
                goto touch_grass;
            }
        }
    }

    touch_grass:

    if (x < row && y < column) {
        grid[x][y].is_hovered = true; //darken the hovered tile
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (x <= row && y <= column) { //just in case someone think "outside" the box
            if (!grid[x][y].is_mine) { //not bomb then open
                domain_expansion(x,y);
            } else { //if its bomb, display all mine, then switch to losing screen
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < column; j++) {
                        if(grid[i][j].is_mine) {
                            grid[i][j].is_opened = true;
                        }
                    }
                }
                PlaySound(death);
                status = stand_proud_youre_strong; //lose, reveal all mine
                return;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) { //flagging a tile
        if (!grid[x][y].is_opened) { 
            grid[x][y].is_flagged = !grid[x][y].is_flagged;
            if (grid[x][y].is_flagged)
                flagged++;
            else
                flagged--;
        }
    }
}

void but_would_you_lose() { //check if you win or not
    for(int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if(!grid[i][j].is_mine && !grid[i][j].is_opened) { //if its normal tile and its not opened, then the game has yet to be won 
                return;
            }
        }
    }
    PlaySound(victory);
    status = nah_id_win; //you win, omedetou
}

void draw_status(Texture2D gojo) {
    Rectangle gojo_box = {(window.width - GOJO_SIZE) / 2 - BORDER_SIZE,
        row * CELL_SIZE, GOJO_SIZE + BORDER_SIZE * 2, GOJO_SIZE + BORDER_SIZE * 2};
    DrawTexture(gojo, gojo_box.x + BORDER_SIZE, gojo_box.y + BORDER_SIZE, WHITE);
    DrawRectangleLinesEx(gojo_box, BORDER_SIZE, BLACK);
}

void end_game(bool win) {
    draw_status(win ? gojo_win : gojo_lose);
    draw_grid();
    DrawRectangle(0, 0, window.width, window.height, ColorAlpha(WHITE, 0.5));
    DrawTextCentered(TextFormat("You %s, press R for reset", win ? "won" : "lost"), (Rectangle) {0, 0, window.width, window.height}, 30, BLACK);
    if (IsKeyPressed(KEY_R)) {
        init_grid();
        status = gameplay;
    }
    if (IsKeyPressed(KEY_M)) {
        status = menu;
    }
}

void Init() {
    InitAudioDevice();

    // Load all textures and sounds
    unopened_tile = LoadTexture("assets/images/unopened.png");
    opened_tile = LoadTexture("assets/images/opened.png");
    flagged_tile = LoadTexture("assets/images/flagged.png");
    mine_tile = LoadTexture("assets/images/bomb.png");
    gojo_default = LoadTexture("assets/images/gojo_default_small.png");
    gojo_win = LoadTexture("assets/images/gojo_win_small.png");
    gojo_lose = LoadTexture("assets/images/gojo_lose_small.png");
    logo = LoadTexture("assets/images/logo_official.png");
    bgm = LoadMusicStream("assets/audios/New Tim Follin Song 2021.mp3");
    victory = LoadSound("assets/audios/snd_dumbvictory.wav");
    death = LoadSound("assets/audios/snd_damage.wav");
    status = menu;
    
    PlayMusicStream(bgm); 

    grid = (tile**) malloc(row * sizeof(tile*));
    if (!grid) {
        printf("Failed to allocate memory for grid.\n");
        return;
    }
    for (int i = 0; i < row; i++)
    {
        grid[i] = (tile*) malloc(column * sizeof(tile));
        if (!grid[i]) {
            printf("Failed to allocate memory for grid[%d].\n", i);
            return;
        }
    }
}

void Update() {
    if (IsKeyPressed(KEY_M)) {
        mute = !mute;
        if (mute) {
            PauseMusicStream(bgm);
        } else {
            ResumeMusicStream(bgm);
        }
    }

    if (!mute) {
        UpdateMusicStream(bgm);
    }
    switch (status)
    {
        case gameplay: //standard gameplay loop           
            draw_status(gojo_default);
            update_grid();
            draw_grid();
            but_would_you_lose();
            break;

        case nah_id_win: //win
            end_game(true);
            break;

        case stand_proud_youre_strong: //lost
            end_game(false);
            break;

        case menu:    
            ClearBackground(WHITE);
            DrawTextureEx(logo, (Vector2) {(window.width - logo.width) / 2, (window.height - 450) / 2}, 0, 1, WHITE);
            DrawTextCentered("press ENTER to start game", (Rectangle) {0, 0, window.width, window.height}, 30, BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                init_grid();
                status = gameplay;
            }
            break;
    }
}

void DeInit() {
    for (int i = 0; i < row; i++) {
        free(grid[i]);
    }
    free(grid);

    CloseAudioDevice();
    UnloadTexture(unopened_tile);
    UnloadTexture(opened_tile);
    UnloadTexture(flagged_tile);
    UnloadTexture(mine_tile);
    UnloadTexture(gojo_default);
    UnloadTexture(gojo_win);
    UnloadTexture(gojo_lose);
    UnloadTexture(logo);
    UnloadSound(victory);
    UnloadSound(death);
    UnloadMusicStream(bgm);
}

void minesweeper(int r, int c, int m)
{
    window.width = c * CELL_SIZE;
    window.height = r * CELL_SIZE + GOJO_SIZE + BORDER_SIZE * 2;
    row = r;
    column = c;
    mine_count = m;
    newGameWindow(&window, Init, Update, NULL, DeInit);
}

int main(int argc, char** argv) {

    if (argc != 4) {
        fprintf(stderr, "Error: Please launch the game with the Game Selector UI.\n");
        return EXIT_FAILURE;
    }

    int arg1 = atoi(argv[1]);
    int arg2 = atoi(argv[2]);
    int arg3 = atoi(argv[3]);

    minesweeper(arg1, arg2, arg3);

    return 0;
}
