//
//  Mesh.cpp
//  Xengine
//
//  Created by Xenthio on 21/1/2023.
//

#include "Model.hpp"
#include "Mesh.hpp"
#include <string>
#include <stdio.h>
 
Model* Model::Load(std::string File)
{
    
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    
    class Model* newModel = new class Model();
    class Mesh* newMesh = new class Mesh();
    // Return a model from a file
    FILE * file = fopen(File.c_str(), "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return newModel;
    }
    while( 1 ){
        
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        // else : parse lineHeader
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return newModel;
            }
            newMesh->VertexIndices.push_back(vertexIndex[0]);
            newMesh->VertexIndices.push_back(vertexIndex[1]);
            newMesh->VertexIndices.push_back(vertexIndex[2]);
            newMesh->UVIndices    .push_back(uvIndex[0]);
            newMesh->UVIndices    .push_back(uvIndex[1]);
            newMesh->UVIndices    .push_back(uvIndex[2]);
            newMesh->NormalIndices.push_back(normalIndex[0]);
            newMesh->NormalIndices.push_back(normalIndex[1]);
            newMesh->NormalIndices.push_back(normalIndex[2]);
        }
        for( unsigned int i=0; i<newMesh->VertexIndices.size(); i++ ){

            // Get the indices of its attributes
            unsigned int vertexIndex = newMesh->VertexIndices[i];
            unsigned int uvIndex = newMesh->UVIndices[i];
            unsigned int normalIndex = newMesh->NormalIndices[i];
                
            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
            glm::vec2 uv = temp_uvs[ uvIndex-1 ];
            glm::vec3 normal = temp_normals[ normalIndex-1 ];
            
            // Put the attributes in buffers
            newMesh->Vertices.push_back(vertex);
            newMesh->UVs.push_back(uv);
            newMesh->Normals.push_back(normal);
            
        }
    }
    return new Model(newMesh);
}
