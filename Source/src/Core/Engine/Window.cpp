#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <GLFW/glfw3.h>

#define WindowPtr static_cast<GLFWwindow*>(m_nativeHandle)

namespace ramus
{

    Window::Window(const WindowSettings& settings) :
        m_settings(settings)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_nativeHandle = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.title.c_str(), nullptr, nullptr);
        if (m_nativeHandle)
        {
            Logger::GetWindowLogger()->info("GLFW Window created: '{}' ({}x{})", m_settings.title, m_settings.width, m_settings.height);
        }
        else
        {
            throw std::runtime_error("GLFW Window creation failed!");
        }
    }

    Window::~Window()
    {
        glfwDestroyWindow(WindowPtr);
    }

    void Window::HandleEvents()
    {
        glfwPollEvents();
    }

    bool Window::IsOpen() const
    {
        return !glfwWindowShouldClose(WindowPtr);
    }

    float Window::GetAspectRatio() const
    {
        if (m_settings.height == 0) return 1.0f;
        return static_cast<float>(m_settings.width) / static_cast<float>(m_settings.height);
    }
}