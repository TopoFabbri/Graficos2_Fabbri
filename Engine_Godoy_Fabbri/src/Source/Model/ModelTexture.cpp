#include "ModelTexture.h"

#include <glew.h>

ToToEng::ModelTexture::ModelTexture(const std::string& filePath, const std::string& name)
{
    this->filePath = filePath;
    this->name = name;

    textureId = TextureImporter::loadTexture(filePath.c_str(), width, height);
}

ToToEng::ModelTexture::~ModelTexture()
{
    deleteTexture();
}

void ToToEng::ModelTexture::loadTexture()
{
    textureId = TextureImporter::loadTexture(filePath.c_str(), width, height);
}

void ToToEng::ModelTexture::bind()
{
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
}

void ToToEng::ModelTexture::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void ToToEng::ModelTexture::deleteTexture()
{
    glDeleteTextures(1, &textureId);
    textureId = 0;
    width = 0;
    height = 0;
    filePath = "";
}