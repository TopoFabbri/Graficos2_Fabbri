#include "Game.h"

#include "Character.h"

Game::Game(bool is3D, int width, int height, const char* title) : BaseGame(is3D, width, height, title)
{
    entities.push_back(new Sprite(renderer));
    dynamic_cast<Sprite*>(entities.back())->loadTexture("../res/textures/BG.png");
    dynamic_cast<Sprite*>(entities.back())->setTrigger(true);
    dynamic_cast<Sprite*>(entities.back())->transform.setScale({1600.f, 1600.f, 0.f});

    entities.push_back(new Character(renderer));
    character = dynamic_cast<Character*>(entities.back());

    entities.push_back(new Sprite(renderer));
    dynamic_cast<Sprite*>(entities.back())->setTrigger(false);

    dynamic_cast<Sprite*>(entities.back())->addAnimation(2.f, 5, {132.f, 323.f}, {49.f, 120.f}, "../res/textures/Sonic_Mania_Sprite_Sheet.png");
    dynamic_cast<Sprite*>(entities.back())->animation->setAnimByIndex(6);
}

Game::~Game()
{
}

void Game::update()
{
    camera->transform.lerpPos2D(character->transform.getPos() - vec3(400.f, 300.f, 0), .1f);
}
