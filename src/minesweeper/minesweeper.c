#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "minesweeper_game.h"

const int  screen_width = column_minesweeper*minesweeper_tile_width;
const int  screen_height= row_minesweeper*minesweeper_tile_height+110;


void init_grid(tile **grid)//initialize the grid
{
    for(int i=0;i<row_minesweeper;i++)
    {
        for(int j=0;j<column_minesweeper;j++)
        {
            grid[i][j].location.x = j*minesweeper_tile_width;
            grid[i][j].location.y = i*minesweeper_tile_height;
            grid[i][j].is_opened = false;
            grid[i][j].is_flagged=false;
            grid[i][j].is_mine=false;
            grid[i][j].is_hovered=false;
            grid[i][j].tile_rect.height=minesweeper_tile_height;
            grid[i][j].tile_rect.width=minesweeper_tile_width;
            grid[i][j].tile_rect.x=grid[i][j].location.x;
            grid[i][j].tile_rect.y= grid[i][j].location.y;
        }
    }
    int mineplaced=0;
    while(mineplaced<mine_count)// Iterate until mineplaced equals mine_count
    {
        int x = GetRandomValue(0,row_minesweeper-1);
        int y = GetRandomValue(0,column_minesweeper-1);
        if(!grid[x][y].is_mine) // If no mine, then place the mine
        {
            grid[x][y].is_mine=true;
            mineplaced++;
        }
    }
    
    for (int i=0;i<row_minesweeper;i++)
    {
        for(int j=0;j<column_minesweeper;j++)
        {
            if(!grid[i][j].is_mine)// if mine then ignore
            {
                int count =0;
                for(int k=i-1;k<=i+1;k++)//row_minesweeper above, same, below
                {
                    for(int l=j-1;l<=j+1;l++)//column_minesweeper left, same, right
                    {
                        if(k>=0 && k<row_minesweeper && l>=0 && l<column_minesweeper)// Check if neighboring cell is within the grid
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

void draw_grid(tile **grid,Texture2D unopened_tile,Texture2D opened_tile,Texture2D flagged_tile,Texture2D mine_tile)
{
    ClearBackground((Color){235,235,235,1});
    for(int i=0; i<column_minesweeper;i++)
    {
        for(int j=0;j<row_minesweeper;j++)
        {
            Rectangle source_rec = (Rectangle) {0,0,minesweeper_tile_width,minesweeper_tile_height};
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

void update_grid (tile**grid, game_state *status_ptr, Sound death)
{
   
    Vector2 mouse_location = GetMousePosition();
    int x= (int) ((mouse_location.y)/minesweeper_tile_height); //check which row_minesweeper it is, i.e height/size per tile
    int y= (int) ((mouse_location.x )/minesweeper_tile_width);//check which column_minesweeper it is
    //DrawText(TextFormat("tile [%d;%d] ",x,y),0,300,50,BLACK); //test

    for (int i=0;i<row_minesweeper;i++)//resetting the hovered tile
    {
        for(int j=0;j<column_minesweeper;j++)
        {
            if(grid[i][j].is_hovered)
            {
                grid[i][j].is_hovered=false;
                goto touch_grass;
            }
        }
    }

    touch_grass:

    if(x<row_minesweeper && y<column_minesweeper)
    {
    grid[x][y].is_hovered=true;//darken the hovered tile
    }


    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if(x>row_minesweeper || y>column_minesweeper)//just in case someone think "outside" the box
        {}
        else
        if(!grid[x][y].is_mine)// not bomb then open
        {
            domain_expansion(grid,x,y);
        }
        else//if its bomb, display all mine, then switch to losing screen
        {
            for(int i =0;i<row_minesweeper;i++)
            {
                for(int j=0;j<column_minesweeper;j++)
                {
                    if(grid[i][j].is_mine)
                    {
                        grid[i][j].is_opened=true;
                    }
                }
            }
            PlaySound(death);
            *status_ptr = stand_proud_youre_strong;//lose, reveal all mine
            return;
        }
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) //flaging a tile
    {
        if(!grid[x][y].is_opened)
        {   
            if(!grid[x][y].is_flagged)
            {
                grid[x][y].is_flagged=true;
            }
            else
            {
                grid[x][y].is_flagged=false;
            }
        }
    }
}

void domain_expansion (tile **grid,int x, int y) //flood fill, open tile
{
    if (x<0 || x>=row_minesweeper || y<0 || y>=column_minesweeper ||  grid[x][y].is_mine ==true || grid[x][y].is_opened == true ) //if the button is not in bound or is a mine, then stop the show
    {
        return;
    }
    else
    { 
        if(grid[x][y].nearby_mine!=0)
        {
            grid[x][y].is_opened=true;
        }
        else
        {
            grid[x][y].is_opened=true;
            domain_expansion(grid,x+1,y);//north
            domain_expansion(grid,x+1,y+1);//north-east
            domain_expansion(grid,x,y+1);//east
            domain_expansion(grid,x-1,y+1);//south-east
            domain_expansion(grid,x-1,y);//south
            domain_expansion(grid,x-1,y-1);//south-west
            domain_expansion(grid,x,y-1);//west
            domain_expansion(grid,x+1,y-1);//north-west

        }
    }
}

void but_would_you_lose(tile **grid, game_state *status_ptr,Sound victory) //check if you win or not
{
    for(int i=0; i<row_minesweeper;i++)
    {
        for (int j=0; j<column_minesweeper;j++)
        {
            if(!grid[i][j].is_mine && !grid[i][j].is_opened )//if its normal tile and its not opened, then the game has yet to be won 
            {
                return;
            }
        }
    }
    PlaySound(victory);
    *status_ptr =nah_id_win; //you win, omedetou
}

void draw_status(Texture2D gojo)
{
    DrawTexture(gojo,(screen_width-gojo.width)/2,row_minesweeper*minesweeper_tile_height+5,WHITE);
    DrawRectangleLinesEx((Rectangle){(screen_width-gojo.width-10)/2,row_minesweeper*minesweeper_tile_height,gojo.width+5,gojo.height+10},5,BLACK);
}

void minesweeper()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    //InitWindow(screen_width,screen_height,"minesweeper");
    SetWindowSize(screen_width,screen_height);
    InitAudioDevice();
    
    Texture2D unopened_tile= LoadTexture("assets/unopened.png");
    Texture2D opened_tile= LoadTexture("assets/opened.png");
    Texture2D flagged_tile= LoadTexture("assets/flagged.png");
    Texture2D mine_tile= LoadTexture("assets/bomb.png");
    Texture2D gojo_default = LoadTexture("assets/gojo_default_small.png");
    Texture2D gojo_win = LoadTexture("assets/gojo_win_small.png");
    Texture2D gojo_lose = LoadTexture("assets/gojo_lose_small.png");
    Texture2D logo= LoadTexture("assets/logo_official.png");
    Music bgm = LoadMusicStream("audio/New Tim Follin Song 2021.mp3");
    Sound victory = LoadSound("audio/snd_dumbvictory.wav");
    Sound death = LoadSound("audio/snd_damage.wav");
    

    tile **grid = (tile**) malloc(row_minesweeper*sizeof(tile));// create array of tiles
    for(int i=0;i<column_minesweeper;i++)
    {
        grid[i]=(tile*) malloc(column_minesweeper*sizeof(tile));
    }
    game_state  status = menu;
    game_state *status_ptr = &status;

    //--------------------------------------------------------------------------------------

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    PlayMusicStream(bgm); 
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateMusicStream(bgm);
        switch (status)
        {
        case gameplay: //standard gameplay loop           
            BeginDrawing();
            draw_status(gojo_default);
            update_grid(grid, status_ptr,death);
            draw_grid(grid,unopened_tile,opened_tile,flagged_tile,mine_tile);
            but_would_you_lose(grid,status_ptr,victory);
            EndDrawing();
            break;
        
        case nah_id_win: //win
            StopMusicStream(bgm);
            BeginDrawing();
            draw_grid(grid,unopened_tile,opened_tile,flagged_tile,mine_tile);
            draw_status(gojo_win);
            DrawRectangle(0,0,screen_width,screen_height,ColorAlpha(WHITE,0.5));
            DrawText("You won, press R for reset",(-MeasureText("You won, press R for reset",30)+screen_width)/2,(screen_height+15)/2,30,BLACK);
            if(IsKeyPressed(KEY_R))
            {
                init_grid(grid);
                PlayMusicStream(bgm);
                status = gameplay;
            }
            if(IsKeyPressed(KEY_M))
            {
                status = menu;
            }
            EndDrawing();
            break;

        case stand_proud_youre_strong: //lost
            StopMusicStream(bgm);
            BeginDrawing();
            draw_status(gojo_lose);
            
            draw_grid(grid,unopened_tile,opened_tile,flagged_tile,mine_tile);
            DrawRectangle(0,0,screen_width,screen_height,ColorAlpha(WHITE,0.5));
            DrawText("You lost, press R for reset",(-MeasureText("You lost, press R for reset",30)+screen_width)/2,(screen_height+15)/2,30,BLACK);
            if(IsKeyPressed(KEY_R))// reset game
            {
                init_grid(grid);
                PlayMusicStream(bgm);
                status = gameplay;
            }
            
            if(IsKeyPressed(KEY_M))// reset game
            {
                status = menu;
            }
            EndDrawing();
            break;

        case menu:    
            BeginDrawing();
            ClearBackground(WHITE);
            PlayMusicStream(bgm);
            DrawTextureEx(logo,(Vector2) {(screen_width-logo.width)/2,(screen_height-450)/2},0,1,WHITE);
            DrawText("press ENTER to start game",(screen_width-MeasureText("press ENTER to start game",30))/2,(screen_height+100)/2,30,BLACK);
            if (IsKeyPressed(KEY_ENTER))
            {
                init_grid(grid);
                status = gameplay;
            }
            EndDrawing();  
        }
    }
    for(int i = 0; i < row_minesweeper; i++)
    {
        free(grid[i]);
    }
    free(grid);
    CloseAudioDevice();
    UnloadTexture(mine_tile);
    UnloadTexture(opened_tile);
    UnloadTexture(unopened_tile);
    UnloadTexture(flagged_tile);
    UnloadTexture(gojo_default);
    UnloadTexture(gojo_lose);
    UnloadTexture(gojo_win);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return;
}

