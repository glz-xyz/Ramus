#pragma once

#include <memory>
#include <string>

namespace ramus
{

    template <typename T>
    class IResourceLoader
    {
    public:
        IResourceLoader() = default;
        virtual ~IResourceLoader() = default;

        virtual std::shared_ptr<T> Load(const std::string& path) = 0;
        
    };

}