#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLResource.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexBuffer.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLIndexBuffer.hpp"

#include <memory>
#include <vector>

namespace ramus
{

    class OpenGLVertexArray : public OpenGLResource<OpenGLVertexArray>
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        OpenGLVertexArray(const OpenGLVertexArray&) = delete;
        OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;

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