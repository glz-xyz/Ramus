#include "Ramus/Graphics/Device/OpenGL/OpenGLMesh.hpp"

namespace ramus 
{

    OpenGLMesh::OpenGLMesh(const Mesh& mesh) 
    {
        m_vao = std::make_unique<OpenGLVertexArray>();
        m_vao->Bind();

        auto vbo = std::make_shared<OpenGLVertexBuffer>(mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data());
        auto ibo = std::make_shared<OpenGLIndexBuffer>(mesh.indices.size(), mesh.indices.data());

        m_vao->AddVertexBuffer(vbo);
        m_vao->SetIndexBuffer(ibo);
        
        m_indexCount = static_cast<uint32_t>(mesh.indices.size());
        
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