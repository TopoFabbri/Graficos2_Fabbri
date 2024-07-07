#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include <string>
#include <iostream>
#include <vector>

#include "Mesh.h"

using namespace std;

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

namespace ToToEng
{
    class Model
    {
    public:
        vector<Texture> textures_loaded;
        vector<Mesh> meshes;
        string directory;
        bool gammaCorrection;
        Renderer* renderer;

        Model(Renderer* renderer, string const& path, bool gamma = false);

        void draw();

    private:
        void loadModel(string const& path);
        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);

        // checks all material textures of a given type and loads the textures if they're not loaded yet.
        // the required info is returned as a Texture struct.
        vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    };
}
