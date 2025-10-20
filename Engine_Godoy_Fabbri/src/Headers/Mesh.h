#pragma once
#include <glew.h>
#include <vector>
#include <glm/vec2.hpp>


#include "Shader.h"
#include "Transform.h"

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

struct Box
{
    vec3 min;
    vec3 max;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;
    Box aabb;

    ToToEng::Transform* transform;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, ToToEng::Transform* transform);

    void updateBoundingBox();
    Box getBox() const;

private:
    unsigned int VBO, EBO;

    void setupMesh();
};
