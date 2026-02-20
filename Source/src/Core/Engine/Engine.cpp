#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/UI/EditorLayer.hpp"
#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLDevice.hpp"

#include <GLFW/glfw3.h>

namespace ramus
{

    Engine::Engine(const EngineConfig& config) : m_config(config)
    {
        InitWindowing();
        InitGraphics();
        InitAssets();
        InitEditorLayer();
    }

    Engine::~Engine()
    {
        Logger::GetEngineLogger()->info("Ramus shutting down...");

        Logger::GetEngineLogger()->debug("Destroying window");
        m_window.reset();

        Logger::GetEngineLogger()->debug("Terminating GLFW");
        glfwTerminate();

        Logger::GetEngineLogger()->info("Ramus shutdown complete.");
    }

    void Engine::Run(std::unique_ptr<Application> app)
    {
        m_application = std::move(app);

        Logger::GetEngineLogger()->info("Binding user application Ramus Engine...");
        m_application->BindEngineContext(m_assetManager.get(), m_renderer.get(), m_window.get());

        Logger::GetEngineLogger()->info("Loading user application assets...");
        m_application->OnLoad();

        while(m_window->IsOpen()) 
        {
            m_window->HandleEvents();

            m_editorLayer->BeginFrame();
            m_renderer->BeginFrame();

            double deltaTime = 16.0;
            m_application->OnUpdate(deltaTime);
            
            m_application->OnRender();
            m_editorLayer->OnImGuiRender();
            
            m_renderer->EndFrame();
            m_editorLayer->EndFrame();

            m_graphicsDevice->Present();
        }
    }

    void Engine::InitWindowing()
    {
        if (!glfwInit()) 
        {
            Logger::GetEngineLogger()->critical("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
        
        int glfwMajor, glfwMinor, glfwRev;
        glfwGetVersion(&glfwMajor, &glfwMinor, &glfwRev);
        Logger::GetEngineLogger()->info("GLFW version {}.{}.{}", glfwMajor, glfwMinor, glfwRev);

         m_window = std::make_unique<Window>(m_config.winSettings);
         assert(m_window);
    }

    void Engine::InitGraphics()
    {
        try 
        {
            m_graphicsDevice = std::make_unique<OpenGLDevice>(m_window->GetNativeHandle());
            assert(m_graphicsDevice != nullptr && "Graphics Device creation failed!");
            Logger::GetEngineLogger()->info("Graphics Device initialized.");
        } 
        catch (const std::exception& e) 
        {
            Logger::GetEngineLogger()->critical("Graphics Device creation failed: {}", e.what());
            throw; 
        }

        m_renderer = std::make_unique<Renderer>(m_graphicsDevice->GetContext());
    }

    void Engine::InitAssets()
    {
        assert(m_graphicsDevice != nullptr && "InitGraphics must be called before InitAssets!");

        m_assetManager = std::make_unique<AssetManager>(m_graphicsDevice.get());
        Logger::GetEngineLogger()->info("Loading engine assets");
    }

    void Engine::InitEditorLayer()
    {
        assert(m_assetManager != nullptr && "InitAssets must be called before InitEditorLayer!");

        m_editorLayer = std::make_unique<EditorLayer>(m_assetManager.get());
        m_editorLayer->OnAttach(m_window->GetNativeHandle());

    }
}