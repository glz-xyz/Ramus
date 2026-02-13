#pragma once

#include "Ramus/Graphics/Device/DeviceResource.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexArray.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"

namespace ramus
{
    class OpenGLMesh : public DeviceResource
    {
    public:
        OpenGLMesh(const Mesh& meshData);

        void Bind();
        void Unbind();

    private: 
        std::unique_ptr<OpenGLVertexArray> m_vao;
        uint32_t m_indexCount;
    };
}