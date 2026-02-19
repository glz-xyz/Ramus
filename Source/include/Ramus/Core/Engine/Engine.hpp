#pragma once

#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
#include "Ramus/UI/ImGuiLayer.hpp"

namespace ramus
{
    struct EngineConfig
    {
        WindowSettings winSettings;
        //struct GraphicsSettings
        //{
        //    enum class API { None, OpenGL } api = API::OpenGL;
        //} graphicsSettings;
    };

    class Engine
    {
    public:
        Engine(const EngineConfig& config);
        ~Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        
        void Run(std::unique_ptr<Application> app);

    private:
        void InitWindowing();
        void InitGraphics();
        void InitImGuiLayer();
        void InitAssets();

        std::unique_ptr<Window> m_window;
        std::unique_ptr<GraphicsDevice> m_graphicsDevice;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<AssetManager> m_assetManager;
        std::unique_ptr<Application> m_application;
        std::unique_ptr<ImGuiLayer> m_imguiLayer;

        EngineConfig m_config;
    };

}