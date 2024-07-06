#include "Model.h"

ToToEng::Model::Model(Renderer* renderer) : Entity(renderer)
{
    ownMaterial = false;
    material = new Material();
}

ToToEng::Model::~Model()
{
    if (!ownMaterial)
        return;

    delete material;
    material = nullptr;

    deleteModel();
}

void ToToEng::Model::loadModel(std::string modelPath, std::string texturePath)
{
}

void ToToEng::Model::loadModel(std::string modelPath, std::string texturePath, std::string textureName)
{
}

void ToToEng::Model::draw()
{
    for (int i = 0; i < meshes.size(); i++)
    {
        uint materialIndex = meshesToTex[i];

        if (materialIndex < textures.size() && textures[materialIndex])
            textures[materialIndex]->bind();

        meshes[i]->setMaterial(material);
        meshes[i]->draw();

        if (materialIndex < textures.size() && textures[materialIndex])
            textures[materialIndex]->unbind();
    }
}

void ToToEng::Model::deleteModel()
{
    meshes.clear();
    meshesToTex.clear();
    textures.clear();
}

void ToToEng::Model::setMaterial(Material* material)
{
    ownMaterial = true;
    this->material = material;
}
