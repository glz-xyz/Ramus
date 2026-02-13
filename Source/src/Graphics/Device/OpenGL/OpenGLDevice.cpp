#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLDevice.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <glm/glm.hpp>
#include <glad/gl.h>

namespace ramus 
{

    OpenGLDevice::OpenGLDevice(void* nativeWindow)
    {
        m_context = std::make_unique<OpenGLContext>(nativeWindow);
        m_context->Init();

        // 3. Set Initial State (Using the settings from EngineConfig)
        //ConfigureInitialState(settings);

        Init();

        // 4. Log hardware info (Great for debugging those Coursera assets)
        const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        Logger::GetRendererLogger()->info("GPU: {} ({})", renderer, vendor);
    }

    void OpenGLDevice::Init()
    {
        // Enable modern OpenGL 4.6 features by default
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // Enable MSAA if requested in the config
        //if (settings.msaaSamples > 1) 
        //{
        //    glEnable(GL_MULTISAMPLE);
        //}

        // Set VSync through the context
        //m_context->SetVSync(settings.vSyncEnabled);
    }

    void OpenGLDevice::SetClearColor(const glm::vec4& clearColor)
    {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    }

    void OpenGLDevice::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLDevice::Present()
    {
        m_context->SwapBuffers();
    }

    std::unique_ptr<DeviceResource> OpenGLDevice::CreateResource(const Mesh& mesh)
    {
        return std::make_unique<OpenGLMesh>(mesh);
    }

    void OpenGLDevice::BindGeometry(DeviceResource* resource)
    {
        if (resource)
        {
            auto* glMesh = static_cast<OpenGLMesh*>(resource);
            glMesh->Bind();
        }
        else
        {
            assert(false && "Attempting to bind a null geometry resource!");
            return;
        }
    }

    void OpenGLDevice::UnbindGeometry()
    {
        glBindVertexArray(0);
    }

    void OpenGLDevice::DrawIndexed(uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
}