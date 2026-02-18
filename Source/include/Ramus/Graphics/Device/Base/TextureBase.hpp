#pragma once

#include <cstdint>

namespace ramus
{
    struct TextureDescriptor;
    class TextureBase 
    {
    public:
        virtual ~TextureBase() = default;

        virtual uint32_t GetHandle() const = 0;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual const TextureDescriptor& GetDescriptor() const = 0;
    };
}