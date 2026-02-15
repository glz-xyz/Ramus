#pragma once

namespace ramus 
{
    enum class ShaderStage 
    {
        Vertex,
        Fragment
    };

    class ShaderBase 
    {
    public:
        virtual ~ShaderBase() = default;
        virtual ShaderStage GetStage() const = 0;
    };
}