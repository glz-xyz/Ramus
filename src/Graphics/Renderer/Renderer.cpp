#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/RHI/OpenGL/OpenGLDevice.hpp"

#include <glad/gl.h>
#include <spdlog/spdlog.h>

namespace ramus
{
    Renderer::Renderer(std::unique_ptr<GraphicsDevice> graphicsDevice) : 
        m_graphicsDevice(std::move(graphicsDevice))
    {
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