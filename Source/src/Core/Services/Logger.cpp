#include "Ramus/Core/Services/Logger.hpp"

namespace ramus
{

    std::shared_ptr<spdlog::logger> Logger::s_appLogger;
    std::shared_ptr<spdlog::logger> Logger::s_windowLogger;
    std::shared_ptr<spdlog::logger> Logger::s_engineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_assetLogger;
    std::shared_ptr<spdlog::logger> Logger::s_rendererLogger;
    std::shared_ptr<spdlog::logger> Logger::s_deviceLogger;
    bool Logger::s_initialized = false;

    void Logger::Init() 
    {
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%T] [%n] %l: %v%$");
        // [Timestamp] [LoggerName] [Level]: Message

        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Ramus.log", true);
        fileSink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%#] %v");
        // [Date & Time (ms)] [Level] [File:Line] [Message]

        s_appLogger = spdlog::stdout_color_mt("APP");
        s_windowLogger = spdlog::stdout_color_mt("WINDOW");
        s_rendererLogger = spdlog::stdout_color_mt("RENDERER");
        s_engineLogger = spdlog::stdout_color_mt("ENGINE");
        s_assetLogger = spdlog::stdout_color_mt("ASSETS");
        s_deviceLogger = spdlog::stdout_color_mt("DEVICE");

        s_appLogger->set_level(spdlog::level::trace);
        s_appLogger->flush_on(spdlog::level::trace);

        s_initialized = true;
    }

}