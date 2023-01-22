//
//  Mesh.hpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
// 
#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <vector>


#include "Materials.hpp"
#include "Mesh.hpp"


 
class Model
{
public:
    Mesh* Mesh;
    std::vector<Material*> Materials;
    Model(class Mesh* mesh) {     // Constructor
        Mesh = mesh;
    }
    Model() {     // Constructor
        
    }
    
    static Model* Load(std::string File);
};

#endif /* Mesh_hpp */
