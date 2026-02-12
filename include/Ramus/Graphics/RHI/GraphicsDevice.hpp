#pragma once

#include "Ramus/Graphics/RHI/GraphicsContext.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace ramus
{
    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        virtual void Init() = 0;
        
        virtual void SetClearColor(const glm::vec4& clearColor) = 0;
        virtual void Clear() = 0;
        virtual void Present() = 0;
    };
}