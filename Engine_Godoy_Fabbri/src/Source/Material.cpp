#include "Material.h"

namespace ToToEng
{
    Material::Material()
    {
        ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
        specular = glm::vec3(1.0f, 1.0f, 1.0f);
        shininess = 32.0f;
    }

    Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }

    void Material::setAmbient(glm::vec3 ambient)
    {
        this->ambient = ambient;
    }

    void Material::setDiffuse(glm::vec3 diffuse)
    {
        this->diffuse = diffuse;
    }

    void Material::setSpecular(glm::vec3 specular)
    {
        this->specular = specular;
    }

    void Material::setShininess(float shininess)
    {
        this->shininess = shininess;
    }

    glm::vec3 Material::getAmbient() const
    {
        return ambient; 
    }

    glm::vec3 Material::getDiffuse() const
    {
        return diffuse;
    }

    glm::vec3 Material::getSpecular() const
    {
        return specular;
    }

    float Material::getShininess() const
    {
        return shininess;
    }
}
