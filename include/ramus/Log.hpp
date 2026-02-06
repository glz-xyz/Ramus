#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>

namespace ramus
{

    class Log
    {
    public:
        inline static std::shared_ptr<spdlog::logger>& GetAppLogger() 
        { 
            if (!s_initialized) Init();
            return s_appLogger; 
        }
        inline static std::shared_ptr<spdlog::logger>& GetWindowLogger() 
        { 
            if (!s_initialized) Init();
            return s_windowLogger; 
        }
        inline static std::shared_ptr<spdlog::logger>& GetRendererLogger() 
        { 
            if (!s_initialized) Init();
            return s_rendererLogger; 
        }

    private:
        static void Init();
        
        static std::shared_ptr<spdlog::logger> s_appLogger;
        static std::shared_ptr<spdlog::logger> s_windowLogger;
        static std::shared_ptr<spdlog::logger> s_rendererLogger;
        static bool s_initialized;
    };

}