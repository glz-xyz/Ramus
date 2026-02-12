#include "Ramus/Graphics/Geometry/Mesh.hpp"

namespace ramus
{
    Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
    {
        /*
        m_vertexArray = std::make_unique<VertexArray>();

        auto vbo = std::make_shared<VertexBuffer>(vertices.size() * sizeof(Vertex), vertices.data(), BufferFlags::Dynamic);
        vbo->SetLayout({
            { ShaderDataType::Float3, "a_position" },
            { ShaderDataType::Float3, "a_normal"},
            { ShaderDataType::Float3, "a_tangent"},
            { ShaderDataType::Float2, "a_texCoords"}    
        });
        m_vertexArray->AddVertexBuffer(vbo);

        m_numIndices = static_cast<uint32_t>(indices.size());
        auto ibo = std::make_shared<IndexBuffer>(m_numIndices, indices.data());
        m_vertexArray->SetIndexBuffer(ibo);
        */
    }

    Mesh::~Mesh()
    {
        
    }
}