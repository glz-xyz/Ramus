#include "Ramus/Assets/Material.hpp"
#include "Ramus/Graphics/Device/GraphicsContext.hpp"
#include "Ramus/Graphics/Device/Base/ShaderProgramBase.hpp"

namespace ramus
{

    Material::Material()
    {

    }

    Material::~Material()
    {
        
    }

    void Material::SetShaderProgram(std::shared_ptr<ShaderProgramBase> program) 
    { 
        m_shaderProgram = program; 
    }

    void Material::Bind(GraphicsContext* context) const
    {
        m_shaderProgram->Bind();

        if (m_diffuseTexture)
        {
            context->SetTexture(0, m_diffuseTexture.get());
        }
    }

}