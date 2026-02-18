#include "Ramus/Assets/Texture.hpp"
#include "Ramus/Graphics/Device/Base/TextureBase.hpp"
#include "Ramus/Graphics/GraphicsDefines.hpp"

#include <memory>

namespace ramus
{

    Texture::Texture(const TextureDescriptor& desc, std::unique_ptr<TextureBase> resource) :
        m_descriptor(desc),
        m_resource(std::move(resource))
    {

    }

    Texture::~Texture()
    {
        
    }

}