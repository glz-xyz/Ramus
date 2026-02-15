#pragma once

#include "Ramus/Assets/Asset.hpp"
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

    class Model : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Model)

        Model();
        ~Model();

        void AddMesh(MeshLink&& meshLink);

        const std::vector<MeshLink>& GetMeshLinks() const;
        
    private:
        std::vector<MeshLink> m_meshLinks;
    };
}