#pragma once

#include "Ramus/Assets/Loaders/AssetLoader.hpp"
#include "Ramus/Assets/Material.hpp"

namespace ramus
{
    class MaterialLoader : public AssetLoader<Material>
    {
    public: 
        MaterialLoader();
        ~MaterialLoader();
        
        std::shared_ptr<Material> Load(const std::string& path, AssetLoadContext& loadContext) override;
    };

}