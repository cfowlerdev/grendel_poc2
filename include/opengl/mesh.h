#pragma once
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>
#include "opengl/program.h"
#include "opengl/vertexarray.h"
#include "opengl/vertexbuffer.h"
#include "opengl/indexbuffer.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    bool operator == (const Vertex& vertex) const
    {
        return (position == vertex.position) && (texCoords == vertex.texCoords);
    }
};

namespace std 
{
    template<> struct hash<Vertex>
    {
        size_t operator() (Vertex const& vertex) const
        {
            return(hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec2>()(vertex.texCoords) << 1));
        }
    };
}

enum TextureType { 
    TEXTURE_SPECULAR, 
    TEXTURE_NORMAL, 
    TEXTURE_BUMP,
    TEXTURE_ALPHA 
};

struct Texture
{
    GLuint      id;
    std::string type;
    std::string path;
};

class Mesh
{
public:

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    // Transform worldTransform;

    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
   
    void bindResources(Program& p_program);
    void draw(Program& p_program);
private:
    VertexArray *_vao;
    VertexBuffer *_vbo;
    IndexBuffer *_ibo;
   
    void generateMesh();
};

