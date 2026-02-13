#pragma once

#include <cstdint>
namespace ramus 
{
    class BufferBase 
    {
    public:
        virtual ~BufferBase() = default;
        virtual void SetData(const void* data, uint32_t size) = 0;
        virtual uint32_t GetSize() const = 0;
    };
}