#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
private:
    glm::vec3 direction;
    float cutOff;
    float outerCutoff;

public:
    SpotLight();
    ~SpotLight();

    void setDirection(glm::vec3 direction);
    void setCutoff(float cutOff);
    void setOuterCutoff(float outerCutOff);
    
    glm::vec3 getDirection();
    float getCutoff();
    float getOuterCutoff();
};
