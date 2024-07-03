#pragma once
#include "LightSource.h"

class PointLight : public LightSource
{
private:
    glm::vec3 position;
    glm::vec3 attenuation;

public:
    PointLight();
    ~PointLight();
    
    glm::vec3 getAttenuation() const;
    glm::vec3 getPosition() const;
    
    void setAttenuation(glm::vec3 attenuation);
    void setPosition(glm::vec3 position);
};
