#pragma once
#include "Ramus/Graphics/GraphicsResource.hpp"

namespace ramus
{

    class Shader : public GraphicsResource<Shader>
    {
    public:
        Shader();
        ~Shader();
    };

}