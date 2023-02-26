#pragma once
#include <string>
#include <glm/glm.hpp>
#include "opengl/texture2d.h"
#include "opengl/program.h"
#include "opengl/shapes/quad.h"

class Entity
{
public:
    unsigned int id;
    glm::vec2 position;
    std::string name;
    std::string icon;

    Entity(const unsigned int& p_id, const std::string& p_name, const std::string& p_icon, const glm::vec2& p_position);
    Entity(const unsigned int& p_id, const std::string& p_name, const std::string& p_icon);
    ~Entity();

    void setPosition(glm::vec2 position);

    void draw(Program& p_program);

private:
    Texture2D *_texture;
    Mesh *_mesh;

    void _createMesh();
};