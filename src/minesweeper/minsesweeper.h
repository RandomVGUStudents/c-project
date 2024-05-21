#pragma once


#define row_minesweeper 15
#define column_minesweeper 15
#define minesweeper_tile_width 30
#define minesweeper_tile_height 30
#define mine_count  25


typedef enum 
{
    menu, gameplay, nah_id_win, stand_proud_youre_strong
}game_state;
typedef struct tile
{
    Vector2 location;
    bool is_opened;
    bool is_mine;
    bool is_flagged;
    bool is_hovered;
    int nearby_mine;
    Rectangle tile_rect;
}tile ;

void init_grid (tile **grid);
void draw_grid (tile **grid,Texture2D unopened_tile,Texture2D opened_tile,Texture2D flagged_tile,Texture2D mine_tile);
void update_grid (tile**grid,game_state *status_ptr,Sound death);
void domain_expansion(tile **grid,int x, int y);
void but_would_you_lose(tile **grid, game_state *status_ptr,Sound victory);
void draw_status(Texture2D gojo);
void minesweeper();