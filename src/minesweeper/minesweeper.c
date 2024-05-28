#include "minesweeper.h"

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

struct WindowAttr *window;
tile **grid;
game_state status;
game_state *status_ptr = &status;

int row;
int column;
int mine_count;

void init_grid()//initialize the grid
{
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            grid[i][j].location.x = j*CELL_SIZE;
            grid[i][j].location.y = i*CELL_SIZE;
            grid[i][j].is_opened = false;
            grid[i][j].is_flagged = false;
            grid[i][j].is_mine = false;
            grid[i][j].is_hovered = false;
        }
    }
    int mineplaced = 0;
    while(mineplaced < mine_count)// Iterate until mineplaced equals MINE_COUNT
    {
        int x = GetRandomValue(0,row - 1);
        int y = GetRandomValue(0,column - 1);
        if(!grid[x][y].is_mine) // If no mine, then place the mine
        {
            grid[x][y].is_mine = true;
            mineplaced++;
        }
    }
    
    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            if(!grid[i][j].is_mine)// if mine then ignore
            {
                int count = 0;
                for(int k = i - 1; k <= i + 1; k++)//row above, same, below
                {
                    for(int l = j - 1; l <= j + 1; l++)//column left, same, right
                    {
                        if(k >= 0 && k < row && l >= 0 && l < column)// Check if neighboring cell is within the grid
                        {
                            if(grid[k][l].is_mine)
                            {
                                count++;
                            }
                        }
                    }
                }
                grid[i][j].nearby_mine=count;// Assign the count of neighboring mines to the current cell
            }
        }
    }

}

void draw_grid()
{
    ClearBackground((Color){235,235,235,1});
    for(int i=0; i<column;i++)
    {
        for(int j=0;j<row;j++)
        {
            Rectangle source_rec = (Rectangle) {0,0,CELL_SIZE,CELL_SIZE};
            if(grid[i][j].is_opened)//is it opened, if yes then draw the content
            {
                if(grid [i][j].is_mine)
                {
                    DrawTextureRec(mine_tile,source_rec,grid[i][j].location,WHITE);
                }
                else// opened safe tile
                {
                    //DrawText(TextFormat("%d",grid[i][j].nearby_mine),grid[i][j].location.x,grid[i][j].location.x,5,BLACK);
                    source_rec.x= grid[i][j].nearby_mine*33;
                    DrawTextureRec(opened_tile,source_rec,grid[i][j].location,WHITE);
                }
            }
            else if (grid[i][j].is_flagged)//flagged tile
            {
                DrawTextureRec(flagged_tile,source_rec,grid[i][j].location,WHITE);
            }
            else
            {
                if(!grid[i][j].is_hovered)
                {
                    DrawTextureRec(unopened_tile,source_rec,grid[i][j].location,WHITE);
                }
                else
                {
                    DrawTextureRec(unopened_tile,source_rec,grid[i][j].location,DARKGRAY);
                }
            }
        }
    }
}

