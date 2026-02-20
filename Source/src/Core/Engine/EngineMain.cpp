#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Core/Engine/Application.hpp"

int main(int argc, char** argv)
{
    ramus::EngineConfig engineConfig;
    engineConfig.winSettings = { "Greenhouse App", 1600, 900 };

    ramus::Engine engine(engineConfig);

    try 
    {
        std::unique_ptr<ramus::Application> app = ramus::CreateApplication();
        engine.Run(std::move(app));
    }
    catch (const std::exception& e) 
    {
        printf("FATAL ENGINE EXCEPTION: %s\n\n Press any key...", e.what());
        getchar(); 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}