#include "Ramus/Assets/Loaders/MaterialLoader.hpp"
#include "Ramus/Assets/AssetManager.hpp"
#include "Ramus/Assets/Material.hpp"
#include "Ramus/Core/Services/Logger.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"

#include <string>

#include <fstream>
#include <sstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace 
{
    std::string LoadFileToString(const std::string& path) 
    {
        std::ifstream file(path);
        if (!file.is_open()) 
        {
            ramus::Logger::GetRendererLogger()->error("Failed to open shader file: {}", path);
            return "";
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
}

namespace ramus
{
    MaterialLoader::MaterialLoader()
    {
        m_supportedExtensions = { ".mat" };
    }

    MaterialLoader::~MaterialLoader()
    {
    }

    std::shared_ptr<Material> MaterialLoader::Load(const std::string& path, AssetLoadContext& loadContext)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            Logger::GetAssetLogger()->error("Failed to open material file: {}", path);
            return nullptr;
        }

        nlohmann::json data;
        try 
        {
            file >> data;
        } 
        catch (const nlohmann::json::parse_error& e) 
        {
            Logger::GetAssetLogger()->error("JSON Parse Error in {}: {}", path, e.what());
            return nullptr;
        }

        auto material = std::make_shared<Material>();
        
        if (data.contains("shader")) 
        {
            std::string vertexShaderPath = data["shader"]["vertex"];
            std::string fragmentShaderPath = data["shader"]["fragment"];
            
            std::filesystem::path assetRoot = ramus::GetExecutableDirectory();
            std::filesystem::path fullVsPath = assetRoot / vertexShaderPath;
            std::filesystem::path fullFsPath = assetRoot / fragmentShaderPath;

            std::string vsSource = LoadFileToString(fullVsPath.string());
            std::string fsSource = LoadFileToString(fullFsPath.string());

            auto shaderProgram = loadContext.device->CreateShaderProgram(vsSource, fsSource);

            material->SetShaderProgram(std::move(shaderProgram));
        }

        if (data.contains("samplers") && data["samplers"].is_array()) 
        {
            for (const auto& sampler : data["samplers"]) 
            {
                std::string bindingName = sampler["binding"];

                // If texture is null, maybe assign a default/missing texture
                if (sampler["texture"].is_null()) 
                {
                    // [TODO] material->SetTexture(...
                } 
                else 
                {
                    std::string texPath = sampler["texture"];
                    auto texture = loadContext.manager->LoadTexture(texPath);
                    // [TODO] hack to hardcode diffuse (only type for now)
                    material->SetDiffuseTexture(texture->GetResource());
                }
            }
        }

        return material;
    }

}