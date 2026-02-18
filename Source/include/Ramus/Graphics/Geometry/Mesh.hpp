#pragma once

#include "Ramus/Graphics/Geometry/Vertex.hpp"

namespace ramus
{
    struct Mesh
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        
        float CalculateVolume() const;
    };
}