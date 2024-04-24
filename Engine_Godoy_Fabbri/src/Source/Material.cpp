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

    Material* Material::defaultMaterial()
    {
        return new Material
        {
            {glm::vec3(0.2f, 0.2f, 0.2f)},
            {glm::vec3(0.8f, 0.8f, 0.8f)},
            {glm::vec3(1.0f, 1.0f, 1.0f)},
            32.0f
        };
    }

    Material* Material::emerald()
    {
        return new Material {
            {0.0215f, 0.1745f, 0.0215f},
            {0.07568f, 0.61424f, 0.07568f},
            {0.633f, 0.727811f, 0.633f},
            0.6f
        };
    }

    Material* Material::jade()
    {
        return new Material {
            {0.135f, 0.2225f, 0.1575f},
            {0.54f, 0.89f, 0.63f},
            {0.316228f, 0.316228f, 0.316228f},
            0.1f
        };
    }

    Material* Material::obsidian()
    {
        return new Material {
            {0.05375f, 0.05f, 0.06625f},
            {0.18275f, 0.17f, 0.22525f},
            {0.332741f, 0.328634f, 0.346435f},
            0.3f
        };
    }

    Material* Material::pearl()
    {
        return new Material {
            {0.25f, 0.20725f, 0.20725f},
            {1.0f, 0.829f, 0.829f},
            {0.296648f, 0.296648f, 0.296648f},
            0.088f
        };
    }

    Material* Material::ruby()
    {
        return new Material {
            {0.1745f, 0.01175f, 0.01175f},
            {0.61424f, 0.04136f, 0.04136f},
            {0.727811f, 0.626959f, 0.626959f},
            0.6f
        };
    }

    Material* Material::turquoise()
    {
        return new Material {
            {0.1f, 0.18725f, 0.1745f},
            {0.396f, 0.74151f, 0.69102f},
            {0.297254f, 0.30829f, 0.306678f},
            0.1f
        };
    }

    Material* Material::brass()
    {
        return new Material {
            {0.329412f, 0.223529f, 0.027451f},
            {0.780392f, 0.568627f, 0.113725f},
            {0.992157f, 0.941176f, 0.807843f},
            0.21794872f
        };
    }

    Material* Material::bronze()
    {
        return new Material {
            {0.2125f, 0.1275f, 0.054f},
            {0.714f, 0.4284f, 0.18144f},
            {0.393548f, 0.271906f, 0.166721f},
            0.2f
        };
    }

    Material* Material::chrome()
    {
        return new Material {
            {0.25f, 0.25f, 0.25f},
            {0.4f, 0.4f, 0.4f},
            {0.774597f, 0.774597f, 0.774597f},
            0.6f
        };
    }

    Material* Material::copper()
    {
        return new Material {
            {0.19125f, 0.0735f, 0.0225f},
            {0.7038f, 0.27048f, 0.0828f},
            {0.256777f, 0.137622f, 0.086014f},
            0.1f
        };
    }

    Material* Material::gold()
    {
        return new Material {
            {0.24725f, 0.1995f, 0.0745f},
            {0.75164f, 0.60648f, 0.22648f},
            {0.628281f, 0.555802f, 0.366065f},
            0.4f
        };
    }

    Material* Material::silver()
    {
        return new Material {
            {0.19225f, 0.19225f, 0.19225f},
            {0.50754f, 0.50754f, 0.50754f},
            {0.508273f, 0.508273f, 0.508273f},
            0.4f
        };
    }

    Material* Material::blackPlastic()
    {
        return new Material {
            {0.0f, 0.0f, 0.0f},
            {0.01f, 0.01f, 0.01f},
            {0.50f, 0.50f, 0.50f},
            0.25f
        };
    }

    Material* Material::cyanPlastic()
    {
        return new Material
        {
            {0.0f, 0.1f, 0.06f},
            {0.0f, 0.50980392f, 0.50980392f},
            {0.50196078f, 0.50196078f, 0.50196078f},
            0.25f
        };
    }

    Material* Material::greenPlastic()
    {
        return new Material
        {
            {0.0f, 0.0f, 0.0f},
            {0.1f, 0.35f, 0.1f},
            {0.45f, 0.55f, 0.45f},
            0.25f
        };
    }

    Material* Material::redPlastic()
    {
        return new Material
        {
            {0.0f, 0.0f, 0.0f},
            {0.5f, 0.0f, 0.0f},
            {0.7f, 0.6f, 0.6f},
            0.25f
        };
    }

    Material* Material::whitePlastic()
    {
        return new Material
        {
            {0.0f, 0.0f, 0.0f},
            {0.55f, 0.55f, 0.55f},
            {0.70f, 0.70f, 0.70f},
            0.25f
        };
    }

    Material* Material::yellowPlastic()
    {
        return new Material {
            {0.0f, 0.0f, 0.0f},
            {0.5f, 0.5f, 0.0f},
            {0.60f, 0.60f, 0.50f},
            0.25f};
    }

    Material* Material::blackRubber()
    {
        return new Material
        {
            {0.02f, 0.02f, 0.02f},
            {0.01f, 0.01f, 0.01f},
            {0.4f, 0.4f, 0.4f},
            0.078125f
        };
    }

    Material* Material::cyanRubber()
    {
        return new Material
        {
            {0.0f, 0.05f, 0.05f},
            {0.4f, 0.5f, 0.5f},
            {0.04f, 0.7f, 0.7f},
            0.078125f
        };
    }

    Material* Material::greenRubber()
    {
        return new Material
        {
            {0.0f, 0.05f, 0.0f},
            {0.4f, 0.5f, 0.4f},
            {0.04f, 0.7f, 0.04f},
            0.078125f
        };
    }

    Material* Material::redRubber()
    {
        return new Material
        {
            {0.05f, 0.0f, 0.0f},
            {0.5f, 0.4f, 0.4f},
            {0.7f, 0.04f, 0.04f},
            0.078125f
        };
    }

    Material* Material::whiteRubber()
    {
        return new Material
        {
            {0.05f, 0.05f, 0.05f},
            {0.5f, 0.5f, 0.5f},
            {0.7f, 0.7f, 0.7f},
            0.078125f
        };
    }

    Material* Material::yellowRubber()
    {
        return new Material
        {
            {0.05f, 0.05f, 0.0f},
            {0.5f, 0.5f, 0.4f},
            {0.7f, 0.7f, 0.04f},
            0.078125f
        };
    }
}
