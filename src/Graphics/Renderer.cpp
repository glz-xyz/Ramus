#include "Ramus/Graphics/Renderer.hpp"
#include "Ramus/Core/Log.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace ramus
{

    void Renderer::Init()
    {
        if (!gladLoadGL(glfwGetProcAddress)) 
        {
            Log::GetRendererLogger()->critical("Failed to initialize GLAD!");
            throw std::runtime_error("Failed to initialize GLAD");
        }

        Log::GetRendererLogger()->info("GLAD initialized (OpenGL {})", (const char*)glGetString(GL_VERSION));
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}