#pragma once

#include "Ramus/Graphics/GraphicsResource.hpp"
#include "Ramus/Graphics/VertexBuffer.hpp"
#include "Ramus/Graphics/IndexBuffer.hpp"

namespace ramus
{

    class VertexArray : public GraphicsResource<VertexArray>
    {
    public:
        VertexArray();
        ~VertexArray();

        void BindVertexBuffer(const VertexBuffer& vbo, uint32_t bindingIndex, int32_t offset, int32_t stride);
        void BindIndexBuffer(const IndexBuffer& ibo);

        void Bind() const;
        void Unbind() const;
    };

}