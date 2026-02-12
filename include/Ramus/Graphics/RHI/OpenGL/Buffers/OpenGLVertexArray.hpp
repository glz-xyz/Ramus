#pragma once

#include "Ramus/Graphics/RHI/GraphicsResource.hpp"
#include "Ramus/Graphics/RHI/VertexBuffer.hpp"
#include "Ramus/Graphics/RHI/IndexBuffer.hpp"

#include <memory>
#include <vector>

namespace ramus
{

    class VertexArray : public GraphicsResource<VertexArray>
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo);
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_vboIdx = 0;

        std::vector<std::shared_ptr<VertexBuffer>> m_vbos;
        std::shared_ptr<IndexBuffer> m_ibo;
    };

}