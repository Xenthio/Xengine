//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGl/glu.h>
#else
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stdio.h>
#include <string>
#include "Render/Renderer.hpp"
#include "Render/Inputs.hpp"
#include "CSInterop.h"

typedef int32_t i32;
typedef uint32_t u32;
typedef int32_t b32;

#define DefaultWindowWidth 800
#define DefaultWindowHeight 600



struct SceneCamera {
public:
    glm::vec3 Position;
    glm::quat Rotation;
};

int main(int argc, char* args[])
{
    struct SceneCamera Camera = *new struct SceneCamera();
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
       // bool a = Project::CSMain::OnFrame();
        //if (a == true) {
            
            printf("real");
        //}
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
        // START MOVE TO C#
        
        float speed = 0.1f;
        const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_W]) {
                Camera.Position.x += speed;
            }
            if (state[SDL_SCANCODE_S]) {
                Camera.Position.x -= speed;
            }
            if (state[SDL_SCANCODE_A]) {
                Camera.Position.y += speed;
            }
            if (state[SDL_SCANCODE_D]) {
                Camera.Position.y -= speed;
            }
        // END MOVE TO C#
        DoInputs();
        
        glViewport(0, 0, DefaultWindowWidth, DefaultWindowHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glRotatef(1, 0.0f, 1.0f, 0.0f);
            glRotatef(1, 1.0f, 0.0f, 0.0f);
            glTranslatef(Camera.Position.x, Camera.Position.y, Camera.Position.z);
        
        DoRender();
        
        glBindVertexArray(VertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3 );
        
        SDL_GL_SwapWindow(Window);
    }
    return 0;
}
