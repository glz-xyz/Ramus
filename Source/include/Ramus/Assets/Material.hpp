#pragma once

#include "Ramus/Assets/Asset.hpp"

#include <memory>

namespace ramus
{
    class ShaderProgramBase;
    class TextureBase;

    class Material : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Material)

        Material();
        ~Material();

        void SetShaderProgram(std::shared_ptr<ShaderProgramBase> program) { m_shaderProgram = program; }
        std::shared_ptr<ShaderProgramBase> GetShaderProgram() const { return m_shaderProgram; }
        
        void SetDiffuseTexture(std::shared_ptr<TextureBase> texture) { m_diffuseTexture = texture; }
        std::shared_ptr<TextureBase> GetDiffuseTexture() const { return m_diffuseTexture; }

    protected:
        std::shared_ptr<ShaderProgramBase> m_shaderProgram;
        std::shared_ptr<TextureBase> m_diffuseTexture;
    };
}