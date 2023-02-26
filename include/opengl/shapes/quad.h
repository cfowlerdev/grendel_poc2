#pragma once
#include "opengl/mesh.h"

class Quad {
    
public:
    Mesh *p_mesh;

    // float QuadVertices[] = {
    //     // positions            // texture coords
    //     0.5f,  0.5f, 0.0f,      1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,      1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
    //     -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left 
    // };

    // unsigned int QuadIndices[] = {  
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    Quad(GLuint& p_textureId)
    {
        std::vector<Vertex> vertices;
        Vertex v1, v2, v3, v4;
        v1.position = glm::vec3(0.5f,  0.5f, 0.0f);
        v1.texCoords = glm::vec2(1.0f, 1.0f);
        vertices.push_back(v1);
        v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
        v2.texCoords = glm::vec2(1.0f, 0.0f);
        vertices.push_back(v2);
        v3.position = glm::vec3(-0.5f, -0.5f, 0.0f);
        v3.texCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(v3);
        v4.position = glm::vec3(-0.5f,  0.5f, 0.0f);
        v4.texCoords = glm::vec2(0.0f, 1.0f);
        vertices.push_back(v4);

        std::vector<GLuint> indices = {0, 1, 3, 1, 2, 3};
        std::vector<Texture> textures;
        Texture texture;
        texture.id = p_textureId;
        texture.type = "uTexture";
        textures.push_back(texture);

        p_mesh = new Mesh(vertices, indices, textures);
    }

    ~Quad()
    {
        
    }
private:
};
