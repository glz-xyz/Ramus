#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLDevice.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShader.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShaderProgram.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLTexture.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <glm/glm.hpp>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define WindowPtr static_cast<GLFWwindow*>(m_nativeWindow)

namespace ramus 
{

    OpenGLDevice::OpenGLDevice(void* nativeWindow) :
        m_nativeWindow(nativeWindow)
    {
        glfwMakeContextCurrent(WindowPtr);

        int glVersion = gladLoadGL(glfwGetProcAddress);
        if (glVersion == 0) 
        {
            Logger::GetRendererLogger()->critical("gladLoadGL failed!");
            throw std::runtime_error("OpenGL context init failed: glad could not load OpenGL functions.");
        }
        else
        {
            m_context = std::make_unique<OpenGLContext>();

            auto* glVersionStr = (const char*)glGetString(GL_VERSION);
            Logger::GetRendererLogger()->info("Graphics context init (OpenGL {})", glVersionStr);

            const char* vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
            const char* renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
            Logger::GetRendererLogger()->info("GPU: {} ({})", renderer, vendor);
        }
    }

    void OpenGLDevice::SetInitialState()
    {
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

    void OpenGLDevice::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        Logger::GetRendererLogger()->debug("VSync {}.", enabled ? "Enabled" : "Disabled");
    }

    GraphicsContext* OpenGLDevice::GetContext()
    {
        return m_context.get();
    }

    void* OpenGLDevice::GetNativeWindow()
    {
        return m_nativeWindow;
    }

    void OpenGLDevice::Present()
    {
        glfwSwapBuffers(WindowPtr);
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

    std::unique_ptr<TextureBase> OpenGLDevice::CreateTexture(const TextureDescriptor& desc, const void* data) 
    {
        return std::make_unique<OpenGLTexture>(desc, data);
    }
}