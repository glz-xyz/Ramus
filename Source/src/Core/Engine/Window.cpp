#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <GLFW/glfw3.h>

#define WindowPtr static_cast<GLFWwindow*>(m_nativeHandle)

namespace ramus
{
    inline GLFWwindow* WindowCast(void* nativeHandle) { static_cast<GLFWwindow*>(nativeHandle); }

    Window::Window(const WindowSettings& settings)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_nativeHandle = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
        if (m_nativeHandle)
        {
            Logger::GetWindowLogger()->info("GLFW Window created: '{}' ({}x{})", settings.title, settings.width, settings.height);
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

    void Window::Display()
    {
        glfwSwapBuffers(WindowPtr);
    }

    void* Window::GetNativeHandle()
    {
        return m_nativeHandle;
    }
}