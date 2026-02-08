#pragma once

#include <glm/glm.hpp>

namespace ramus 
{

    class GraphicsDevice
    {
    public:
        GraphicsDevice() = default;

        void SetClearColor(const glm::vec4& color);
        void Clear();
    };

}