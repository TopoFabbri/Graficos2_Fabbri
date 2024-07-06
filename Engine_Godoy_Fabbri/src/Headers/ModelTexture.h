#pragma once

#include <string>
#include <glm/glm.hpp>
#include "TextureImporter.h"

namespace ToToEng
{
    class ModelTexture
    {
    private:
        glm::uint textureId;
        int width;
        int height;
        std::string filePath;
        std::string name;

    public:
        ModelTexture(const std::string& filePath, const std::string& name);
        ~ModelTexture();

        void loadTexture();
        void bind();
        void unbind();
        void deleteTexture();
    };
}
