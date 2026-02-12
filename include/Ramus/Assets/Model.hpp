#pragma once

#include <vector>
#include <memory>

namespace ramus
{

    class Mesh;
    class Model
    {
    public:
        Model();
        ~Model();

        void AddMesh(std::unique_ptr<Mesh> mesh);
        
    private:
        
    };
}