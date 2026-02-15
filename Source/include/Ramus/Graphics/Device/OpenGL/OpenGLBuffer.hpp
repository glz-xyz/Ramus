#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLHandle.hpp"

#include <glad/gl.h>

#include <cstddef>
#include <cstdint>

namespace ramus
{
     enum class BufferFlags : uint32_t 
     {
        None         = 0,
        MapRead      = 0x0001,
        MapWrite     = 0x0002,
        Dynamic      = 0x0004,
        Client       = 0x0008
    };

    inline BufferFlags operator|(BufferFlags a, BufferFlags b) {
        return static_cast<BufferFlags>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
    }

    enum class BufferUsage : uint8_t
    {
        None = 0, 
        Static,
        Dynamic,
        Stream
    };

     static GLbitfield BufferFlagsToOpenGL(BufferFlags flags) 
    {
        GLbitfield glFlags = 0;
        if ((uint32_t)flags & (uint32_t)BufferFlags::MapRead)  glFlags |= GL_MAP_READ_BIT;
        if ((uint32_t)flags & (uint32_t)BufferFlags::MapWrite) glFlags |= GL_MAP_WRITE_BIT;
        if ((uint32_t)flags & (uint32_t)BufferFlags::Dynamic)  glFlags |= GL_DYNAMIC_STORAGE_BIT;
        if ((uint32_t)flags & (uint32_t)BufferFlags::Client)   glFlags |= GL_CLIENT_STORAGE_BIT;
        return glFlags;
    }

    static GLenum BufferUsageToOpenGL(BufferUsage usage)
    {
        switch (usage)
        {
            case BufferUsage::Static:  return GL_STATIC_DRAW;
            case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
            case BufferUsage::Stream:  return GL_STREAM_DRAW;
        }
        return GL_STATIC_DRAW;
    }

    class OpenGLBuffer
    {
    public:
        OpenGLBuffer(size_t size, const void* data, BufferFlags flags);
        ~OpenGLBuffer();

        OpenGLBuffer(const OpenGLBuffer&) = delete;
        OpenGLBuffer& operator=(const OpenGLBuffer&) = delete;

        uint32_t GetHandle() const { return m_handle.Get(); }

    protected:
        OpenGLHandle<BufferDeleter> m_handle;
    };

}