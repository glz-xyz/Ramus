#include "Ramus/Core/Engine/Application.hpp"
#include "Ramus/Core/Engine/Engine.hpp"
#include "Ramus/Assets/AssetManager.hpp"

#include <glm/gtc/matrix_transform.hpp>

class GreenhouseApp : public ramus::Application
{
public:
    void OnLoad() override
    {
        m_grassModel = m_assetManager->LoadModel(GH_ASSET_PATH + "Models/quixel/uncut_grass/uncut_grass_2k.gltf");
        m_grassMaterial = m_assetManager->LoadMaterial(GH_ASSET_PATH + "Materials/UncutGrass.mat");

        m_grassTransform = glm::mat4(1.0f); 
        m_grassTransform = glm::translate(m_grassTransform, glm::vec3(0.0f, -1.0f, -5.0f));
        m_grassTransform = glm::rotate(m_grassTransform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        m_grassTransform = glm::scale(m_grassTransform, glm::vec3(0.1f));
    }

    void OnUpdate(double dt) override
    {

    }

    void OnRender() override
    {
        m_renderer->BeginFrame();

        m_renderer->Render(*m_grassModel, *m_grassMaterial, m_grassTransform);

        m_renderer->EndFrame();
    }

    void OnExit() override
    {
        
    }

private:
    const std::string GH_ASSET_PATH = "Samples/Greenhouse/Assets/";

    std::shared_ptr<ramus::Model> m_grassModel;
    std::shared_ptr<ramus::Material> m_grassMaterial;
    glm::mat4 m_grassTransform;
};

namespace ramus
{
    std::unique_ptr<Application> CreateApplication()
    {
        return std::make_unique<GreenhouseApp>();
    }
}