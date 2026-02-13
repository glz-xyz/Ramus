#pragma once

#include "Ramus/Graphics/Geometry/Mesh.hpp"
#include "Ramus/Graphics/Device/DeviceResource.hpp"

#include <vector>
#include <memory>

namespace ramus
{
    struct MeshLink
    {
        std::unique_ptr<Mesh> mesh;
        std::unique_ptr<DeviceResource> resource;
    };

    class Model
    {
    public:
        Model();
        ~Model();

        void AddMesh(MeshLink&& meshLink);

        const std::vector<MeshLink>& GetMeshLinks() const;
        
    private:
        std::vector<MeshLink> m_meshLinks;
    };
}