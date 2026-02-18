#pragma once

#include "Ramus/Graphics/GraphicsDefines.hpp"
#include "Ramus/Graphics/Device/GraphicsContext.hpp"
#include "Ramus/Graphics/Device/Base/VertexBufferBase.hpp"
#include "Ramus/Graphics/Device/Base/IndexBufferBase.hpp"
#include "Ramus/Graphics/Device/Base/TextureBase.hpp"
#include "Ramus/Graphics/Device/Base/ShaderBase.hpp"
#include "Ramus/Graphics/Device/Base/ShaderProgramBase.hpp"
#include "Ramus/Graphics/Device/DeviceResource.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"

namespace ramus
{
    enum class GraphicsAPI
    {
        None = 0,
        OpenGL = 1
    };

    class GraphicsDevice
    {
    public:
        virtual ~GraphicsDevice() = default;
        
        virtual void SetInitialState() = 0;
        virtual void SetVSync(bool enabled) = 0;

        // Resource Creation
        virtual std::unique_ptr<DeviceResource> CreateResource(const Mesh& mesh) = 0;
        virtual std::unique_ptr<ShaderProgramBase> CreateShaderProgram(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc) = 0;
        virtual std::unique_ptr<TextureBase> CreateTexture(const TextureDescriptor& desc, const void* data) = 0;
    
        // Swapchain
        virtual void Present() = 0;

        // Getters
        virtual void* GetNativeWindow() = 0;
        virtual GraphicsContext* GetContext() = 0;
        static GraphicsAPI GetAPI() { return s_API; }
        
    private:
        static GraphicsAPI s_API;
    };
}