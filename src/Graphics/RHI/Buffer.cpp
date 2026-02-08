#include "Ramus/Graphics/RHI/Buffer.hpp"
#include "Ramus/Graphics/RHI/GraphicsInternal.hpp"

using namespace ramus::gl;

namespace ramus
{

    Buffer::Buffer(size_t size, const void* data, uint32_t flags)
    {
        glCreateBuffers(1, &m_handle);
        glNamedBufferStorage(m_handle, toSize(size), data, toBitfield(flags));
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