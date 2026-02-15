#pragma once

#include "Ramus/Assets/Asset.hpp"

#include <memory>

namespace ramus
{
    class ShaderProgramBase;
    class GraphicsDevice;

    class Material : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Material)

        Material();
        ~Material();

        void SetShaderProgram(std::shared_ptr<ShaderProgramBase> program);
        void Bind() const;

    protected:
        std::shared_ptr<ShaderProgramBase> m_shaderProgram;
    };
}