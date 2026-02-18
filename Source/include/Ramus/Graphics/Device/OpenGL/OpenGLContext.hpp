#pragma once

#include "Ramus/Graphics/Device/GraphicsContext.hpp"

namespace ramus 
{

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext();
        ~OpenGLContext();

        void Init() override;

       void Clear() override;
       
       void BindGeometry(DeviceResource* resource) override;
       void UnbindGeometry() override;
       
       void SetTexture(uint32_t slot, TextureBase* texture) override;
       void SetVertexBuffer(VertexBufferBase* vbo) override;
       void SetIndexBuffer(IndexBufferBase* ibo) override;
       void SetViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h) override;
       void SetClearColor(float r, float g, float b, float a) override;

       void DrawIndexed(uint32_t count) override;
    };

}