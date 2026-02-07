#pragma once

#include "Ramus/Core/Window.hpp"
#include "Ramus/Graphics/Renderer.hpp"
#include "Ramus/Resources/IResourceService.hpp"

#include <string>
#include <memory>

namespace ramus
{

    class App
    {   
    public: 
        struct Config
        {
            std::string name = "Ramus App";
            int winWidth = 1600;
            int winHeight = 900;
        };

        App(const Config& config);
        ~App();

        bool Init();
        void Run();

    private:
        Config m_config;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<IResourceService> m_resourceService;
    };

}