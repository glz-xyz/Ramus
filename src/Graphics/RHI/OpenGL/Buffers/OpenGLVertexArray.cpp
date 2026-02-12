#pragma once

#include "Ramus/Graphics/RHI/OpenGL/OpenGLResource.hpp"
#include "Ramus/Graphics/RHI/OpenGL/Buffers/OpenGLVertexBuffer.hpp"
#include "Ramus/Graphics/RHI/OpenGL/Buffers/OpenGLIndexBuffer.hpp"

#include <memory>
#include <vector>

namespace ramus
{

    class VertexArray : public OpenGLResource<VertexArray>
    {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator=(const VertexArray&) = delete;

        void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vbo);
        void SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& ibo);

        void Bind() const;
        void Unbind() const;

    private:
        uint32_t m_vboIdx = 0;

        std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vbos;
        std::shared_ptr<OpenGLIndexBuffer> m_ibo;
    };

}