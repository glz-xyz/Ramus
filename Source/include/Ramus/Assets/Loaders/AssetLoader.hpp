#pragma once

#include <memory>
#include <string>
#include <filesystem>

namespace ramus
{
    struct AssetLoadContext;

    template <typename T>
    class AssetLoader
    {
    public:
        virtual ~AssetLoader() = default;

        bool IsValidAssetPath(const std::string& path) const 
        {
            std::string ext = std::filesystem::path(path).extension().string();
            for (const auto& supported : m_supportedExtensions) 
                if (ext == supported)
                    return true;
            return false;
        }

        virtual std::shared_ptr<T> Load(const std::string& path, AssetLoadContext& loadContext) = 0;
      
    protected:
        std::vector<std::string> m_supportedExtensions;
    };

}