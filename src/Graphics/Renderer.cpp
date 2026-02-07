#include "Ramus/Graphics/Renderer.hpp"
#include "Ramus/Core/Log.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace ramus
{
    Renderer::Renderer()
    {
        m_graphicsDevice = std::make_unique<GraphicsDevice>();
    }

    void Renderer::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }

    void Renderer::BeginFrame()
    {
        m_graphicsDevice->SetClearColor({0.384f, 0.506f, 0.255f, 1.0f});
        m_graphicsDevice->Clear();
    }

    void Renderer::EndFrame()
    {
        // [TODO] ImGui render data, post-processing, etc.
    }
}