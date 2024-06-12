#pragma once
#include <list>
#include <glm/vec3.hpp>

class LightSource
{
private:
    glm::vec3 pos;
    
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
public:
    LightSource();

    ~LightSource();

    glm::vec3 getPos() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
};
