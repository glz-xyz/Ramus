#pragma once

#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexArray.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLUtils.hpp"

#include <glad/gl.h>

namespace ramus
{

    OpenGLVertexArray::OpenGLVertexArray() : 
        m_handle(CreateInternal()),
        m_vboIdx(0)
    {
        
    }

    uint32_t OpenGLVertexArray::CreateInternal()
    {
        uint32_t handle = 0;
        glCreateVertexArrays(1, &handle);
        return handle;
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vbo)
    {
        // const auto& layout = vbo->GetLayout();
        // HACK
        auto layout = OpenGLVertexBuffer::Layout(
        {
            { ShaderDataType::Float3, "a_position" },
            { ShaderDataType::Float2, "a_texCoord"}    
        });

        uint32_t bindingPoint = 0;
        glVertexArrayVertexBuffer(m_handle, bindingPoint, vbo->GetHandle(), 0, layout.GetStride());

        for (const auto& element : layout) 
        {
            glEnableVertexArrayAttrib(m_handle, m_vboIdx);
            glVertexArrayAttribFormat(
                m_handle, 
                m_vboIdx, 
                element.GetComponentCount(), 
                gl::ShaderDataTypeToOpenGL(element.type), 
                element.normalized ? GL_TRUE : GL_FALSE, 
                element.offset
            );

            glVertexArrayAttribBinding(m_handle, m_vboIdx, bindingPoint);

            m_vboIdx++;
        }

        m_vbos.push_back(vbo);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& ibo)
    {
        glVertexArrayElementBuffer(m_handle, ibo->GetHandle());
        m_ibo = ibo;
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_handle);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

}