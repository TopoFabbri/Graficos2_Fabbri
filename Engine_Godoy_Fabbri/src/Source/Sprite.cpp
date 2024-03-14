#include "Sprite.h"

#include "TextureImporter.h"

void ToToEng::Sprite::update()
{
    Entity2D::update();

    if (animation && playAnim)
    {
        animation->update();
        setOffset(animation->getOffset());
    }
}

ToToEng::Sprite::Sprite(Renderer* renderer) : Entity2D(renderer)
{
    loadTexture("../res/textures/AstonBirra.png");

    animation = nullptr;
    
    vertexQty = 4;
    indexQty = 6;
    id = 1;

    positions = new float[vertexQty * 3]
    {
        -.5f, -.5f, 0.f,
        .5f, -.5f, 0.f,
        -.5f, .5f, 0.f,
        .5f, .5f, 0.f
    };

    colors = new float[vertexQty * 4]
    {
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 1.f
    };

    textureCoords = new float[vertexQty * 2]
    {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        1.f, 0.f
    };

    indices = new unsigned int[indexQty]
    {
        0, 1, 2,
        1, 2, 3,
    };
    
    updateVao();

    collider = new BoxCollider2D({0.f, 0.f}, {1.f, 1.f}, &transform, false);
}

ToToEng::Sprite::~Sprite()
{
}

void ToToEng::Sprite::draw()
{
    renderer->drawEntity2D(VAO, indexQty, color, transform.getTransformMatrix(), texture);
}

void ToToEng::Sprite::loadTexture(const char* filePath)
{
    texture = TextureImporter::loadTexture(filePath, texWidth, texHeight);
}

void ToToEng::Sprite::addAnimation(float duration, int frameQty, int animQty, const char* filePath)
{
    loadTexture(filePath);
    animation = new Animation(duration, frameQty, animQty, texWidth, texHeight);
    setScale(animation->getFrameSize());
}

void ToToEng::Sprite::addAnimation(float duration, int frameQty, int animQty, const char* filePath, int frameStart,
    int frameEnd)
{
    loadTexture(filePath);
    animation = new Animation(duration, frameQty, animQty, frameStart, frameEnd, texWidth, texHeight);
    setScale(animation->getFrameSize());
}

void ToToEng::Sprite::addAnimation(float duration, int frameQty, vec2 offset, vec2 frameSize, const char* filePath)
{
    loadTexture(filePath);
    animation = new Animation(duration, frameQty, offset, frameSize, texWidth, texHeight);
    setScale(animation->getFrameSize());
}
