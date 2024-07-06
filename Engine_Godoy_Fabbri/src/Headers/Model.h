#pragma once
#include <vector>

#include "Entity.h"
#include "Mesh.h"

namespace ToToEng
{
    class Model : public Entity
    {
    private:
        uint textureId;
        int width, height, bitDepth;

        const char* filePath;

        std::vector<Mesh*> meshes;
        std::vector<uint> meshesToTex;
    public:
    
    };
}
