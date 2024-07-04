#pragma once
#include <string>
#include <glm/vec3.hpp>
#include "Exports.h"
#include "TextureImporter.h"

namespace ToToEng
{
    class TOTO_API Material
    {
        unsigned int diffuse;
        unsigned int specular;
        float shininess;

    public:
        Material();
        Material(std::string diffuse, std::string specular, float shininess);

        void setDiffuse(std::string path);
        void setSpecular(std::string path);
        void setShininess(float shininess);

        unsigned int getDiffuse() const;
        unsigned int getSpecular() const;
        float getShininess() const;
    };
}
