#include <iostream>
#include "entity.h"
#include "shaders/shader.h"

Entity::Entity(const unsigned int& p_id, const std::string& p_name, const std::string& p_icon, const glm::vec2& p_position)
    : id(p_id), name(p_name), icon(p_icon), position(p_position)
{
    _texture = new Texture2D(p_icon, 0);
    _createMesh();
}

Entity::Entity(const unsigned int& p_id, const std::string& p_name, const std::string& p_icon)
    : Entity(id, name, icon, glm::vec2(0.0f, 0.0f))
{}

Entity::~Entity()
{

}

void Entity::setPosition(glm::vec2 position)
{
    this->position = position;
}

void Entity::draw(Program& p_program)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 pos3d = glm::vec3(this->position.x, this->position.y, 0);
    model = glm::translate(model, pos3d);
    p_program.setMat4("uModel", model);

    _mesh->draw(p_program);
}

void Entity::_createMesh()
{
    std::vector<Vertex> quadVertices;
    std::vector<GLuint> quadIndices;
    std::vector<Texture> quadTextures;    

    Vertex v1, v2, v3, v4;
    v1.position = {0.5f, 0.5f, 0.0f};
    v1.texCoords = {0.0f, 0.0f};
    v2.position = {0.5f, -0.5f, 0.0f};
    v2.texCoords = {0.0f, 0.0f};
    v3.position = {-0.5f, -0.5f, 0.0f};
    v3.texCoords = {0.0f, 0.0f};
    v4.position = {-0.5f,  0.5f, 0.0f};
    v4.texCoords = {0.0f, 0.0f};

    quadIndices.push_back(0);
    quadIndices.push_back(1);
    quadIndices.push_back(3);
    quadIndices.push_back(1);
    quadIndices.push_back(2);
    quadIndices.push_back(3);

    quadVertices.push_back(v1);
    quadVertices.push_back(v2);
    quadVertices.push_back(v3);
    quadVertices.push_back(v4);

    // TODO: textures

    _mesh = new Mesh(quadVertices, quadIndices, quadTextures);
}

