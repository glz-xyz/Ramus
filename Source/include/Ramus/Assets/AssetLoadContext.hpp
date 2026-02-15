#pragma once

namespace ramus 
{
    class AssetManager;
    class GraphicsDevice;

    struct AssetLoadContext 
    {
        AssetManager* manager;
        GraphicsDevice* device;
    };
}