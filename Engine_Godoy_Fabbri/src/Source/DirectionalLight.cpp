#include "DirectionalLight.h"

#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

DirectionalLight::DirectionalLight()
{
    type = Type::Dir;
    direction = glm::vec3(-0.2f, 1.0f, -0.3f);
}

DirectionalLight::~DirectionalLight() = default;

glm::vec3 DirectionalLight::getDirection() const
{
    return direction;
}

void DirectionalLight::setDirection(glm::vec3 direction)
{
    this->direction = direction;
}