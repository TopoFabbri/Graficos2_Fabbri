#pragma once
#include "Entity3D.h"

namespace ToToEng
{
    class TOTO_API Mesh : public Entity3D
    {
    private:
        uint positionLocation;
        uint texLocation;
        uint normalLocation;
    
    public:
        Mesh(Renderer* renderer);
        ~Mesh();

        void createMesh(float* vertices, int vertexCount, unsigned int* indices, int indexQty);
        void draw() override;
        void clearMesh();
    };
}
