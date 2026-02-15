#pragma once

#include <glad/gl.h>
#include <cstdint>

namespace ramus
{
    struct BufferDeleter        { void operator()(uint32_t handle) { glDeleteBuffers(1, &handle); } };
    struct ProgramDeleter       { void operator()(uint32_t handle) { glDeleteProgram(handle); } };
    struct ShaderDeleter        { void operator()(uint32_t handle) { glDeleteShader(handle); } };
    struct TextureDeleter       { void operator()(uint32_t handle) { glDeleteTextures(1, &handle); } };
    struct VertexArrayDeleter   { void operator()(uint32_t handle) { glDeleteVertexArrays(1, &handle); } };

    template<typename Deleter>
    class OpenGLHandle {
    public:
        OpenGLHandle() : m_handle(0) {}
        explicit OpenGLHandle(uint32_t handle) : m_handle(handle) {}

        ~OpenGLHandle() { Cleanup(); }

        OpenGLHandle(const OpenGLHandle&) = delete;
        OpenGLHandle& operator=(const OpenGLHandle&) = delete;

        OpenGLHandle(OpenGLHandle&& other) noexcept : m_handle(other.m_handle) { other.m_handle = 0; }
        OpenGLHandle& operator=(OpenGLHandle&& other) noexcept 
        {
            Cleanup();
            m_handle = other.m_handle;
            other.m_handle = 0;
            return *this;
        }

        operator uint32_t() const { return m_handle; }
        uint32_t Get() const { return m_handle; }

    private:
        void Cleanup() 
        {
            if (m_handle != 0) 
                Deleter()(m_handle);
        }
        uint32_t m_handle;
    };
}