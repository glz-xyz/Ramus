#pragma once

#include "Ramus/Resources/ResourceLoader.hpp"
#include "Ramus/Graphics/Model.hpp"

namespace ramus
{

    class ModelLoader : public ResourceLoader<Model>
    {
    public: 
        ModelLoader() = default;
        ~ModelLoader() = default;
        
        std::shared_ptr<Model> Load(const std::string& path) override;
    };

}