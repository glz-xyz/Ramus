#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Model.hpp"

#include <memory>

class GreenhouseApp : public ramus::Application
{
public:
    void OnLoad() override
    {
        grass = m_assetManager->GetModel("assets/models/quixel/uncut_grass/uncut_grass_2k.gltf");
    }

    void OnUpdate(double dt) override
    {

    }

    void OnRender() override
    {
        m_renderer->BeginFrame();

        m_renderer->Render(*grass);

        m_renderer->EndFrame();
    }

    void OnExit() override
    {
        
    }

private:
    std::shared_ptr<ramus::Model> grass;
};

namespace ramus
{
    std::unique_ptr<Application> CreateApplication()
    {
        return std::make_unique<GreenhouseApp>();
    }
}