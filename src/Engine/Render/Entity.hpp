//
//  ModelEntity.hpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#ifndef Entity_hpp
#define Entity_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp> 

class Entity {
    glm::vec3 Position;
    glm::quat Rotation;
};
#endif /* ModelEntity_hpp */
