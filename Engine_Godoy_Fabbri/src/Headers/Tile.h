#pragma once

namespace ToToEng
{
    class Tile
    {
    private:
        int id;
        int x;
        int y;
        unsigned int textureId;
    
    public:
        Tile(int x, int y, const char* texturePath, int id);
        ~Tile();

        void loadTexture(const char* texturePath);
    };
}
