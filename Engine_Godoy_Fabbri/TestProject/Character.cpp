#include "Character.h"

#include "Headers/GameTime.h"
#include "Headers/Input.h"

using namespace ToToEng;

Character::Character(Renderer* renderer) : Sprite(renderer)
{
    accel = 20.f;
    vel = vec3(0.f);
    maxSpeed = 4.f;
    friction = .1f;

    transform.setPos(vec3(0.f, 100.f, 0.f));

    addAnimation(1.f, 8, 8, "../res/textures/dragon.png", 0, 4);
    setTrigger(false);
}

Character::~Character()
{
}

void Character::update()
{
    Sprite::update();
    
    if (Input::getKey(Input::a, Input::Repeated))
        accelerateInDir(-transform.right() * GameTime::getDelta());
    if (Input::getKey(Input::d, Input::Repeated))
        accelerateInDir(transform.right() * GameTime::getDelta());
    
    if (Input::getKey(Input::s, Input::Repeated))
        accelerateInDir(-transform.up() * GameTime::getDelta());
    if (Input::getKey(Input::w, Input::Repeated))
        accelerateInDir(transform.up() * GameTime::getDelta());
    
    if (Input::getKey(Input::q, Input::Repeated))
        transform.rotateZ(100.f * GameTime::getDelta());
    if (Input::getKey(Input::e, Input::Repeated))
        transform.rotateZ(-100.f * GameTime::getDelta());

    if (Input::getKey(Input::f, Input::Pressed))
        animation->setAnimByIndex(animation->getAnimIndex() >= 7 ? 0 : animation->getAnimIndex() + 1);
    
    transform.setPos(transform.getPos() + vel);

    if (length(vel) > 0)
    {
        if (length(vel) > friction)
            vel = normalize(vel) * (length(vel) - friction);
        else
            vel = vec3(0.f);
        
        playAnim = true;
    }
    else
    {
        playAnim = false;
    }
}

void Character::accelerateInDir(vec3 dir)
{
    vel += dir * accel;

    if (length(vel) > maxSpeed)
        vel = normalize(vel) * maxSpeed;
}
