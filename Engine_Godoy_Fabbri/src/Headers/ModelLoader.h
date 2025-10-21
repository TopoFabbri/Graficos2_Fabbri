#pragma once
#include <map>
#include <string>
#include <vector>

#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

static class ModelLoader
{
public:
    static std::vector<Texture> textures_loaded;
    static std::string directory;
    static bool gammaCorrection;

    static void loadModel(std::string const& path, std::map<ToToEng::Transform*, Mesh*>& meshes, ToToEng::Transform* modelTransform, bool gamma = false);
    
private:
    static void processNode(aiNode* node, const aiScene* scene, std::map<ToToEng::Transform*, Mesh*>& meshes, ToToEng::Transform* parent, bool gamma = false);
    static Mesh* processMesh(aiMesh* mesh, const aiScene* scene, ToToEng::Transform* transform, bool gamma = false);
    
    static std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName, bool gamma);
};

static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
