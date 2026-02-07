#include "ramus/Core/Log.hpp"

namespace ramus
{

    std::shared_ptr<spdlog::logger> Log::s_appLogger;
    std::shared_ptr<spdlog::logger> Log::s_windowLogger;
    std::shared_ptr<spdlog::logger> Log::s_rendererLogger;
    bool Log::s_initialized = false;

    void Log::Init() 
    {
        // [Timestamp] [LoggerName] [Level]: Message
        spdlog::set_pattern("%^[%T] [%n] %l: %v%$");

        s_appLogger = spdlog::stdout_color_mt("APP");
        s_windowLogger = spdlog::stdout_color_mt("WINDOW");
        s_rendererLogger = spdlog::stdout_color_mt("RENDERER");

        s_appLogger->set_level(spdlog::level::trace);

        s_initialized = true;
    }

}