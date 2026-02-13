#pragma once

#include "Ramus/Graphics/Device/Base/VertexBufferBase.hpp"
#include "Ramus/Graphics/Device/Base/IndexBufferBase.hpp"
#include "Ramus/Graphics/Device/Base/TextureBase.hpp"
#include "Ramus/Graphics/Device/Base/ShaderBase.hpp"
#include "Ramus/Graphics/Device/DeviceResource.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <cstdint>
#include <memory>

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

        virtual void Init() = 0;
        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& clearColor) = 0;
        virtual void Present() = 0;


        virtual std::unique_ptr<DeviceResource> CreateResource(const Mesh& mesh) = 0;

        virtual void BindGeometry(DeviceResource* resource) = 0;
        virtual void UnbindGeometry() = 0;

        virtual void DrawIndexed(uint32_t count) = 0;

        // State Management
        //virtual void SetVertexBuffers(const std::vector<std::shared_ptr<VertexBuffer>>& buffers) = 0;

        // Resource Factories
        //virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(uint32_t size, const void* data, BufferFlags flags) = 0;
        //virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(uint32_t count, const uint32_t* data, BufferFlags flags) = 0;

        static GraphicsAPI GetAPI() { return s_API; }
        
    private:
        static GraphicsAPI s_API;
    };
}