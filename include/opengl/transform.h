#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


class Transform
{
public:
    Transform(glm::vec3 pos = glm::vec3(0, 0, 0), glm::vec3 rot = glm::vec3(0, 0, 0), glm::vec3 scale = glm::vec3(1, 1, 1))
        : position(pos), rotation(rot), scale(scale)
    {
        transformMatrix *= glm::scale(transformMatrix, scale);
        transformMatrix *= glm::translate(transformMatrix, position);
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.x), glm::vec3(1, 0, 0));
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.y), glm::vec3(0, 1, 0));
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.z), glm::vec3(0, 0, 1));
    }

    void setPosition(glm::vec3 pos)
    {
        position = pos;
        transformMatrix *= glm::translate(transformMatrix, pos);
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.x), glm::vec3(1, 0, 0));
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.y), glm::vec3(0, 1, 0));
        transformMatrix *= glm::rotate(transformMatrix, (float) glm::radians(rotation.z), glm::vec3(0, 0, 1));
        transformMatrix *= glm::scale(transformMatrix, scale);
    }

    void setScale(glm::vec3 scale)
    {
        this->scale = scale;
        transformMatrix *= glm::scale(transformMatrix, scale);
        transformMatrix *= glm::translate(transformMatrix, position);
    }    

    glm::vec3   position = glm::vec3(0.0f);
    glm::vec3   rotation = glm::vec3(0.0f);
    glm::vec3   scale = glm::vec3(1.0f);
    glm::mat4   transformMatrix = glm::mat4(1.0f);    
};

