#include "SpotLight.h"

#include <glm/detail/func_trigonometric.inl>

SpotLight::SpotLight()
{
    type = Type::Spot;
    
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    cutOff = glm::cos(glm::radians(12.5f));
    outerCutoff = glm::cos(glm::radians(17.5f));
}

SpotLight::~SpotLight()
{
}

void SpotLight::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}

void SpotLight::setCutoff(float cutOff)
{
    this->cutOff = cutOff;
}

void SpotLight::setOuterCutoff(float outerCutOff)
{
    this->outerCutoff = outerCutOff;
}

glm::vec3 SpotLight::getDirection()
{
    return direction;
}

float SpotLight::getOuterCutoff()
{
    return outerCutoff;
}

float SpotLight::getCutoff()
{
    return cutOff;
}