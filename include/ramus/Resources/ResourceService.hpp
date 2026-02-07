#pragma once

#include "Ramus/Resources/IResourceService.hpp"

namespace ramus 
{

    class ResourceService : public IResourceService 
    {
    public:
        ResourceService() = default;
        ~ResourceService() override = default;

        std::shared_ptr<Model> LoadModel(const std::string& modelPath) override 
        {
            // TODO: assimp logic
            return nullptr; 
        }

        std::shared_ptr<Texture> LoadTexture(const std::string& texturePath) override 
        {
            // [TODO] stb_image logic
            return nullptr;
        }

        std::shared_ptr<Shader> LoadShader(const std::string& shaderPath) override 
        {
            // [TODO] Shader compile/link/cache logic
            return nullptr;
        }
    };

}