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
#include <glm/gtx/euler_angles.hpp>
#include <stdio.h>
#include <string>
#include<iostream>
#include<fstream>
#include<sstream>
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
    glm::vec3 Rotation;

    glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Forward = glm::vec3(0.0f, 1.0f, 0.0f);// glm::normalize(Position - CameraTarget);
    glm::vec3 Right = glm::normalize(glm::cross(up, Forward));
    glm::vec3 Up = glm::cross(Forward, Right);
};

int main(int argc, char* args[])
{
    struct SceneCamera Camera = *new struct SceneCamera();
    u32 WindowFlags = SDL_WINDOW_OPENGL;
    SDL_Window *Window = SDL_CreateWindow("Xengine", 32, 32, DefaultWindowWidth, DefaultWindowHeight, WindowFlags);
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

    GLuint UVBuffer = 1;
    glGenBuffers(1, &UVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, UVBuffer); 

    // LOAD SHADERS //

    std::ifstream in("base/shaders/core.fsh");
    std::string contents((std::istreambuf_iterator<char>(in)),
        std::istreambuf_iterator<char>());

    const char* fragShaderSrc = contents.c_str();


    std::ifstream in2("base/shaders/core.vsh");
    std::string contents2((std::istreambuf_iterator<char>(in2)),
        std::istreambuf_iterator<char>());

    const char* vertShaderSrc = contents2.c_str();

    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAG::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int vertShader;
    vertShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    int  success2;
    char infoLog2[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success2);
    if (!success2)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::VERT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragShader);
    //glAttachShader(shaderProgram, vertShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
    // ------------ //



    int MouseX, MouseY;
    int LastMouseX = 0;
    int LastMouseY = 0;
    SDL_SetRelativeMouseMode(SDL_TRUE);  
    while (Running)
    {
       // bool a = Project::CSMain::OnFrame();
        //if (a == true) {
            
        //    printf("real");
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
        Camera.Forward.x = cos(glm::radians(Camera.Rotation.y)) * cos(glm::radians(Camera.Rotation.x));
        Camera.Forward.y = sin(glm::radians(Camera.Rotation.x));
        Camera.Forward.z = sin(glm::radians(Camera.Rotation.y)) * cos(glm::radians(Camera.Rotation.x));

        Camera.Right = glm::normalize(glm::cross(Camera.up, Camera.Forward));
        Camera.Up = glm::cross(Camera.Forward, Camera.Right);
        //right_ = glm::normalize(glm::cross(front_, WORLD_UP));
        //up_ = glm::normalize(glm::cross(right_, front_));
        //view_ = glm::lookAt(position_, position_ + front_, up_);

        // START MOVE TO C#
        
        float speed = 0.1f;
        const Uint8 *state = SDL_GetKeyboardState(NULL);
            if (state[SDL_SCANCODE_W]) {
                Camera.Position += speed * Camera.Forward;
            }
            if (state[SDL_SCANCODE_S]) {
                Camera.Position -= speed * Camera.Forward;
            }
            if (state[SDL_SCANCODE_A]) {
                Camera.Position += speed * Camera.Right;
            }
            if (state[SDL_SCANCODE_D]) {
                Camera.Position -= speed * Camera.Right;
            }

            if (state[SDL_SCANCODE_SPACE]) {
                Camera.Position += speed * Camera.up;
            }
            if (state[SDL_SCANCODE_LCTRL]) {
                Camera.Position -= speed * Camera.up;
            }

            float sensitivity = 0.1f;

            int xrel = 0;
            int yrel = 0;
            SDL_GetRelativeMouseState(&xrel, &yrel);  
            
            Camera.Rotation.x += yrel * -sensitivity;
            if (Camera.Rotation.x > 89) {
                Camera.Rotation.x = 89;
            }
            if (Camera.Rotation.x < -89) {
                Camera.Rotation.x = -89;
            }
            Camera.Rotation.y += xrel * sensitivity;




        // END MOVE TO C#
        DoInputs();

        glViewport(0, 0, DefaultWindowWidth, DefaultWindowHeight);
        glClear(GL_COLOR_BUFFER_BIT);

        // VBO and VBA stuff
        glBindBuffer(GL_ARRAY_BUFFER,VertexBufferObject);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);


        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        //glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
        //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
        //glEnableVertexAttribArray(1);


        //set projection to perspective
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // 90 fov, 4/3 aspect, 0.4 nearz, 8000 farz;
        gluPerspective(90, 4 / 3, 0.4, 8000);
        glMatrixMode(GL_MODELVIEW);

        // set camera position and rotation
        glLoadIdentity();
        glm::mat4 view = glm::lookAt(Camera.Position, Camera.Position + Camera.Forward, Camera.up);
        
        glMultMatrixf(&view[0][0]);
        //move to shader
        
        // Render, todo iterate thru modelentities and draw them all
        DoRender();
        
        glBindVertexArray(VertexArrayObject);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 256 );
        
        SDL_GL_SwapWindow(Window);
    }
    return 0;
}
