#include "Ramus/Graphics/VertexArray.hpp"
#include "Ramus/Graphics/GraphicsInternal.hpp"

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

    void VertexArray::BindVertexBuffer(const VertexBuffer& vbo, uint32_t bindingIndex, int32_t offset, int32_t stride) 
    {
        glVertexArrayVertexBuffer(m_handle, toUint(bindingIndex), getHandle(vbo), toPtr(offset), toSize(stride));
    }

    void VertexArray::BindIndexBuffer(const IndexBuffer& ibo) 
    {
        glVertexArrayElementBuffer(m_handle, getHandle(ibo));
    }
}