#pragma once
#include "LightSource.h"

class TOTO_API DirectionalLight : public LightSource
{
private:
    glm::vec3 direction;
    
public:
    DirectionalLight();
    ~DirectionalLight();
    
    glm::vec3 getDirection() const;
    void setDirection(glm::vec3 direction);
};