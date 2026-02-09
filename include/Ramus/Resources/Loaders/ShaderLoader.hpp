#pragma once

#include "Ramus/Resources/Loaders/IResourceLoader.hpp"
#include "Ramus/Graphics/Shader.hpp"

namespace ramus
{

    class ShaderLoader : public IResourceLoader<Shader>
    {
    public: 
        ShaderLoader() = default;
        ~ShaderLoader() = default;
        
        std::shared_ptr<Shader> Load(const std::string& path) override;
    };

}