void domain_expansion(int x, int y) //flood fill, open tile
{
    if (x < 0
        || x >= row
        || y < 0
        || y >= column
        || grid[x][y].is_mine == true
        || grid[x][y].is_opened == true) //if the button is not in bound or is a mine, then stop the show
    {
        return;
    }
    else
    { 
        if(grid[x][y].nearby_mine != 0)
        {
            grid[x][y].is_opened=true;
        }
        else
        {
            grid[x][y].is_opened=true;
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

void update_grid()
{
    Vector2 mouse_location = GetMousePosition();
    int x = (int) ((mouse_location.y) / CELL_SIZE); //check which row it is, i.e height/size per tile
    int y = (int) ((mouse_location.x) / CELL_SIZE); //check which column it is
    //DrawText(TextFormat("tile [%d;%d] ",x,y),0,300,50,BLACK); //test

    for (int i = 0; i < row; i++)//resetting the hovered tile
    {
        for (int j = 0; j < column; j++)
        {
            if(grid[i][j].is_hovered)
            {
                grid[i][j].is_hovered = false;
                goto touch_grass;
            }
        }
    }

    touch_grass:

    if (x < row && y < column)
    {
        grid[x][y].is_hovered = true;//darken the hovered tile
    }


    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (x <= row && y <= column) //just in case someone think "outside" the box
        {
            if (!grid[x][y].is_mine)// not bomb then open
            {
                domain_expansion(x,y);
            }
            else//if its bomb, display all mine, then switch to losing screen
            {
                for (int i = 0; i < row; i++)
                {
                    for (int j = 0; j < column; j++)
                    {
                        if(grid[i][j].is_mine)
                        {
                            grid[i][j].is_opened = true;
                        }
                    }
                }
                PlaySound(death);
                *status_ptr = stand_proud_youre_strong;//lose, reveal all mine
                return;
            }
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) //flagging a tile
    {
        if (!grid[x][y].is_opened)
        {   
            grid[x][y].is_flagged = !grid[x][y].is_flagged;
        }
    }
}

void but_would_you_lose() //check if you win or not
{
    for(int i=0; i<row;i++)
    {
        for (int j=0; j<column;j++)
        {
            if(!grid[i][j].is_mine && !grid[i][j].is_opened)//if its normal tile and its not opened, then the game has yet to be won 
            {
                return;
            }
        }
    }
    PlaySound(victory);
    *status_ptr = nah_id_win; //you win, omedetou
}

void draw_status(Texture2D gojo)
{
    DrawTexture(gojo,(window->width-gojo.width)/2,row*CELL_SIZE+5,WHITE);
    DrawRectangleLinesEx((Rectangle){(window->width-gojo.width-10)/2,row*CELL_SIZE,gojo.width+5,gojo.height+10},5,BLACK);
}

void minesweeper(struct WindowAttr *w, int r, int c, int m)
{
    // Set window dimensions based on grid size
    window = w;
    window->width = c * CELL_SIZE;
    window->height = r * CELL_SIZE + 110;
    row = r;
    column = c;
    mine_count = m;
    

    InitWindow(window->width, window->height, "minesweeper");
    InitAudioDevice();

    // Load all textures and sounds
    unopened_tile = LoadTexture("assets/unopened.png");
    opened_tile = LoadTexture("assets/opened.png");
    flagged_tile = LoadTexture("assets/flagged.png");
    mine_tile = LoadTexture("assets/bomb.png");
    gojo_default = LoadTexture("assets/gojo_default_small.png");
    gojo_win = LoadTexture("assets/gojo_win_small.png");
    gojo_lose = LoadTexture("assets/gojo_lose_small.png");
    logo = LoadTexture("assets/logo_official.png");
    bgm = LoadMusicStream("audio/New Tim Follin Song 2021.mp3");
    victory = LoadSound("audio/snd_dumbvictory.wav");
    death = LoadSound("audio/snd_damage.wav");
    bool mute = false;

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
    status = menu;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    PlayMusicStream(bgm); 

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (mute)
        {
            StopMusicStream(bgm);
        }
        UpdateMusicStream(bgm);
        switch (status)
        {
        case gameplay: //standard gameplay loop           
            BeginDrawing();
            draw_status(gojo_default);
            update_grid();
            draw_grid();
            but_would_you_lose();
            EndDrawing();
            break;
        
        case nah_id_win: //win
            StopMusicStream(bgm);
            BeginDrawing();
            draw_grid();
            draw_status(gojo_win);
            DrawRectangle(0, 0, window->width, window->height, ColorAlpha(WHITE, 0.5));
            DrawTextCentered("You won, press R for reset", window->width, window->height, 30, BLACK);
            if (IsKeyPressed(KEY_R))
            {
                init_grid();
                PlayMusicStream(bgm);
                status = gameplay;
            }
            if (IsKeyPressed(KEY_M))
            {
                status = menu;
            }
            EndDrawing();
            break;

        case stand_proud_youre_strong: //lost
            StopMusicStream(bgm);
            BeginDrawing();
            draw_status(gojo_lose);
            draw_grid();
            DrawRectangle(0, 0, window->width, window->height, ColorAlpha(WHITE, 0.5));
            DrawTextCentered("You lost, press R for reset", window->width, window->height, 30, BLACK);
            if (IsKeyPressed(KEY_R)) // reset game
            {
                init_grid();
                PlayMusicStream(bgm);
                status = gameplay;
            }
            if (IsKeyPressed(KEY_M)) // return to menu
            {
                status = menu;
            }
            EndDrawing();
            break;

        case menu:    
            BeginDrawing();
            ClearBackground(WHITE);
            PlayMusicStream(bgm);
            DrawTextureEx(logo, (Vector2) {(window->width - logo.width) / 2, (window->height - 450) / 2}, 0, 1, WHITE);
            DrawTextCentered("press ENTER to start game", window->width, window->height, 30, BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                init_grid();
                status = gameplay;
            }
            if(IsKeyPressed(KEY_M))//mute game
            {
                mute=!mute;
            }
            EndDrawing();  
            break;
        }
    }

    // Free allocated memory
    for (int i = 0; i < row; i++)
    {
        free(grid[i]);
    }
    free(grid);

    // Unload resources
    CloseAudioDevice();
    UnloadTexture(mine_tile);
    UnloadTexture(opened_tile);
    UnloadTexture(unopened_tile);
    UnloadTexture(flagged_tile);
    UnloadTexture(gojo_default);
    UnloadTexture(gojo_lose);
    UnloadTexture(gojo_win);

    // De-Initialization
    CloseWindow(); // Close window and OpenGL context
    return;
}

