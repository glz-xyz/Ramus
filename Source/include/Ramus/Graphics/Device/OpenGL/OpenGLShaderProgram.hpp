#pragma once

#include "Ramus/Graphics/Device/Base/ShaderProgramBase.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShader.hpp"

namespace ramus 
{

    class OpenGLShaderProgram : public ShaderProgramBase 
    {
    public:
        OpenGLShaderProgram(std::shared_ptr<ShaderBase> vertexShader, 
                            std::shared_ptr<ShaderBase> fragmentShader);
        
        void Bind() const override;
        void Unbind() const override;

        void SetUniform(const std::string& name, float value) override;
        void SetUniform(const std::string& name, int value) override;
        void SetUniform(const std::string& name, const glm::mat4& matrix) override;
        void SetUniform(const std::string& name, const glm::vec3& vector) override;

    private:
        OpenGLHandle<ProgramDeleter> m_handle;
        mutable std::unordered_map<std::string, int> m_uniformLocationCache;
        int GetUniformLocation(const std::string& name) const;
    };

}