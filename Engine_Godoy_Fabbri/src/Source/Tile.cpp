#include "Tile.h"

#include "TextureImporter.h"

namespace ToToEng
{
    Tile::Tile(int x, int y, const char* texturePath, int id)
    {
        this->id = id;
        this->x = x;
        this->y = y;

        loadTexture(texturePath);
    }

    Tile::~Tile()
    = default;

    void Tile::loadTexture(const char* texturePath)
    {
        textureId = TextureImporter::loadTexture(texturePath);
    }
}
