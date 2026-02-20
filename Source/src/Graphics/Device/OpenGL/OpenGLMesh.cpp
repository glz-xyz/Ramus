#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLVertexBuffer.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLIndexBuffer.hpp"

namespace ramus 
{

    OpenGLMesh::OpenGLMesh(const Mesh& mesh) 
    {
        m_vao = std::make_unique<OpenGLVertexArray>();
        m_vao->Bind();

        auto vbo = std::make_shared<OpenGLVertexBuffer>(mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data());
        
        m_indexCount = static_cast<uint32_t>(mesh.indices.size());
        auto ibo = std::make_shared<OpenGLIndexBuffer>(m_indexCount, mesh.indices.data());

        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);
        m_vao->Unbind();
    }

    void OpenGLMesh::Bind()
    {
        m_vao->Bind();
    }

    void OpenGLMesh::Unbind()
    {
        m_vao->Unbind();
    }
}