#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Graphics/RHI/OpenGL/OpenGLDevice.hpp"

#include <GLFW/glfw3.h>

namespace ramus
{

    Engine::Engine(const EngineConfig& config) : m_config(config)
    {
        InitWindowing();
        InitGraphics();
        InitAssets();
    }

    Engine::~Engine()
    {
        Logger::GetAppLogger()->info("Ramus shutting down...");

        Logger::GetAppLogger()->debug("Destroying window");
        m_window.reset();

        Logger::GetAppLogger()->debug("Terminating GLFW");
        glfwTerminate();

        Logger::GetAppLogger()->info("Ramus shutdown complete.");
    }

    void Engine::Run(std::unique_ptr<Application> app)
    {
        m_application = std::move(app);

        Logger::GetAppLogger()->info("Binding user application Ramus Engine...");
        m_application->BindEngineContext(m_assetManager.get(), m_renderer.get(), m_window.get());

        Logger::GetAppLogger()->info("Loading user application assets...");
        m_application->OnLoad();

        while(m_window->IsOpen()) 
        {
            m_window->HandleEvents();

            double deltaTime = 16.0;
            m_application->OnUpdate(deltaTime);
            m_application->OnRender();

            m_window->Display();
        }
    }

    void Engine::InitWindowing()
    {
        if (!glfwInit()) 
        {
            Logger::GetAppLogger()->critical("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        
        int glfwMajor, glfwMinor, glfwRev;
        glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
        Logger::GetAppLogger()->info("GLFW version {}.{}.{}", glfwMajor, glfwMinor, glfwRev);

         m_window = std::make_unique<Window>(m_config.winSettings);
         assert(m_window);
    }

    void Engine::InitGraphics()
    {
        auto graphicsDevice = std::make_unique<OpenGLDevice>(m_window->GetNativeHandle());
        Logger::GetAppLogger()->info("Graphics Device (OpenGL) initialized.");

        m_renderer = std::make_unique<Renderer>(std::move(graphicsDevice));
    }

    void Engine::InitAssets()
    {
        m_assetManager = std::make_unique<AssetManager>();
        Logger::GetAppLogger()->info("Loading engine assets");
    }
}