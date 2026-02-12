#pragma once

#include "Ramus/Graphics/RHI/GraphicsDevice.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace ramus
{

    class Renderer
    {
    public:
        Renderer(std::unique_ptr<GraphicsDevice> graphicsDevice);

        void Init();
        void BeginFrame();
        void EndFrame();

    private:
        std::unique_ptr<GraphicsDevice> m_graphicsDevice;
    };

}