#pragma once
#include "Ramus/Graphics/RHI/OpenGL/Buffers/OpenGLBuffer.hpp"

namespace ramus
{

    class OpenGLIndexBuffer : public OpenGLBuffer
    {
    public:
        OpenGLIndexBuffer(size_t size, const void* data, BufferFlags flags = BufferFlags::None)
            : OpenGLBuffer(size, data, flags) 
        {
        }

        ~OpenGLIndexBuffer() = default;
    };

}