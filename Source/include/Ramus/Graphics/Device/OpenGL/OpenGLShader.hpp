#pragma once

#include "Ramus/Graphics/Device/Base/ShaderBase.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLHandle.hpp"

#include <string>

namespace ramus 
{
    
    class OpenGLShader : public ShaderBase
    {
    public:
        OpenGLShader(ShaderStage stage, const std::string& source);

        OpenGLShader(const OpenGLShader&) = delete;
        OpenGLShader& operator=(const OpenGLShader&) = delete;

        uint32_t GetHandle() const { return m_handle.Get(); }
        ShaderStage GetStage() const { return m_stage; }

    private:
        OpenGLHandle<ShaderDeleter> m_handle;
        ShaderStage m_stage;
    };

}