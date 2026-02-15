#pragma once

#include "Ramus/Assets/Loaders/AssetLoader.hpp"
#include "Ramus/Assets/Texture.hpp"

namespace ramus
{
    class TextureLoader : public AssetLoader<Texture>
    {
    public: 
        TextureLoader();
        ~TextureLoader() = default;
        
        std::shared_ptr<Texture> Load(const std::string& path, AssetLoadContext& loadContext) override;
    };

}