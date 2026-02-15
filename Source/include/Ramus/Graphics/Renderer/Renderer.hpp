#pragma once

#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
#include "Ramus/Assets/Material.hpp"
#include "Ramus/Assets/Model.hpp"

#include <glm/glm.hpp>

namespace ramus
{

    class Renderer
    {
    public:
        Renderer(GraphicsDevice*graphicsDevice);

        void Init();

        void BeginFrame();
        void Render(const Model& model, const Material& material, const glm::mat4& transform);
        void EndFrame();

    private:
        GraphicsDevice* m_graphicsDevice;
    };

}