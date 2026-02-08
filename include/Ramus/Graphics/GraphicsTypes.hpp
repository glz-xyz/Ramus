#pragma once

#include <cstdint>

namespace ramus 
{

    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) 
    {
        switch (type) 
        {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
        }
        return 0;
    }

    static uint32_t GetShaderDataTypeComponentCount(ShaderDataType type) 
    {
        switch (type)
        {
            case ShaderDataType::Float:    return 1;
            case ShaderDataType::Float2:   return 2;
            case ShaderDataType::Float3:   return 3;
            case ShaderDataType::Float4:   return 4;
            case ShaderDataType::Mat3:     return 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4;
            case ShaderDataType::Int:      return 1;
            case ShaderDataType::Int2:     return 2;
            case ShaderDataType::Int3:     return 3;
            case ShaderDataType::Int4:     return 4;
            case ShaderDataType::Bool:     return 1;
        }
        return 0;
    }

    enum class BufferFlags : uint32_t {
        None         = 0,
        MapRead      = 0x0001, // GL_MAP_READ_BIT
        MapWrite     = 0x0002, // GL_MAP_WRITE_BIT
        Dynamic      = 0x0004, // GL_DYNAMIC_STORAGE_BIT
        Client       = 0x0008  // GL_CLIENT_STORAGE_BIT
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
}