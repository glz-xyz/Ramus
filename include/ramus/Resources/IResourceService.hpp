#pragma once

#include <memory>
#include <string>

namespace ramus
{

    class Model;
    class Texture;
    class Shader;

    class IResourceService
    {
    public:
        virtual ~IResourceService() = default;

        virtual std::shared_ptr<Model> LoadModel(const std::string& modelPath) = 0;
        virtual std::shared_ptr<Texture> LoadTexture(const std::string& texturePath) = 0;
        virtual std::shared_ptr<Shader> LoadShader(const std::string& shaderPath) = 0;
    };

}