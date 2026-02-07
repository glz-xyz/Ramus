#pragma once

#include <glad/gl.h>

#include "Ramus/Graphics/Buffer.hpp"
#include "Ramus/Graphics/GraphicsResource.hpp"

namespace ramus::gl
{
    inline GLint toBitfield(int32_t value) { return static_cast<GLbitfield>(value); }
    inline GLint toInt(int32_t value) { return static_cast<GLint>(value); }
    inline GLint toPtr(int32_t value) { return static_cast<GLintptr>(value); }
    inline GLint toSize(int32_t value) { return static_cast<GLsizei>(value); }
    inline GLint toUint(int32_t value) { return static_cast<GLuint>(value); }

    template <typename T>
    inline GLuint getHandle(const Buffer& buffer) { return toUint(buffer.GetHandle()); }

    template <typename T>
    inline GLuint getHandle(const GraphicsResource<T>& resource) { return toUint(resource.GetHandle()); }
}