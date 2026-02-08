#pragma once

#include "Ramus/Resources/ResourceLoader.hpp"
#include "Ramus/Graphics/Shader.hpp"

namespace ramus
{

    class ShaderLoader : public ResourceLoader<Shader>
    {
    public: 
        ShaderLoader() = default;
        ~ShaderLoader() = default;
        
        std::shared_ptr<Shader> Load(const std::string& path) override;
    };

}