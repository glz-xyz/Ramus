#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Core/Engine/Application.hpp"

int main(int argc, char** argv)
{
    // 1. Set up infra
    // 2. Init Device & AssetManager

    ramus::EngineConfig engineConfig;
    engineConfig.winSettings = { "Greenhouse App", 1600, 900 };

    ramus::Engine engine(engineConfig);

    std::unique_ptr<ramus::Application> app = ramus::CreateApplication();
    engine.Run(std::move(app));

    return EXIT_SUCCESS;
}