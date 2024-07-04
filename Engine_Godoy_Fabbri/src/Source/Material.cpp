#include "Material.h"

namespace ToToEng
{
    Material::Material()
    {
        diffuse = TextureImporter::loadTexture("../res/textures/BaseTexture.png");
        specular = TextureImporter::loadTexture("../res/textures/BaseSpecular.png");
        shininess = 32.0f;
    }

    Material::Material(std::string diffuse, std::string specular, float shininess)
    {
        this->diffuse = TextureImporter::loadTexture(diffuse.c_str());
        this->specular = TextureImporter::loadTexture(specular.c_str());
        this->shininess = shininess;
    }

    void Material::setDiffuse(std::string path)
    {
        diffuse = TextureImporter::loadTexture(path.c_str());
    }

    void Material::setSpecular(std::string path)
    {
        specular = TextureImporter::loadTexture(path.c_str());
    }

    void Material::setShininess(float shininess)
    {
        this->shininess = shininess;
    }

    unsigned int Material::getDiffuse() const
    {
        return diffuse;
    }

    unsigned int Material::getSpecular() const
    {
        return specular;
    }

    float Material::getShininess() const
    {
        return shininess;
    }
}
