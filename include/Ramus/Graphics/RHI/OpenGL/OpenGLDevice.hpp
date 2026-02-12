#pragma once

#include "Ramus/Graphics/RHI/GraphicsDevice.hpp"
#include "Ramus/Graphics/RHI/OpenGL/OpenGLContext.hpp"

#include <memory>

namespace ramus 
{

    class OpenGLDevice : public GraphicsDevice
    {
    public:
        OpenGLDevice(void* nativeWindow);

        void Init() override;

        void SetClearColor(const glm::vec4& clearColor) override;
        void Clear() override;
        void Present() override;

    private:
        std::unique_ptr<OpenGLContext> m_context;
    };

}