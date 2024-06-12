#include "Game.h"

#include "Headers/Entity3D.h"
#include "Headers/Sprite.h"
#include "Headers/TpCamera.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setScale({1, 1, 1});
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setScale({100, 100, 100});

    dynamic_cast<Entity3D*>(entities.back())->setMaterial(Material::turquoise());
    dynamic_cast<Entity3D*>(entities.front())->setMaterial(Material::ruby());
}

Game::~Game()
{
}

void Game::update()
{
    float speed = 2.f;
    float camSens = 5.f;

    if (Input::getKey(Input::a, Input::Repeated))
        camera->moveRight(-speed * GameTime::getDelta());
    if (Input::getKey(Input::d, Input::Repeated))
        camera->moveRight(speed * GameTime::getDelta());

    if (Input::getKey(Input::w, Input::Repeated))
        camera->moveForward(speed * GameTime::getDelta());
    if (Input::getKey(Input::s, Input::Repeated))
        camera->moveForward(-speed * GameTime::getDelta());

    if (Input::getKey(Input::e, Input::Repeated))
        camera->moveUp(speed * GameTime::getDelta());
    if (Input::getKey(Input::q, Input::Repeated))
        camera->moveUp(-speed * GameTime::getDelta());

    const vec2 mouseDelta = Input::getMouseDelta();

    if (abs(mouseDelta.x) > 0.0001f)
        camera->rotateYaw(-camSens * mouseDelta.x * GameTime::getDelta());
    if (abs(mouseDelta.y) > 0.0001f)
        camera->rotatePitch(camSens * mouseDelta.y * GameTime::getDelta());
}