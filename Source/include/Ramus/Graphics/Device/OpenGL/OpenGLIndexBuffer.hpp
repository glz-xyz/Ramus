#pragma once
#include "Ramus/Graphics/Device/OpenGL/OpenGLBuffer.hpp"

namespace ramus
{

    // [TODO] Should inherit from IndexBufferBase (and that from OpenGLBuffer)
    class OpenGLIndexBuffer : public OpenGLBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t count, const uint32_t* indices)
            : OpenGLBuffer(count * sizeof(uint32_t), indices, BufferFlags::None) 
        {
        }
    };

}