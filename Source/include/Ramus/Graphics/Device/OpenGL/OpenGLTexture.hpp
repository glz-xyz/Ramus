#pragma once

#include "Ramus/Graphics/Device/Base/TextureBase.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLHandle.hpp"
#include "Ramus/Graphics/GraphicsDefines.hpp"

namespace ramus
{
    class OpenGLTexture : public TextureBase
    {
    public:
        OpenGLTexture(const TextureDescriptor& desc, const void* data);

        uint32_t GetWidth() const override { return m_descriptor.width; }
        uint32_t GetHeight() const override { return m_descriptor.height; }
        const TextureDescriptor& GetDescriptor() const override { return m_descriptor; }
        uint32_t GetHandle() const override { return m_handle.Get(); }
        
    private:
        OpenGLHandle<TextureDeleter> m_handle;
        TextureDescriptor m_descriptor;
    };
}