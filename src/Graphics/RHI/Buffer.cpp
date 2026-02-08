#include "Ramus/Graphics/RHI/Buffer.hpp"
#include "Ramus/Graphics/RHI/GraphicsInternal.hpp"

using namespace ramus::gl;

namespace ramus
{

    Buffer::Buffer(size_t size, const void* data, BufferFlags flags)
    {
        glCreateBuffers(1, &m_handle);
        glNamedBufferStorage(m_handle, toSize(size), data, BufferFlagsToOpenGL(flags));
    }


    Buffer::~Buffer()
    {
        if (IsValid())
        {
            glDeleteBuffers(1, &m_handle);
            m_handle = 0;
        }
    }
}