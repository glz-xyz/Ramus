#include "Ramus/Resources/Loaders/ModelLoader.hpp"
#include "Ramus/Core/Log.hpp"
#include "Ramus/Graphics/Mesh.hpp"
#include "Ramus/Graphics/Vertex.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace ramus
{

    std::shared_ptr<Model> ModelLoader::Load(const std::string& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path
            , aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_FlipUVs
            | aiProcess_GenNormals
            | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Log::GetRendererLogger()->debug("Assimp Error: Failed to import model @ {}", path);
            return nullptr;
        }
        else if (!scene->HasMeshes())
        {
            Log::GetRendererLogger()->debug("Assimp Error: Model @ contains no meshes {}", path);
            return nullptr;
        }

        auto model = std::make_shared<Model>();
        ProcessNode(scene->mRootNode, scene, *model);

        return model;
    }

    void ModelLoader::ProcessNode(aiNode* node, const aiScene* scene, Model& model)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) 
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            model.AddMesh(ProcessMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) 
        {
            ProcessNode(node->mChildren[i], scene, model);
        }
    }


    std::unique_ptr<Mesh> ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        std::vector<Vertex> vertices = ExtractVertices(mesh);
        std::vector<uint32_t> indices = ExtractIndices(mesh);

        return std::make_unique<Mesh>(std::move(vertices), std::move(indices));
    }

    std::vector<Vertex> ModelLoader::ExtractVertices(aiMesh* mesh)
    {
        std::vector<Vertex> vertices;
        vertices.reserve(mesh->mNumVertices);

        for (uint32_t i = 0; i < mesh->mNumVertices; i++) 
        {
            Vertex vertex;

            vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

            if (mesh->HasNormals())
                vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            vertex.texCoords = mesh->mTextureCoords[0] 
                ? glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) 
                : glm::vec2(0.0f);

            vertices.push_back(vertex);
        }

        return vertices;
    }

    std::vector<uint32_t> ModelLoader::ExtractIndices(aiMesh* mesh)
    {
        std::vector<uint32_t> indices;
        indices.reserve(mesh->mNumFaces * 3);

        for (uint32_t f = 0; f < mesh->mNumFaces; f++)
        {
            const aiFace& face = mesh->mFaces[f];
        
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        return indices;
    }
}