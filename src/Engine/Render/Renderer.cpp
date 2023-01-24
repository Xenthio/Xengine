//
//  Renderer.cpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#include "Renderer.hpp"

#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#else
#include <SDL2/SDL.h>
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#endif

#include "../Xengine/Model.hpp"

#include <string>

Model* mdl;
bool DoRender() {
    glClearColor(0.f, 0.f, 1.f, 0.f);
    if (mdl == NULL) {
        mdl = Model::Load("base/models/cube.obj");
    }
    
    // Frame Events (C++ to C# somehow)
    
    glBufferData(GL_ARRAY_BUFFER, mdl->Mesh->Vertices.size() * sizeof(glm::vec3), &mdl->Mesh->Vertices[0], GL_STATIC_DRAW); 
   // glBufferData(GL_ARRAY_BUFFER, mdl->Mesh->UVs.size() * sizeof(glm::vec2), &mdl->Mesh->UVs[0], GL_STATIC_DRAW);  
    
    glColor3f(1.0, 0.0, 0.0); 
    return false;
}
