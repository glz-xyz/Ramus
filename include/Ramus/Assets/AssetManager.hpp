#pragma once

#include "Ramus/Assets/Loaders/MaterialLoader.hpp"
#include "Ramus/Assets/Loaders/ModelLoader.hpp"
#include "Ramus/Assets/Loaders/TextureLoader.hpp"

#include <unordered_map>
#include <memory>

/*
#include "Ramus/Assets/IResourceService.hpp"
#include "Ramus/Assets/Loaders/AssetLoader.hpp"

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
        std::shared_ptr<T> GetResource(const std::string& path, ResourceCache<T>& cache, AssetLoader<T>& loader);

        std::unique_ptr<AssetLoader<Model>> m_modelLoader;
        std::unique_ptr<AssetLoader<Texture>> m_textureLoader;
        std::unique_ptr<AssetLoader<Shader>> m_shaderLoader;

        ResourceCache<Model> m_modelCache;
        ResourceCache<Texture> m_textureCache;
        ResourceCache<Shader> m_shaderCache;
    };

}
*/

namespace ramus
{
    template<typename T>
    using AssetCache = std::unordered_map<std::string, std::shared_ptr<T>>;

    class Material;
    class Model;
    class Texture;
    class AssetManager
    {
    public:
        AssetManager();

        std::shared_ptr<Material> GetMaterial(const std::string& shaderPath);
        std::shared_ptr<Model> GetModel(const std::string& modelPath);
        std::shared_ptr<Texture> GetTexture(const std::string& texturePath);

    private:
        std::unique_ptr<MaterialLoader> m_materialLoader;
        std::unique_ptr<ModelLoader> m_modelLoader;
        std::unique_ptr<TextureLoader> m_textureLoader;

        AssetCache<Material> m_materialCache;
        AssetCache<Model> m_modelCache;
        AssetCache<Texture> m_textureCache;

        template<typename T>
        std::shared_ptr<T> GetAsset(const std::string& path, AssetCache<T>& cache, AssetLoader<T>& loader);
    };
}