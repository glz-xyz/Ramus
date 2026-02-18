#include "Ramus/Graphics/Device/OpenGL/OpenGLShaderProgram.hpp"
#include "Ramus/Graphics/Device/OpenGL/OpenGLShader.hpp"

#include <glad/gl.h>

namespace ramus
{
    OpenGLShaderProgram::OpenGLShaderProgram(std::shared_ptr<ShaderBase> vertexShader, std::shared_ptr<ShaderBase> fragmentShader) 
    {
        auto vs = std::static_pointer_cast<OpenGLShader>(vertexShader);
        auto fs = std::static_pointer_cast<OpenGLShader>(fragmentShader);

        uint32_t tempHandle = glCreateProgram();
        glAttachShader(tempHandle, vs->GetHandle());
        glAttachShader(tempHandle, fs->GetHandle());
        glLinkProgram(tempHandle);

        int success;
        glGetProgramiv(tempHandle, GL_LINK_STATUS, &success);
        if (!success) 
        {
            char infoLog[512];
            glGetProgramInfoLog(tempHandle, 512, NULL, infoLog);
            std::cerr << "[GL Error] Shader Linking Failed: " << infoLog << std::endl;
        }

        m_handle = OpenGLHandle<ProgramDeleter>(tempHandle);
    }

    void OpenGLShaderProgram::Bind() const { glUseProgram(m_handle); }

    void OpenGLShaderProgram::Unbind() const { glUseProgram(0); }

    void OpenGLShaderProgram::SetUniform(const std::string& name, float value) 
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void OpenGLShaderProgram::SetUniform(const std::string& name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void OpenGLShaderProgram::SetUniform(const std::string& name, const glm::vec3& vector)
    {
        glUniform3fv(GetUniformLocation(name), 1, &vector.x);
    }

    void OpenGLShaderProgram::SetUniform(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }

    int OpenGLShaderProgram::GetUniformLocation(const std::string& name) const
    {
        if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
            return m_uniformLocationCache[name];

        int location = glGetUniformLocation(m_handle, name.c_str());
        m_uniformLocationCache[name] = location;
        return location;
    }
};