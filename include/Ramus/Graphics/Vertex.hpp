#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace ramus
{

    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec2 texCoords;
    };

}