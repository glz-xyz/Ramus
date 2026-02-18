#pragma once

#include "Ramus/Assets/Asset.hpp"

#include <memory>

namespace ramus
{
    class GraphicsContext;
    class ShaderProgramBase;
    class TextureBase;

    class Material : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Material)

        Material();
        ~Material();

        void SetShaderProgram(std::shared_ptr<ShaderProgramBase> program);
        void SetDiffuseTexture(std::shared_ptr<TextureBase> texture) { m_diffuseTexture = texture; }
        void Bind(GraphicsContext* context) const;

    protected:
        std::shared_ptr<ShaderProgramBase> m_shaderProgram;
        std::shared_ptr<TextureBase> m_diffuseTexture;
    };
}