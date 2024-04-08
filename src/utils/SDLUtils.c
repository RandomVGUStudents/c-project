#include "SDLUtils.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

bool SDLUtils_init(int width, int height, const char* title)
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    gWindow = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_SHOWN
            );

    if(!gWindow)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if (!gRenderer) {
        printf("Error creating SDL Renderer. SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    return true;
}

void SDLUtils_quit()
{
    SDL_DestroyRenderer( gRenderer );
    gRenderer = NULL;
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    SDL_Quit();
}
