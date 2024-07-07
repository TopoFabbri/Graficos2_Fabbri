#pragma once

#include <glew.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "Renderer.h"
#include "Transform.h"

using namespace std;

#define MAX_BONE_INFLUENCE 4

namespace ToToEng
{
    struct Vertex
    {
        vec3 Position;
        vec3 Normal;
        vec2 TexCoords;
    };

    struct Texture
    {
        unsigned int id;
        string type;
        string path;
    };

    class Mesh
    {
    public:
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        unsigned int VAO;

        Transform transform;

        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

        void Draw(Renderer* renderer);

    private:
        unsigned int VBO, EBO;

        // initializes all the buffer objects/arrays
        void setupMesh();
    };
}
