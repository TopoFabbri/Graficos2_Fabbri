#pragma once

namespace ToToEng
{
    class TextureImporter
    {
    public:
        TextureImporter();
        ~TextureImporter();
        
        static unsigned int loadTexture(const char* filePath, int& width, int& height);
        static unsigned int loadTexture(const char* filePath);
    };
}
