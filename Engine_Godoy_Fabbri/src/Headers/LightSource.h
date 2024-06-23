#pragma once
#include <glm/vec3.hpp>

#include "Exports.h"

class TOTO_API LightSource
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

    void setPos(glm::vec3 pos);
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
};