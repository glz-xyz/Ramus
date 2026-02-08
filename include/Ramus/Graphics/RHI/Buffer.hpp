#pragma once

#include "Ramus/Graphics/RHI/GraphicsResource.hpp"

namespace ramus
{

    class Buffer : public GraphicsResource<Buffer>
    {
    public:
        Buffer(size_t size, const void* data, uint32_t flags);
        ~Buffer();

        Buffer(const Buffer&) = delete;
        Buffer& operator=(const Buffer&) = delete;
    };

}