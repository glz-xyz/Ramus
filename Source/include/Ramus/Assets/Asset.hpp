#pragma once

#include <string>

#define DEFINE_ASSET_TYPE(Type) \
    static const char* StaticTypeName() { return #Type; } \
    const char* GetTypeName() const override { return StaticTypeName(); }

namespace ramus
{
    class Asset 
    {
    public:
        virtual ~Asset() = default;
    
        virtual const char* GetTypeName() const = 0;
    
        std::string path;
    };
}