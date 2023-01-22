//
//  Materials.hpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#ifndef Materials_hpp
#define Materials_hpp

#include <stdio.h>
#include <glm/glm.hpp>

// Struct to hold materials loaded into OpenGL
struct Material
{
public:
    glm::vec3 RenderColour;
    
    glm::vec3 DiffuseColour;
    int DiffuseTexture;
    int MetalTexture;
    int RoughnessTexture;
    bool HasDiffuseTexture;
};

#endif /* Materials_hpp */
