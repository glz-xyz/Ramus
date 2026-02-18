#pragma once

#include <cstdint>

namespace ramus
{
    class DeviceResource;
    class TextureBase;
    class VertexBufferBase;
    class IndexBufferBase;

    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;

        // Resource Binding
        virtual void SetTexture(uint32_t slot, TextureBase* texture) = 0;
        virtual void SetVertexBuffer(VertexBufferBase* vbo) = 0;
        virtual void SetIndexBuffer(IndexBufferBase* ibo) = 0;
        // Temp
        virtual void BindGeometry(DeviceResource* resource) = 0;
        virtual void UnbindGeometry() = 0;
        
        // State
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) = 0;
        virtual void SetClearColor(float r, float g, float b, float a) = 0;
        virtual void Clear() = 0;

        // Draw Calls
        virtual void DrawIndexed(uint32_t count) = 0;
    };
}