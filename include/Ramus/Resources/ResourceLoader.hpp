#pragma once

#include <memory>
#include <string>

namespace ramus
{

    template <typename T>
    class ResourceLoader
    {
    public:
        ResourceLoader() = default;
        virtual ~ResourceLoader() = default;

        virtual std::shared_ptr<T> Load(const std::string& path) = 0;
        
    };

}