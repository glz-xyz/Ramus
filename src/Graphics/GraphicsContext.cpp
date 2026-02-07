#include "Ramus/Graphics/GraphicsContext.hpp"
#include "Ramus/Graphics/GraphicsInternal.hpp"
#include "Ramus/Core/Log.hpp"

#include <GLFW/glfw3.h>

namespace ramus 
{

    GraphicsContext::GraphicsContext(struct GLFWwindow* nativeHandle)
        : m_nativeWindow(nativeHandle)
    {
        if (!m_nativeWindow)
        {
            Log::GetRendererLogger()->critical("Graphics context received invalid GLFW window handle!");
            throw std::runtime_error("Graphics context init failed: Invalid GLFW window handle.");
        }

        MakeCurrent();

        int glVersion = gladLoadGL(glfwGetProcAddress);
        if (glVersion == 0) 
        {
            Log::GetRendererLogger()->critical("gladLoadGL failed!");
            throw std::runtime_error("Graphics context init failed: glad could not load OpenGL functions.");
        }

        auto* glVersionStr = (const char*)glGetString(GL_VERSION);
        Log::GetRendererLogger()->info("Graphics context init (OpenGL {})", glVersionStr);
    }

    void GraphicsContext::MakeCurrent()
    {
        glfwMakeContextCurrent(m_nativeWindow);
    }

    void GraphicsContext::SwapBuffers()
    {
        glfwSwapBuffers(m_nativeWindow);
    }

    void GraphicsContext::SetVSync(const bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        Log::GetRendererLogger()->info("VSync is now {}", enabled ? "Enabled" : "Disabled");
    }
}