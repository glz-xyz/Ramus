#include "Ramus/Resources/ResourceService.hpp"
#include "Ramus/Resources/ModelLoader.hpp"
#include "Ramus/Resources/TextureLoader.hpp"
#include "Ramus/Resources/ShaderLoader.hpp"

namespace ramus
{

    ResourceService::ResourceService()
    {
        m_modelLoader = std::make_unique<ModelLoader>();
        m_textureLoader = std::make_unique<TextureLoader>();
        m_shaderLoader = std::make_unique<ShaderLoader>();
    }

    template <typename T>
    std::shared_ptr<T> ResourceService::GetResource(const std::string& path, ResourceCache<T>& cache, ResourceLoader<T>& loader) 
    {
        auto it = cache.find(path);
        if (it != cache.end()) return it->second;

        auto resource = loader.Load(path);
        if (resource) cache[path] = resource;
        
        return resource;
    }

    std::shared_ptr<Model> ResourceService::GetModel(const std::string& path) 
    {
        return GetResource(path, m_modelCache, *m_modelLoader);
    }

    std::shared_ptr<Shader> ResourceService::GetShader(const std::string& path) 
    {
        return GetResource(path, m_shaderCache, *m_shaderLoader);
    }

    std::shared_ptr<Texture> ResourceService::GetTexture(const std::string& path) 
    {
        return GetResource(path, m_textureCache, *m_textureLoader);
    }

}