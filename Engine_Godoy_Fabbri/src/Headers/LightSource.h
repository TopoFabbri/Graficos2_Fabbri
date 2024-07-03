#pragma once
#include <list>
#include <glm/vec3.hpp>

#include "Exports.h"

class TOTO_API LightSource
{
public:
    enum class Type
    {
        Dir,
        Point,
        Spot
    };

protected:
    Type type;

private:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    
public:
    static std::list<LightSource*> lights;
    
    LightSource();
    ~LightSource();

    Type getType() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    
    void setAmbient(glm::vec3 ambient);
    void setDiffuse(glm::vec3 diffuse);
    void setSpecular(glm::vec3 specular);
};