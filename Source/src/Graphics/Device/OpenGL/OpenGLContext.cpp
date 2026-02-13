#include "Ramus/Graphics/Device/OpenGL/OpenGLContext.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define WindowPtr static_cast<GLFWwindow*>(m_nativeWindow)

namespace ramus
{

    OpenGLContext::OpenGLContext(void* nativeWindow) : m_nativeWindow(nativeWindow)
    {
        Logger::GetRendererLogger()->info("OpenGL context acquired window.");
    }

    OpenGLContext::~OpenGLContext()
    {
        Logger::GetRendererLogger()->info("OpenGL context destroyed.");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(WindowPtr);

        int glVersion = gladLoadGL(glfwGetProcAddress);
        if (glVersion == 0) 
        {
            Logger::GetRendererLogger()->critical("gladLoadGL failed!");
            throw std::runtime_error("OpenGL context init failed: glad could not load OpenGL functions.");
        }

        auto* glVersionStr = (const char*)glGetString(GL_VERSION);
        Logger::GetRendererLogger()->info("Graphics context init (OpenGL {})", glVersionStr);
    }


    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(WindowPtr);
    }

    void OpenGLContext::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        Logger::GetRendererLogger()->debug("VSync {}.", enabled ? "Enabled" : "Disabled");
    }
}