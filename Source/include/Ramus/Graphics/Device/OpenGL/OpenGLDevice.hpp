#pragma once

#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLContext.hpp"

namespace ramus 
{
    class ShaderProgramBase;

    class OpenGLDevice : public GraphicsDevice
    {
    public:
        OpenGLDevice(void* nativeWindow);

        void SetInitialState() override;
        void SetVSync(bool enabled) override;
        void Present() override;

        GraphicsContext* GetContext() override;
        void* GetNativeWindow() override;

        std::unique_ptr<DeviceResource> CreateResource(const Mesh& mesh) override;
        std::unique_ptr<ShaderProgramBase> CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) override;
        std::unique_ptr<TextureBase> CreateTexture(const TextureDescriptor& desc, const void* data) override;

    private:
        std::unique_ptr<OpenGLContext> m_context;
        void* m_nativeWindow;
    };

}