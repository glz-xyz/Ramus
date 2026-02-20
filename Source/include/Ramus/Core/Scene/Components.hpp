#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace ramus
{

    struct TagComponent
    {
        TagComponent() = default;
        TagComponent(const std::string& tag) : tag(tag) {}

        std::string tag;
    };

    struct TransformComponent 
    {
        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation    = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale       = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        
        glm::mat4 GetTransform() const 
        {
            glm::mat4 rotation = glm::mat4(1.0f); // glm::toMat4(glm::quat(glm::radians(rotation)));

            return glm::translate(glm::mat4(1.0f), translation) 
                * rotation
                * glm::scale(glm::mat4(1.0f), scale);
        }
    };

    class Model;
    class Material;
    struct MeshComponent 
    {
        Model* mesh = nullptr;
        Material* material = nullptr;
    };
    
}