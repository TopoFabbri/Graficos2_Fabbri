#include "LightSource.h"

std::list<LightSource*> LightSource::lights = std::list<LightSource*>();

LightSource::LightSource()
{
    lights.push_back(this);
    
    ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

LightSource::~LightSource()
{
    lights.remove(this);
}

LightSource::Type LightSource::getType() const
{
    return type;
}

glm::vec3 LightSource::getAmbient() const
{ return ambient; }

glm::vec3 LightSource::getDiffuse() const
{ return diffuse; }

glm::vec3 LightSource::getSpecular() const
{ return specular; }

void LightSource::setAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}

void LightSource::setDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}

void LightSource::setSpecular(glm::vec3 specular)
{
    this->specular = specular;
}