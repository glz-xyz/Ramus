#include "Ramus/Graphics/RHI/GraphicsDevice.hpp"

#include <glad/gl.h>

namespace ramus 
{

    void GraphicsDevice::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void GraphicsDevice::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

}