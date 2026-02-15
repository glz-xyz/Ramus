#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Loaders/MaterialLoader.hpp"
#include "Ramus/Assets/Loaders/ModelLoader.hpp"
#include "Ramus/Assets/Loaders/TextureLoader.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
#include "Ramus/Core/Services/Logger.hpp"

namespace ramus
{

    AssetManager::AssetManager(GraphicsDevice* device) :
        m_graphicsDevice(device)
    {
        assert(m_graphicsDevice != nullptr && "Cannot initialize AssetManager without a Graphics Device!");
        m_loadContext.device = m_graphicsDevice;
        m_loadContext.manager = this;

        m_materialLoader = std::make_unique<MaterialLoader>();
        m_modelLoader = std::make_unique<ModelLoader>();
        m_textureLoader = std::make_unique<TextureLoader>();
    }

    AssetManager::~AssetManager() = default;

    std::shared_ptr<Material> AssetManager::LoadMaterial(const std::string& path) 
    {
        return LoadInternal<Material>(path, *m_materialLoader, m_materialCache);
    }

    std::shared_ptr<Model> AssetManager::LoadModel(const std::string& path) 
    {
        return LoadInternal<Model>(path, *m_modelLoader, m_modelCache);
    }

    std::shared_ptr<Texture> AssetManager::LoadTexture(const std::string& path) 
    {
        return LoadInternal<Texture>(path, *m_textureLoader, m_textureCache);
    }
}