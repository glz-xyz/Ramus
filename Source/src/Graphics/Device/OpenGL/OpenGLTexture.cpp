#include "Ramus/Graphics/Device/OpenGL/OpenGLTexture.hpp"
#include "Ramus/Graphics/GraphicsDefines.hpp"

namespace ramus 
{

    static GLenum MapFormat(TextureFormat format) {
        switch (format) {
            case TextureFormat::RGB8:  return GL_RGB;
            case TextureFormat::RGBA8: return GL_RGBA;
            default:                   return GL_RGBA;
        }
    }
    
    OpenGLTexture::OpenGLTexture(const TextureDescriptor& desc, const void* data)
    {
        uint32_t handle;
        glGenTextures(1, &handle);
        glBindTexture(GL_TEXTURE_2D, handle);

        GLint filter = (desc.minFilter == TextureFilter::Linear) ? GL_LINEAR : GL_NEAREST;
        GLint wrap   = (desc.wrapS == TextureWrap::Repeat)       ? GL_REPEAT : GL_CLAMP_TO_EDGE;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, desc.useMipmaps ? GL_LINEAR_MIPMAP_LINEAR : filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

        glTexImage2D(
            GL_TEXTURE_2D, 
            0,                // Mip level
            GL_RGBA8,         // Internal Format
            desc.width, 
            desc.height, 
            0,                // Border
            GL_RGBA,          // Data format
            GL_UNSIGNED_BYTE, // Data type
            data
        );

        if (desc.useMipmaps) 
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        m_handle = OpenGLHandle<TextureDeleter>(handle);
    }
}