#pragma once
#include "LightSource.h"

class PointLight : public LightSource
{
private:
    glm::vec3 attenuation;

public:
    PointLight();
    ~PointLight();
    void setAttenuation(glm::vec3 attenuation);
    glm::vec3 getAttenuation() const;
};
