#pragma once
#include <glm/vec3.hpp>
#include "Exports.h"

namespace ToToEng
{
    class TOTO_API Material
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;

    public:
        Material();
        Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

        void setAmbient(glm::vec3 ambient);
        void setDiffuse(glm::vec3 diffuse);
        void setSpecular(glm::vec3 specular);
        void setShininess(float shininess);

        glm::vec3 getAmbient() const;
        glm::vec3 getDiffuse() const;
        glm::vec3 getSpecular() const;
        float getShininess() const;
    };
}
