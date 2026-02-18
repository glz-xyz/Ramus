#pragma once

#include "Ramus/Assets/Asset.hpp"
#include "Ramus/Graphics/GraphicsDefines.hpp"

#include <memory>

namespace ramus
{
    class TextureBase;

    class Texture : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Texture)

        Texture(const TextureDescriptor& desc, std::unique_ptr<TextureBase> resource);
        ~Texture();

        std::shared_ptr<TextureBase> GetResource() const { return m_resource; }

    protected:
        TextureDescriptor m_descriptor;
        std::shared_ptr<TextureBase> m_resource;
    };
}