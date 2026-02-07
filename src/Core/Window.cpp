#include "Ramus/Core/Window.hpp"
#include "Ramus/Core/Log.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace ramus
{

    Window::Window(const std::string& title, int width, int height)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_nativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (m_nativeWindow)
        {
            Log::GetWindowLogger()->info("GLFW Window created: '{}' ({}x{})", title, width, height);
            
            m_graphicsContext = std::make_unique<GraphicsContext>(m_nativeWindow);
        }
        else
        {
            throw std::runtime_error("[RAMUS-WINDOW] GLFW Window creation failed!");
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_nativeWindow);
    }

    void Window::HandleEvents()
    {
        glfwPollEvents();
    }

    bool Window::IsOpen() const
    {
        return !glfwWindowShouldClose(m_nativeWindow);
    }

    void Window::Display()
    {
        m_graphicsContext->SwapBuffers();
    }

}