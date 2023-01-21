//
//  Mesh.hpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#ifndef Mesh_hpp
#define Mesh_hpp

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

#include <vector>
using std::vector;

#include <glm/vec3.hpp>

// Struct to hold mesh loaded into OpenGL
 struct Mesh
 {
     unsigned int drawCount = 0;
     unsigned int materialIndex = 0;
     GLuint indexBuffer;
     GLuint vertexBuffer;
     GLuint uvBuffer;
     GLuint vertexArrayObject;
     bool hasUvs = false;
 };
 
 // Struct to hold material loaded into OpenGL
 struct Material
 {
     glm::vec3 diffuseColor;
     GLuint diffuseTexture;
     bool hasDiffuseTexture;
 };
 
struct Model
 {
 std::vector<Mesh*> meshes;
 std::vector<Material*> materials;
 };

#endif /* Mesh_hpp */
