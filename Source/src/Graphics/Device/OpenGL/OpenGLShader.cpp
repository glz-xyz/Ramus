#include "Ramus/Graphics/Device/OpenGL/OpenGLShader.hpp"
#include "Ramus/Core/Services/Logger.hpp"

namespace ramus 
{
    static GLenum Convert(ShaderStage stage) 
    {
        switch(stage) 
        {
            case ShaderStage::Vertex: return GL_VERTEX_SHADER;
            case ShaderStage::Fragment: return GL_FRAGMENT_SHADER;
        }
        return GL_NONE;
    }

    OpenGLShader::OpenGLShader(ShaderStage stage, const std::string& source)
    {
        uint32_t tempHandle = glCreateShader(Convert(stage));
        const GLchar* shaderSrc = &source[0];
        glShaderSource(tempHandle, 1, &shaderSrc, nullptr);
        glCompileShader(tempHandle);

        int success;
        glGetShaderiv(tempHandle, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint logLength;
            glGetShaderiv(tempHandle, GL_INFO_LOG_LENGTH, &logLength);
            std::string log;
            log.reserve(logLength);
            glGetShaderInfoLog(tempHandle, logLength, nullptr, log.data());
            Logger::GetDeviceLogger()->info(log.data());
        }
        // [TODO]
        // Move file reading here (need to know the paths here, too, for error-handling and hot-reloading in the future)

        m_handle = OpenGLHandle<ShaderDeleter>(tempHandle);
    }
}