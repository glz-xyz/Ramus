#include "Ramus/Core/App.hpp"
#include "Ramus/Core/Log.hpp"
#include "Ramus/Core/ServiceLocator.hpp"
#include "Ramus/Resources/ResourceService.hpp"
#include "Ramus/Graphics/Renderer.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <iostream>
#include <filesystem>

namespace ramus 
{

    App::App(const Config& config) : m_config(config)
    {
        if (!glfwInit()) 
        {
            Log::GetAppLogger()->critical("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        
        int glfwMajor, glfwMinor, glfwRev;
        glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
        Log::GetAppLogger()->info("GLFW version {}.{}.{}", glfwMajor, glfwMinor, glfwRev);
    }

    App::~App() 
    {
        Log::GetAppLogger()->info("Ramus shutting down...");
        Log::GetAppLogger()->debug("Destroying window");
        m_window.reset();
        Log::GetAppLogger()->debug("Terminating GLFW");
        glfwTerminate();
        Log::GetAppLogger()->info("Ramus shutdown complete.");
    }

    bool App::Init()
    {
        try 
        {
            m_window = std::make_unique<AppWindow>(m_config.name, m_config.winWidth, m_config.winHeight);

            m_resourceService = std::make_unique<ResourceService>();
            ServiceLocator::Provide(m_resourceService.get());

            Renderer::Init();

            return true;
        }
        catch (const std::exception& e) 
        {
            Log::GetAppLogger()->critical("Initialization Exception: {}", e.what());
            return false;
        }
    }
    
    void App::Run() 
    {
        while(!m_window->ShouldClose()) 
        {
            m_window->HandleEvents();
            // Grow plants...

            Renderer::SetClearColor({0.384f, 0.506f, 0.255f, 1.0f});
            Renderer::Clear();
            // Draw plants...

            m_window->SwapBuffers();
        }
    }

}