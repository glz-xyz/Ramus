#include "Ramus/Assets/Loaders/ModelLoader.hpp"
#include "Ramus/Assets/Model.hpp"
#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/Geometry/Mesh.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

namespace ramus
{
    ModelLoader::ModelLoader()
    {
        m_supportedExtensions = { ".gltf" };
    }

    ModelLoader::~ModelLoader()
    {
    }

    std::shared_ptr<Model> ModelLoader::Load(const std::string& path, AssetLoadContext& loadContext)
    {
        m_currentLoadContext = &loadContext;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path
            , aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_FlipUVs
            | aiProcess_GenNormals
            | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            Logger::GetRendererLogger()->debug("Assimp Error: Failed to import model @ {}", path);
            return nullptr;
        }
        else if (!scene->HasMeshes())
        {
            Logger::GetRendererLogger()->debug("Assimp Error: Model @ contains no meshes {}", path);
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


    MeshLink ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        auto geoMesh = std::make_unique<Mesh>();
        geoMesh->vertices = ExtractVertices(mesh);
        geoMesh->indices = ExtractIndices(mesh);

        auto gpuMesh = m_currentLoadContext->device->CreateResource(*geoMesh);

        return { std::move(geoMesh), std::move(gpuMesh) };
    }

    std::vector<Vertex> ModelLoader::ExtractVertices(aiMesh* mesh)
    {
        std::vector<Vertex> vertices;
        vertices.reserve(mesh->mNumVertices);

        for (uint32_t i = 0; i < mesh->mNumVertices; i++) 
        {
            Vertex vertex;

            vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

            //if (mesh->HasNormals())
            //    vertex.normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

            vertex.texCoord = mesh->mTextureCoords[0] 
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