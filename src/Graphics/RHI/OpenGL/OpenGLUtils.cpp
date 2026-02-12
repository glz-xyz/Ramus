#pragma once

#include <glad/gl.h>

#include "Ramus/Graphics/GraphicsDefines.hpp"
#include "Ramus/Graphics/RHI/OpenGL/Buffers/OpenGLBuffer.hpp"

namespace ramus::gl
{
    inline GLint toBitfield(int32_t value) { return static_cast<GLbitfield>(value); }
    inline GLint toInt(int32_t value) { return static_cast<GLint>(value); }
    inline GLint toPtr(int32_t value) { return static_cast<GLintptr>(value); }
    inline GLint toSize(int32_t value) { return static_cast<GLsizei>(value); }
    inline GLint toUint(int32_t value) { return static_cast<GLuint>(value); }

    //template <typename T>
    //inline GLuint getHandle(const Buffer& buffer) { return toUint(buffer.GetHandle()); }

    //template <typename T>
    //inline GLuint getHandle(const GraphicsResource<T>& resource) { return toUint(resource.GetHandle()); }

    static GLenum ShaderDataTypeToOpenGL(ramus::ShaderDataType type)
    {
        switch (type)
        {
            case ramus::ShaderDataType::Float:    return GL_FLOAT;
            case ramus::ShaderDataType::Float2:   return GL_FLOAT;
            case ramus::ShaderDataType::Float3:   return GL_FLOAT;
            case ramus::ShaderDataType::Float4:   return GL_FLOAT;
            case ramus::ShaderDataType::Mat3:     return GL_FLOAT;
            case ramus::ShaderDataType::Mat4:     return GL_FLOAT;
            case ramus::ShaderDataType::Int:      return GL_INT;
            case ramus::ShaderDataType::Int2:     return GL_INT;
            case ramus::ShaderDataType::Int3:     return GL_INT;
            case ramus::ShaderDataType::Int4:     return GL_INT;
            case ramus::ShaderDataType::Bool:     return GL_BOOL;
            default: break;
        }

        return 0;
    }

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
}