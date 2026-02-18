#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Assets/Model.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace ramus
{
    Renderer::Renderer(GraphicsContext* graphicsContext) : 
        m_graphicsContext(graphicsContext)
    {
        assert(m_graphicsContext != nullptr && "Cannot initialize Renderer without a Graphics Context!");
    }

    void Renderer::Init()
    {
        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LESS);

        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
    }

    void Renderer::BeginFrame()
    {
        m_graphicsContext->SetClearColor(0.384f, 0.506f, 0.255f, 1.0f);
        m_graphicsContext->Clear();
    }

    void Renderer::EndFrame()
    {
        
    }

    void Renderer::Render(const Model& model, const Material& material, const glm::mat4& transform)
    {
        material.Bind(m_graphicsContext);

        const auto& meshLinks = model.GetMeshLinks();
        for (const auto& link : meshLinks) 
        {
            m_graphicsContext->BindGeometry(link.resource.get());

            uint32_t count = link.mesh->indices.size();
            m_graphicsContext->DrawIndexed(count);

            // [TODO] Modernize and/or pass resource so we can more explicitly know which (VAO) we're unbinding.
            m_graphicsContext->UnbindGeometry();
        }
    }

}