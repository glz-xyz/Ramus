#pragma once

#include "Ramus/Assets/AssetLoadContext.hpp"

#include "Ramus/Assets/Material.hpp"
#include "Ramus/Assets/Model.hpp"
#include "Ramus/Assets/Texture.hpp"

#include "Ramus/Utils/FileUtils.hpp"

//#include "Ramus/Assets/Loaders/MaterialLoader.hpp"
//#include "Ramus/Assets/Loaders/ModelLoader.hpp"
//#include "Ramus/Assets/Loaders/TextureLoader.hpp"

#include <string>
#include <memory>
#include <unordered_map>

namespace ramus
{
    class MaterialLoader;
    class ModelLoader;
    class TextureLoader;

    class AssetManager final
    {
    public:
        template <typename TAsset> 
        using AssetCache = std::unordered_map<std::string, std::shared_ptr<TAsset>>;

        explicit AssetManager(GraphicsDevice* device);
        ~AssetManager();

        std::shared_ptr<Material> LoadMaterial(const std::string& materialPath);
        std::shared_ptr<Model> LoadModel(const std::string& modelPath);
        std::shared_ptr<Texture> LoadTexture(const std::string& texturePath);

    private:
        GraphicsDevice* m_graphicsDevice;

        std::unique_ptr<MaterialLoader> m_materialLoader;
        std::unique_ptr<ModelLoader> m_modelLoader;
        std::unique_ptr<TextureLoader> m_textureLoader;

        AssetCache<Material> m_materialCache;
        AssetCache<Model> m_modelCache;
        AssetCache<Texture> m_textureCache;

        AssetLoadContext m_loadContext;
        AssetLoadContext& GetLoadContext() { return m_loadContext; }

        template<typename TAsset, typename TLoader>
        std::shared_ptr<TAsset> LoadInternal(const std::string& path, TLoader& loader, AssetCache<TAsset>& cache)
        {
            const char* assetType = TAsset::StaticTypeName();

            std::string cleanedPath = ramus::GetExecutableDirectory().string() + "/" + ramus::ResolvePath(path);
            Logger::GetAssetLogger()->info("Cleaned path: {}", cleanedPath);

            if (!loader.IsValidAssetPath(cleanedPath)) 
            {
                std::string ext = std::filesystem::path(cleanedPath).extension().string();
                Logger::GetAssetLogger()->error("Unsupported extension '{}' for {} asset: {}", ext, assetType, path);
                return nullptr;
            }

            auto it = cache.find(cleanedPath);
            if (it != cache.end()) 
            {
                Logger::GetAssetLogger()->trace("[{}] Cache Hit: {}", assetType, cleanedPath);
                return it->second;
            }

            auto asset = loader.Load(cleanedPath, GetLoadContext());
            if (asset) 
            {
                Logger::GetAssetLogger()->info("[{}] Loaded successfully: {}", assetType, cleanedPath);
                cache[cleanedPath] = asset;
            } 
            else 
            {
                Logger::GetAssetLogger()->error("[{}] Failed to load: {}", assetType, cleanedPath);
            }

            return asset;
        }
    };

}