#include "Animation.h"

#include "GameTime.h"

void Animation::updateFrame()
{
    curFrame = static_cast<int>(curTime / frameTime) + frameStart;
}

void Animation::updateOffset()
{
    curOffset.x = static_cast<float>(curFrame) * frameSize.x + startOffset.x;
    curOffset.y = static_cast<float>(curAnim) * frameSize.y + startOffset.y;
}

Animation::Animation(float duration, int frameQty, int animQty, int texWidth, int texHeight)
{
    this->duration = duration;
    this->frameQty = frameQty;
    this->animQty = animQty;
    this->texWidth = texWidth;
    this->texHeight = texHeight;

    frameStart = 0;
    frameEnd = frameQty;
    
    frameSize.x = static_cast<float>(texWidth) / static_cast<float>(frameQty) / static_cast<float>(texWidth);
    frameSize.y = static_cast<float>(texHeight) / static_cast<float>(animQty) / static_cast<float>(texHeight);
    
    curOffset.x = 0;
    curOffset.y = 0;
    curTime = 0;
    frameTime = duration / static_cast<float>(frameQty - frameStart - (frameQty - frameEnd));
    curFrame = 0;
    curAnim = 0;

    startOffset = glm::vec2(0);
}

Animation::Animation(float duration, int frameQty, int animQty, int frameStart, int frameEnd, int texWidth, int texHeight)
{
    this->duration = duration;
    this->frameQty = frameQty;
    this->animQty = animQty;
    this->frameStart = frameStart;
    this->frameEnd = frameEnd;
    this->texWidth = texWidth;
    this->texHeight = texHeight;
    
    frameSize.x = static_cast<float>(texWidth) / static_cast<float>(frameQty) / static_cast<float>(texWidth);
    frameSize.y = static_cast<float>(texHeight) / static_cast<float>(animQty) / static_cast<float>(texHeight);
    
    curOffset.x = 0;
    curOffset.y = 0;
    curTime = 0;
    frameTime = duration / static_cast<float>(frameQty - frameStart - (frameQty - frameEnd));
    curFrame = 0;
    curAnim = 0;

    startOffset = glm::vec2(0);
}

Animation::Animation(float duration, int frameQty, glm::vec2 offset, glm::vec2 frameSize, int texWidth, int texHeight)
{
    this->duration = duration;
    this->frameQty = frameQty;
    this->frameSize = frameSize / static_cast<float>(texWidth);
    this->texWidth = texWidth;
    this->texHeight = texHeight;
    
    setStartOffset(offset);

    animQty = 1;
    frameStart = 0;
    curTime = 0;
    frameTime = duration / static_cast<float>(frameQty);
    curFrame = 0;
    curAnim = 0;

    curOffset = glm::vec2(0);
    frameEnd = frameQty;
}

Animation::~Animation()
{
}

void Animation::update()
{
    curTime += ToToEng::GameTime::getDelta();

    while (curTime >= duration)
        curTime -= duration;
        
    updateFrame();
    updateOffset();
}

void Animation::setAnimByIndex(int animNumber)
{
    if (animNumber >= 0 && animNumber < animQty)
        curAnim = animNumber;
}

int Animation::getAnimIndex()
{
    return curAnim;
}

glm::vec2 Animation::getOffset()
{
    return curOffset;
}

glm::vec2 Animation::getFrameSize()
{
    return frameSize;
}

void Animation::setStartOffset(glm::vec2 offset)
{
    startOffset.x = offset.x / static_cast<float>(texWidth);
    startOffset.y = offset.y / static_cast<float>(texHeight);
}
