//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGl/glu.h>
#else
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/glu.h>
#endif

#include <stdio.h>
#include <string>
#include "Renderer.hpp"

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define DefaultWindowWidth 800
#define DefaultWindowHeight 600

int main ()
{
    
    u32 WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("Xengine", 0, 0, DefaultWindowWidth, DefaultWindowHeight, WindowFlags);
    assert(Window);
    SDL_GLContext Context = SDL_GL_CreateContext(Window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    b32 Running = 1;
    b32 FullScreen = 0;
    
    GLuint VertexArrayObject = 1;
    glGenVertexArrays(1, &VertexArrayObject);
    glBindVertexArray(VertexArrayObject);
    
    GLuint VertexBufferObject = 1;
    glGenBuffers(1, &VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
    
    
    while (Running)
    {
        SDL_Event Event;
        while (SDL_PollEvent(&Event))
        {
            if (Event.type == SDL_KEYDOWN)
            {
                switch (Event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Running = 0;
                        break;
                    case 'f':
                        FullScreen = !FullScreen;
                        if (FullScreen)
                        {
                            SDL_SetWindowFullscreen(Window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                        }
                        else
                        {
                            SDL_SetWindowFullscreen(Window, WindowFlags);
                        }
                        break;
                    default:
                        break;
                }
            }
            else if (Event.type == SDL_QUIT)
            {
                Running = 0;
            }
        }
        
        glViewport(0, 0, DefaultWindowWidth, DefaultWindowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(VertexArrayObject);
        DoRender();
        
        
        SDL_GL_SwapWindow(Window);
    }
    return 0;
}
