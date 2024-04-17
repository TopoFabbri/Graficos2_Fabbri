#pragma once
#include "Entity.h"

class TOTO_API Entity3D : public ToToEng::Entity
{
    float* normals;
    
public:
    explicit Entity3D(ToToEng::Renderer* renderer);
    ~Entity3D() override;
    
    void draw() override;
    void updateVao() override;
};