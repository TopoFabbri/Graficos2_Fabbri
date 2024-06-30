#include "PointLight.h"

PointLight::PointLight()
{
    attenuation = glm::vec3(1.0f, 0.09f, 0.032f);
}

PointLight::~PointLight()
{
}

void PointLight::setAttenuation(glm::vec3 attenuation)
{
    this->attenuation = attenuation;
}

glm::vec3 PointLight::getAttenuation() const
{
    return attenuation;
}