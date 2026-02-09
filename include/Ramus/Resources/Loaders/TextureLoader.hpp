#pragma once

#include "Ramus/Resources/Loaders/IResourceLoader.hpp"
#include "Ramus/Graphics/Texture.hpp"

namespace ramus
{

    class TextureLoader : public IResourceLoader<Texture>
    {
    public: 
        TextureLoader() = default;
        ~TextureLoader() = default;
        
        std::shared_ptr<Texture> Load(const std::string& path) override;
    };

}