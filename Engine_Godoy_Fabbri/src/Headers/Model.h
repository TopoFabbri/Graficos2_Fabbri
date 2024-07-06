#pragma once
#include <vector>

#include "Entity.h"
#include "Mesh.h"
#include "ModelTexture.h"

namespace ToToEng
{
    class TOTO_API Model : public Entity
    {
    private:
        uint textureId;
        int width, height, bitDepth;

        const char* filePath;

        std::vector<Mesh*> meshes;
        std::vector<uint> meshesToTex;
        std::vector<ModelTexture*> textures;

        bool ownMaterial;
        Material* material;
        
    public:
        Model(Renderer* renderer);
        ~Model();

        void loadModel(std::string modelPath, std::string texturePath);
        void loadModel(std::string modelPath, std::string texturePath, std::string textureName);

        void draw() override;

        void deleteModel();

        void setMaterial(Material* material);
    };
}
