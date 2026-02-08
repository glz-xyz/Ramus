#pragma once
#include "Ramus/Graphics/RHI/GraphicsResource.hpp"

namespace ramus
{

    class Shader : public GraphicsResource<Shader>
    {
    public:
        Shader();
        ~Shader();
    };

}