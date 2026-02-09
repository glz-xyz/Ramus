#pragma once

#include "Ramus/Graphics/RHI/GraphicsResource.hpp"
#include "Ramus/Graphics/GraphicsTypes.hpp"

#include <cstddef>

namespace ramus
{

    class Buffer : public GraphicsResource<Buffer>
    {
    public:
        Buffer(size_t size, const void* data, BufferFlags flags);
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
    };

}