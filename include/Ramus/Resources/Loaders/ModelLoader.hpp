#pragma once

#include "Ramus/Resources/Loaders/IResourceLoader.hpp"
#include "Ramus/Graphics/Model.hpp"
#include "Ramus/Graphics/Vertex.hpp"

#include <memory>
#include <vector>

struct aiScene;
struct aiMesh;
struct aiNode;

namespace ramus
{

    class ModelLoader : public IResourceLoader<Model>
    {
    public: 
        ModelLoader() = default;
        ~ModelLoader() = default;
        
        std::shared_ptr<Model> Load(const std::string& path) override;

    private:
        void ProcessNode(aiNode* node, const aiScene* scene, Model& model);
        std::unique_ptr<Mesh> ProcessMesh(aiMesh* mesh, const aiScene* scene);

        std::vector<Vertex> ExtractVertices(aiMesh* mesh);
        std::vector<uint32_t> ExtractIndices(aiMesh* mesh);
    };

}