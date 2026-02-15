#pragma once

#include "Ramus/Assets/Asset.hpp"

namespace ramus
{
    class Texture : public Asset
    {
    public:
        DEFINE_ASSET_TYPE(Texture)

        Texture();
        ~Texture();
    };
}