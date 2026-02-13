#pragma once
#include <cstdint>

namespace ramus
{

    template <typename T>
    class OpenGLResource
    {
    public:
        uint32_t GetHandle() const { return m_handle; }
        bool IsValid() const { return m_handle != 0; }

    protected:
        OpenGLResource() = default;
        ~OpenGLResource() = default;

        uint32_t m_handle = 0;
    };

}