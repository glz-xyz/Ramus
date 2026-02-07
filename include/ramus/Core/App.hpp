#pragma once

#include "ramus/Core/AppWindow.hpp"

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
        std::unique_ptr<AppWindow> m_window;
    };

}