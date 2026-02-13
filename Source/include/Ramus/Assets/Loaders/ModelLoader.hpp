#pragma once

#include "Ramus/Assets/Loaders/AssetLoader.hpp"
#include "Ramus/Assets/Model.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

#include <memory>
#include <vector>

struct aiScene;
struct aiMesh;
struct aiNode;

namespace ramus
{

    class ModelLoader : public AssetLoader<Model>
    {
    public: 
        ModelLoader(GraphicsDevice* graphicsDevice);
        ~ModelLoader() = default;
        
        std::shared_ptr<Model> Load(const std::string& path) override;

    private:
        void ProcessNode(aiNode* node, const aiScene* scene, Model& model);
        MeshLink ProcessMesh(aiMesh* mesh, const aiScene* scene);
        
        std::vector<Vertex> ExtractVertices(aiMesh* mesh);
        std::vector<uint32_t> ExtractIndices(aiMesh* mesh);
        
        GraphicsDevice* m_graphicsDevice;
    };

}