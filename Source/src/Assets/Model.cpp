#include "Ramus/Assets/Model.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"

namespace ramus
{

    Model::Model()
    {

    }

    Model::~Model()
    {
        
    }

    void Model::AddMesh(MeshLink&& meshLink)
    {
        m_meshLinks.push_back(std::move(meshLink));
    }

    const std::vector<MeshLink>& Model::GetMeshLinks() const
    {
        return m_meshLinks;
    }
}