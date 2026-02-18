#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ramus 
{
    #pragma region Buffers
    enum class BufferFlags : uint32_t { None = 0, MapRead = 0x01, MapWrite = 0x02, Dynamic = 0x04, Client = 0x08 };
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

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;
        virtual void SetData(const void* data, uint32_t size) = 0;
        virtual uint32_t GetSize() const = 0;
        
        static std::shared_ptr<VertexBuffer> Create(uint32_t size, const void* data = nullptr);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() = default;
        virtual uint32_t GetCount() const = 0;
        
        static std::shared_ptr<IndexBuffer> Create(uint32_t count, const uint32_t* indices = nullptr);
    };
    #pragma endregion // Buffers

    enum class ShaderDataType { Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };
    
    struct ShaderDesc 
    {
        std::string vertexSource;
        std::string fragmentSource;
        std::string filePath; 
    };
}