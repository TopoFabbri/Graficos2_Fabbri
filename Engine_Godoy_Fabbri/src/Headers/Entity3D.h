#pragma once
#include "Entity.h"
#include "Material.h"

namespace ToToEng
{
    class TOTO_API Entity3D : public ToToEng::Entity
    {
        Material* material;
        float* normals;
    
    public:
        explicit Entity3D(ToToEng::Renderer* renderer);
        ~Entity3D() override;
    
        void draw() override;
        void updateVao() override;

        void setMaterial(Material* material);
    };
}
