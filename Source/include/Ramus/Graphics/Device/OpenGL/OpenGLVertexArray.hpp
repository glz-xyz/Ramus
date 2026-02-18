#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLHandle.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexBuffer.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLIndexBuffer.hpp"

namespace ramus
{

    class OpenGLVertexArray
    {
    public:
        OpenGLVertexArray();

        OpenGLVertexArray(const OpenGLVertexArray&) = delete;
        OpenGLVertexArray& operator=(const OpenGLVertexArray&) = delete;

        void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vbo);
        void SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& ibo);

        void Bind() const;
        void Unbind() const;

        uint32_t GetHandle() const { return m_handle.Get(); }

    private:
        static uint32_t CreateInternal();
        OpenGLHandle<VertexArrayDeleter> m_handle;
        
        uint32_t m_vboIdx = 0;

        std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_vbos;
        std::shared_ptr<OpenGLIndexBuffer> m_ibo;
    };

}