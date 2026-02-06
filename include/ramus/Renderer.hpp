#pragma once

#include <glm/glm.hpp>

namespace ramus
{

    class Renderer
    {
    public:
        static void Init();
        static void Clear();
        static void SetClearColor(const glm::vec4& color);
    };

}