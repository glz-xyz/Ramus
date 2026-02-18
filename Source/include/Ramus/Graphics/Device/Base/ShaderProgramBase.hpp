#pragma once

#include "Ramus/Graphics/Device/Base/ShaderBase.hpp"

namespace ramus
{

    class ShaderProgramBase 
    {
    public:
        virtual ~ShaderProgramBase() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetUniform(const std::string& name, float value) = 0;
        virtual void SetUniform(const std::string& name, int value) = 0;
        virtual void SetUniform(const std::string& name, const glm::mat4& matrix) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& vector) = 0;
    };
    
}