#pragma once
#include <glew.h>

#include "PointLight.h"

class TOTO_API SpotLight : public PointLight
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
