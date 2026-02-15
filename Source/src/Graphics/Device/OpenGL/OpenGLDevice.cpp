#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLDevice.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShader.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShaderProgram.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <glm/glm.hpp>
#include <glad/gl.h>

namespace ramus 
{

    OpenGLDevice::OpenGLDevice(void* nativeWindow)
    {
        m_context = std::make_unique<OpenGLContext>(nativeWindow);
        m_context->Init();

        Init();

        const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
        const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
        Logger::GetRendererLogger()->info("GPU: {} ({})", renderer, vendor);
    }

    void OpenGLDevice::Init()
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        // [TODO]
        // Enable MSAA if requested in the config
        //if (settings.msaaSamples > 1) 
        //{
        //    glEnable(GL_MULTISAMPLE);
        //}

        // Set VSync through the context
        //m_context->SetVSync(settings.vSyncEnabled);

        // Enable modern OpenGL 4.6 features by default
        // ...
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

    std::unique_ptr<ShaderProgramBase> OpenGLDevice::CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
    {
        auto vs = std::make_shared<OpenGLShader>(ShaderStage::Vertex, vertexShaderSrc);
        auto fs = std::make_shared<OpenGLShader>(ShaderStage::Fragment, fragmentShaderSrc);
        return std::make_unique<OpenGLShaderProgram>(vs, fs);
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
