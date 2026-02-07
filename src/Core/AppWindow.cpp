#include "ramus/Core/AppWindow.hpp"
#include "ramus/Core/Log.hpp"

#include <GLFW/glfw3.h>

#include <stdexcept>

namespace ramus
{

    AppWindow::AppWindow(const std::string& title, int width, int height)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_nativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (m_nativeWindow)
        {
            Log::GetWindowLogger()->info("GLFW Window created: '{}' ({}x{})", title, width, height);
            glfwMakeContextCurrent(m_nativeWindow);
            glfwSwapInterval(1);
        }
        else
        {
            throw std::runtime_error("[RAMUS-WINDOW] GLFW Window creation failed!");
        }
    }

    AppWindow::~AppWindow()
    {
        glfwDestroyWindow(m_nativeWindow);
    }

    void AppWindow::HandleEvents()
    {
        glfwPollEvents();
    }

    bool AppWindow::ShouldClose() const
    {
        return glfwWindowShouldClose(m_nativeWindow);
    }

    void AppWindow::SwapBuffers()
    {
        glfwSwapBuffers(m_nativeWindow);
    }

}