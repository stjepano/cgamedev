#include <SDL2/SDL.h>

#define GLEW_STATIC
#include "GL/glew.h"

#include <SDL2/SDL_opengl.h>


#include "defines.h"
#include "gltools.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define USE_GL_MAJOR_VERSION 3
#define USE_GL_MINOR_VERSION 3

#define VERTEX_SHADER_SOURCE "#version 330 core\nlayout (location = 0) in vec3 position;\nvoid main()\n{\ngl_Position = vec4(position.x, position.y, position.z, 1.0);\n}"
#define FRAGMENT_SHADER_SOURCE "#version 330 core\nout vec4 color;\nvoid main()\n{\ncolor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}"

bool    g_quit      = false;
GLuint  g_vao       = 0;
GLuint  g_vbo       = 0;
GLuint  g_ebo       = 0;
GLuint  g_program   = 0;

error_t InitOpenGL();
void Render();

int main(int argc, char** argv) 
{
    LOG("Demo 01\n");

    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_GLContext gl_context = NULL;

    if ( FAILED(SDL_Init(SDL_INIT_VIDEO)) )
    {
        ABORT("SDL_Init failed!\n");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, USE_GL_MAJOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, USE_GL_MINOR_VERSION);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
    SDL_GL_MakeCurrent(window, gl_context);

    if ( FAILED(InitOpenGL()) )
    {
        ABORT("Could not initialize OpenGL: %s\n", GetError());
    }

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

        Render();
        
        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &g_vao);
    glDeleteBuffers(1, &g_vbo);
    glDeleteProgram(g_program);
    SDL_DestroyWindow(window);
    SDL_Quit();

    LOG("Bye bye, thanks for playing\n");
    return 0;
}


void Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(g_program);
    glBindVertexArray(g_vao);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


error_t InitOpenGL()
{
    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK)
    {
        return Error(13, "Could not initialize GLEW");
    }

    if (FAILED(SDL_GL_SetSwapInterval(1)))
    {
        LOG("WARNING: could not set vsync!\n");
    }
    

    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glViewport(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    GLuint indices[] = {0, 1, 2};

    GLuint vertex_shader, fragment_shader;
    if ( FAILED(GLT_CompileShader(GL_VERTEX_SHADER, VERTEX_SHADER_SOURCE, &vertex_shader)) )
    {
        return Error(1, "Failed to compile vertex shader: %s", GetError());
    }
    if ( FAILED(GLT_CompileShader(GL_FRAGMENT_SHADER, FRAGMENT_SHADER_SOURCE, &fragment_shader)) )
    {
        return Error(1, "Failed to compile fragment shader: %s", GetError());
    }
    
    GLuint shaders[] = { vertex_shader, fragment_shader };
    if ( FAILED(GLT_CreateProgram(shaders, 2, true, &g_program)) )
    {
        return Error(1, "Failed to link shader program: %s", GetError());
    }

    glGenVertexArrays(1, &g_vao);
    glBindVertexArray(g_vao);

    glGenBuffers(1, &g_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &g_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return NoError();
}
