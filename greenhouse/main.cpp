#include "Ramus/Core/App.hpp"
#include "Ramus/Core/ServiceLocator.hpp"

int main() 
{
    ramus::App::Config config { "Ramus Greenhouse", 1600, 900 };
    ramus::App app(config); 
    if (app.Init())
    {
        auto* resources = ramus::ServiceLocator::GetResources();
        if (resources)
        {
            auto grass = resources->GetModel("assets/models/quixel/uncut_grass/uncut_grass_2k.gltf");
            if (grass)
            {
                app.Run();
                return EXIT_SUCCESS;
            }
        }
    }

    return EXIT_FAILURE;
}