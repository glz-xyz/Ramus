#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

namespace ramus
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec2 texCoords;
    };

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
        ~Mesh();
    };
}