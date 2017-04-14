#include <SDL2/SDL.h>

#define GLEW_STATIC
#include "GL/glew.h"

#include <SDL2/SDL_opengl.h>


#include "defines.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define USE_GL_MAJOR_VERSION 3
#define USE_GL_MINOR_VERSION 3

bool g_quit = false;


int main(int argc, char** argv) 
{
    LOG("Demo 01\n");

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_GLContext gl_context = NULL;

    if ( NOTOK(SDL_Init(SDL_INIT_VIDEO)) )
    {
        ABORT("SDL_Init failed!\n");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, USE_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, USE_GL_MINOR_VERSION);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    window = SDL_CreateWindow("Demo 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if ( ISNULL(window) )
    {
        ABORT("Failed to create window!\n");
    }

    gl_context = SDL_GL_CreateContext( window );
    if ( ISNULL(gl_context) )
    {
        ABORT("Could not create OpenGL context\n");
    }

    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        ABORT("Could not initialize GLEW\n");
    }

    if (NOTOK(SDL_GL_SetSwapInterval(1)))
    {
        LOG("WARNING: could not set vsync!\n");
    }
    
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glViewport(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

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
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) g_quit = true;
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    LOG("Bye bye, thanks for playing\n");
    return 0;
}