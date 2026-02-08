#pragma once

#include "Ramus/Graphics/Vertex.hpp"
#include "Ramus/Graphics/RHI/VertexArray.hpp"

#include <memory>
#include <vector>

namespace ramus
{

    class Mesh
    {
    public:
        Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
        ~Mesh() = default;

    private:
        std::unique_ptr<VertexArray> m_vertexArray;
        uint32_t m_numIndices;
    };

}