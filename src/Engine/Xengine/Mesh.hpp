//
//  Mesh.hpp
//  Xengine
//
//  Created by Xenthio on 22/1/2023.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <stdio.h>

#include <vector>

#include <glm/glm.hpp>

// Struct to hold mesh loaded into OpenGL
class Mesh
{
 public:
     unsigned int drawCount = 0;
     unsigned int materialIndex = 0;
     std::vector< unsigned int > VertexIndices, UVIndices, NormalIndices;
     std::vector< glm::vec3 > Vertices;
     std::vector< glm::vec2 > UVs;
     std::vector< glm::vec3 > Normals;
     bool hasUvs = false;
     Mesh() {     // Constructor
         
     }
};

#endif /* Mesh_hpp */
