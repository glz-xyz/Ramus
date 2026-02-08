#pragma once

#include "Ramus/Resources/ResourceLoader.hpp"
#include "Ramus/Graphics/Texture.hpp"

namespace ramus
{

    class TextureLoader : public ResourceLoader<Texture>
    {
    public: 
        TextureLoader() = default;
        ~TextureLoader() = default;
        
        std::shared_ptr<Texture> Load(const std::string& path) override;
    };

}