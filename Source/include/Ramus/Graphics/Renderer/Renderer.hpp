#pragma once

#include "Ramus/Assets/Material.hpp"
#include "Ramus/Assets/Model.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace ramus
{

    class Renderer
    {
    public:
        Renderer(GraphicsDevice*graphicsDevice);

        void Init();

        void BeginFrame();
        void Render(const Model& model);
        void EndFrame();

    private:
        GraphicsDevice* m_graphicsDevice;
    };

}