#include "Ramus/Graphics/RHI/VertexArray.hpp"
#include "Ramus/Graphics/RHI/VertexBuffer.hpp"
#include "Ramus/Graphics/RHI/GraphicsInternal.hpp"

#include <memory>
#include <vector>

using namespace ramus::gl;

namespace ramus
{

    VertexArray::VertexArray()
    {
        glCreateVertexArrays(1, &m_handle);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_handle);
    }

    void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo) 
    {
        const auto& layout = vbo->GetLayout();

        glVertexArrayVertexBuffer(m_handle, 0, vbo->GetHandle(), 0, layout.GetStride());

        for (const auto& element : layout) 
        {
            glEnableVertexArrayAttrib(m_handle, m_vboIdx);

            glVertexArrayAttribFormat(m_handle, m_vboIdx, 
                element.GetComponentCount(), 
                ShaderDataTypeToOpenGL(element.type), 
                element.normalized, element.offset);

            glVertexArrayAttribBinding(m_handle, m_vboIdx, 0);
            m_vboIdx++;
        }
    }

    void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo) 
    {
        glVertexArrayElementBuffer(m_handle, getHandle(*ibo));
    }
}