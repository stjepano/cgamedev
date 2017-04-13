#include <SDL2/SDL.h>

#include "defines.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

bool g_quit = false;


int main(int argc, char** argv) 
{
    LOG("Demo 01\n");

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;

    if ( NOTOK(SDL_Init(SDL_INIT_VIDEO)) )
    {
        ABORT("SDL_Init failed!\n");
    }

    window = SDL_CreateWindow("Demo 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if ( ISNULL(window) )
    {
        ABORT("Failed to create window!\n");
    }

    surface = SDL_GetWindowSurface(window);

    SDL_Event event;
    while (!g_quit) 
    {
        while (SDL_PollEvent(&event) != 0) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    g_quit = true;
                    break;
            }
        }

        SDL_FillRect(surface, NULL, SDL_MapRGB( surface->format, 0xFF, 0x00, 0x00));
        SDL_UpdateWindowSurface(window);
    }

    LOG("Bye bye, thanks for playing\n");
    return 0;
}