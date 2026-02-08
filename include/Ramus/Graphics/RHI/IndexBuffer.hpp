#pragma once
#include "Ramus/Graphics/RHI/Buffer.hpp"
#include "Ramus/Graphics/RHI/GraphicsInternal.hpp"

namespace ramus
{

    class IndexBuffer : public Buffer
    {
    public:
        IndexBuffer(size_t size, const void* data, BufferFlags flags = BufferFlags::None)
            : Buffer(size, data, flags) 
        {
        }
    };

}