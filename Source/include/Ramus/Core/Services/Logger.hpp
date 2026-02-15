#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <memory>

namespace ramus
{

    class Logger
    {
    public:
        inline static std::shared_ptr<spdlog::logger>& GetAppLogger() 
        { 
            if (!s_initialized) Init();
            return s_appLogger; 
        }
        inline static std::shared_ptr<spdlog::logger>& GetAssetLogger() 
        { 
            if (!s_initialized) Init();
            return s_assetLogger; 
        }
        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() 
        { 
            if (!s_initialized) Init();
            return s_engineLogger; 
        }
        inline static std::shared_ptr<spdlog::logger>& GetDeviceLogger() 
        { 
            if (!s_initialized) Init();
            return s_deviceLogger; 
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
        static std::shared_ptr<spdlog::logger> s_assetLogger;
        static std::shared_ptr<spdlog::logger> s_engineLogger;
        static std::shared_ptr<spdlog::logger> s_rendererLogger;
        static std::shared_ptr<spdlog::logger> s_windowLogger;
        static std::shared_ptr<spdlog::logger> s_deviceLogger;
        static bool s_initialized;
    };

}