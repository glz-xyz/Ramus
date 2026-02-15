#include "Ramus/Assets/Loaders/TextureLoader.hpp"
#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Texture.hpp"
#include "Ramus/Core/Services/Logger.hpp"

#include <stb_image.h>

namespace ramus
{

    TextureLoader::TextureLoader()
    {
        m_supportedExtensions = 
        { 
            ".png",
            ".jpg",
            ".jpeg",
            ".tga",
            ".bmp"
        };
    }

    std::shared_ptr<Texture> TextureLoader::Load(const std::string& path, AssetLoadContext& loadContext)
    {
        Logger::GetAssetLogger()->error("Texture loading not implemented yet!");
        return nullptr;
    }

}