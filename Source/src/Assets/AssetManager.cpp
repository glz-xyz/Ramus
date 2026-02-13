#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Loaders/MaterialLoader.hpp"
#include "Ramus/Assets/Loaders/ModelLoader.hpp"
#include "Ramus/Assets/Loaders/TextureLoader.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

namespace ramus
{

    AssetManager::AssetManager(GraphicsDevice* device) :
        m_graphicsDevice(device)
    {
        assert(m_graphicsDevice != nullptr && "Cannot initialize AssetManager without a Graphics Device!");

        m_materialLoader = std::make_unique<MaterialLoader>();
        m_modelLoader = std::make_unique<ModelLoader>(device);
        m_textureLoader = std::make_unique<TextureLoader>();
    }

    std::shared_ptr<Material> AssetManager::GetMaterial(const std::string& path) 
    {
        return GetAsset(path, m_materialCache, *m_materialLoader);
    }

    std::shared_ptr<Model> AssetManager::GetModel(const std::string& path) 
    {
        return GetAsset(path, m_modelCache, *m_modelLoader);
    }

    std::shared_ptr<Texture> AssetManager::GetTexture(const std::string& path) 
    {
        return GetAsset(path, m_textureCache, *m_textureLoader);
    }

    template <typename T>
    std::shared_ptr<T> AssetManager::GetAsset(const std::string& path, AssetCache<T>& cache, AssetLoader<T>& loader) 
    {
        auto it = cache.find(path);
        if (it != cache.end()) return it->second;

        auto resource = loader.Load(path);
        if (resource) cache[path] = resource;
        
        return resource;
    }

}