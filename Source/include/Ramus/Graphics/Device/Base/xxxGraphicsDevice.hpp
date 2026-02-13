#pragma once

#include "Ramus/Graphics/Device/Base/GraphicsContext.hpp"

#include <memory>
#include <glm/glm.hpp>

namespace ramus
{
    class VertexBuffer;
    class IndexBuffer;
    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;

        virtual void Init() = 0;
        
        virtual void SetClearColor(const glm::vec4& clearColor) = 0;
        virtual void Clear() = 0;
        virtual void Present() = 0;

        virtual void SetVertexBuffers(uint32_t startSlot, const std::vector<std::shared_ptr<VertexBuffer>>& buffers) = 0;
        virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
        //virtual void SetPipelineState(const PipelineState& state) = 0;
    };
}