#include "PointLight.h"

PointLight::PointLight()
{
    type = Type::Point;
    
    position = glm::vec3(0.0f, 0.0f, 0.0f);
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

glm::vec3 PointLight::getPos() const
{
    return position;
}

void PointLight::setPosition(glm::vec3 position)
{
    this->position = position;
}
