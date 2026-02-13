#pragma once

#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLContext.hpp"

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

        std::unique_ptr<DeviceResource> CreateResource(const Mesh& mesh) override;

        void BindGeometry(DeviceResource* resource) override;
        void UnbindGeometry() override;

        void DrawIndexed(uint32_t indexCount) override;

    private:
        std::unique_ptr<OpenGLContext> m_context;
    };

}