#include "Ramus/Assets/Material.hpp"
#include "Ramus/Graphics/Device/GraphicsDevice.hpp"
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

    void Material::Bind() const
    {
        m_shaderProgram->Bind();
    }

}