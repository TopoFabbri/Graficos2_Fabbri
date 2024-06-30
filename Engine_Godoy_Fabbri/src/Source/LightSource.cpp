#include "LightSource.h"

LightSource::LightSource()
{
    pos = glm::vec3(0.0f, 0.0f, 0.0f);
        
    ambient = glm::vec3(0.5f, 0.5f, 0.5f);
    diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    specular = glm::vec3(1.0f, 1.0f, 1.0f);
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::getPos() const
{ return pos; }

glm::vec3 LightSource::getAmbient() const
{ return ambient; }

glm::vec3 LightSource::getDiffuse() const
{ return diffuse; }

glm::vec3 LightSource::getSpecular() const
{ return specular; }

void LightSource::setPos(glm::vec3 pos)
{
    this->pos = pos;
}

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