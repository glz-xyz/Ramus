#pragma once

#include <string>
#include <vector>

namespace ramus 
{
    enum class BufferUsage { Static, Dynamic, Stream };
    enum class BufferType  { Vertex, Index, Uniform, Storage };
    enum class TextureFormat { RGBA8, RGB8, Depth24Stencil8, Float16 };

    struct BufferDesc 
    {
        size_t size;
        BufferType tan;
        BufferUsage usage;
        const void* data = nullptr;
        std::string debugName;
    };

    struct TextureDesc 
    {
        uint32_t width;
        uint32_t height;
        TextureFormat format;
        bool generateMipmaps = true;
        const void* data = nullptr;
    };

    struct ShaderDesc 
    {
        std::string vertexSource;
        std::string fragmentSource;
        std::string filePath; 
    };
}