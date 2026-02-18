#include "Ramus/Assets/Loaders/TextureLoader.hpp"
#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Texture.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/Device/Base/TextureBase.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

#define STB_IMAGE_IMPLEMENTATION
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
        int x, y, channels;
        uint8_t* pixels = stbi_load(path.c_str(), &x, &y, &channels, 4);
        if (pixels != nullptr)
        {
            Logger::GetAssetLogger()->info("Image data loaded: {}x{} {}", x, y, channels == 3 ? "RGB" : "RGBA");

            TextureDescriptor desc;
            desc.width = x;
            desc.height = y;
            desc.format = channels == 3 ? TextureFormat::RGBA8 : TextureFormat::RGB8;

            auto gpuTexture = loadContext.device->CreateTexture(desc, pixels);
            auto texture = std::make_shared<Texture>(desc, std::move(gpuTexture));

            stbi_image_free(pixels);

            return texture;
        }
        else
        {
            Logger::GetAssetLogger()->error("Texture loading failed: {}", path);
        }

        return nullptr;
    }

}