#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_SIZE 720

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

bool SDLUtils_init(int width, int height, const char* title);

void SDLUtils_quit();

int SDLUtils_input();
