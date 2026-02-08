#pragma once

#include "Ramus/Resources/IResourceService.hpp"
#include "Ramus/Resources/ResourceLoader.hpp"

#include <unordered_map>

namespace ramus 
{
    template<typename T>
    using ResourceCache = std::unordered_map<std::string, std::shared_ptr<T>>;
    
    class Model;
    class Texture;
    class Shader;

    class ResourceService : public IResourceService 
    {
    public:
        ResourceService();
        ~ResourceService() override = default;

        std::shared_ptr<Model> GetModel(const std::string& modelPath) override ;
        std::shared_ptr<Texture> GetTexture(const std::string& texturePath) override;
        std::shared_ptr<Shader> GetShader(const std::string& shaderPath) override;

    private:
        template<typename T>
        std::shared_ptr<T> GetResource(const std::string& path, ResourceCache<T>& cache, ResourceLoader<T>& loader);

        std::unique_ptr<ResourceLoader<Model>> m_modelLoader;
        std::unique_ptr<ResourceLoader<Texture>> m_textureLoader;
        std::unique_ptr<ResourceLoader<Shader>> m_shaderLoader;

        ResourceCache<Model> m_modelCache;
        ResourceCache<Texture> m_textureCache;
        ResourceCache<Shader> m_shaderCache;
    };

}