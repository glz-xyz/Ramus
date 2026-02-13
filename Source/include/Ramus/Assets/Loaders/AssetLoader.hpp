#pragma once

#include <memory>
#include <string>

namespace ramus
{

    template <typename T>
    class AssetLoader
    {
    public:
        virtual ~AssetLoader() = default;

        virtual std::shared_ptr<T> Load(const std::string& path) = 0;
        
    };

}