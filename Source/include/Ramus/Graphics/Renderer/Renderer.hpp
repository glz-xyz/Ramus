#pragma once

#include "Ramus/Graphics/Device/GraphicsContext.hpp"
#include "Ramus/Assets/Material.hpp"
#include "Ramus/Assets/Model.hpp"

namespace ramus
{

    class Renderer
    {
    public:
        Renderer(GraphicsContext* graphicsContext);

        void Init();

        void BeginFrame();
        void Render(const Model& model, const Material& material, const glm::mat4& transform);
        void EndFrame();

    private:
        GraphicsContext* m_graphicsContext;
    };

}