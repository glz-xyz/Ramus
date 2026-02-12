#pragma once

#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Core/Engine/Window.hpp"
#include "Ramus/Graphics/Renderer/Renderer.hpp"

namespace ramus
{
    class Application
    {
    public:
        virtual ~Application() = default;

        void BindEngineContext(AssetManager* assetManager, Renderer* renderer, Window* window)
        {
            m_assetManager = assetManager;
            m_renderer = renderer;
            m_window = window;
        }

        virtual void OnLoad() = 0;
        virtual void OnUpdate(double dt) = 0;
        virtual void OnRender() = 0;
        virtual void OnExit() = 0;

    protected:
        AssetManager* m_assetManager;
        Renderer* m_renderer;
        Window* m_window;
    };

    std::unique_ptr<Application> CreateApplication();
}