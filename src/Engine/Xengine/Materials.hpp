//
//  Materials.hpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#ifndef Materials_hpp
#define Materials_hpp

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
#include <glm/glm.hpp>

// Struct to hold materials loaded into OpenGL
struct Material
{
public:
    glm::vec3 RenderColour;
    
    glm::vec3 DiffuseColour;
    GLuint DiffuseTexture;
    GLuint MetalTexture;
    GLuint RoughnessTexture;
    bool HasDiffuseTexture;
};

#endif /* Materials_hpp */
