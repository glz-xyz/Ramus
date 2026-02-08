#pragma once

#include "Ramus/Graphics/Mesh.hpp"

#include <memory>
#include <vector>

namespace ramus
{

    class Model
    {
    public:
        Model() = default;
        ~Model() = default;

        void AddMesh(std::unique_ptr<Mesh> mesh) 
        {
            m_meshes.push_back(std::move(mesh));
        }

        const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const 
        { 
            return m_meshes; 
        }

    private:
        std::vector<std::unique_ptr<Mesh>> m_meshes;
    };

}