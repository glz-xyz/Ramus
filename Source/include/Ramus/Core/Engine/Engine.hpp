#pragma once

#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Graphics/Renderer/Renderer.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

namespace ramus
{
    class EditorLayer;

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
        static std::filesystem::path GetAssetsPath() {
            return std::filesystem::path(RAMUS_ASSETS_PATH);
        }

        static std::string GetFullAssetPath(const std::string& relativePath) {
            return (GetAssetsPath() / relativePath).string();
        }

    public:
        Engine(const EngineConfig& config);
        ~Engine();

        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;
        
        void Run(std::unique_ptr<Application> app);

    private:
        void InitWindowing();
        void InitGraphics();
        void InitAssets();
        void InitEditorLayer();

        std::unique_ptr<Window> m_window;
        std::unique_ptr<GraphicsDevice> m_graphicsDevice;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<AssetManager> m_assetManager;
        std::unique_ptr<Application> m_application;
        std::unique_ptr<EditorLayer> m_editorLayer;

        EngineConfig m_config;
    };

}