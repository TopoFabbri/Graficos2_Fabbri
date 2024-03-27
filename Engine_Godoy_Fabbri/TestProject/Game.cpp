#include "Game.h"

#include "Headers/Sprite.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    entities.push_back(new Sprite(renderer));
    entities.back()->transform.setScale({1, 1, 1});
    entities.push_back(new Sprite(renderer));
    entities.back()->transform.setScale({1, 1, 1});
    entities.back()->transform.setPos({1, 1, 1});
}

Game::~Game()
{
}

void Game::update()
{
    float camSpeed = 1.f;
    float camSens = 5.f;

    if (Input::getKey(Input::a, Input::Repeated))
        camera->moveRight(-camSpeed * GameTime::getDelta());
    if (Input::getKey(Input::d, Input::Repeated))
        camera->moveRight(camSpeed * GameTime::getDelta());

    if (Input::getKey(Input::w, Input::Repeated))
        camera->moveForward(camSpeed * GameTime::getDelta());
    if (Input::getKey(Input::s, Input::Repeated))
        camera->moveForward(-camSpeed * GameTime::getDelta());

    if (Input::getKey(Input::e, Input::Repeated))
        camera->moveUp(camSpeed * GameTime::getDelta());
    if (Input::getKey(Input::q, Input::Repeated))
        camera->moveUp(-camSpeed * GameTime::getDelta());

    const vec2 mouseDelta = Input::getMouseDelta();

    if (abs(mouseDelta.x) > 0.0001f)
        camera->rotateYaw(-camSens * mouseDelta.x * GameTime::getDelta());
    if (abs(mouseDelta.y) > 0.0001f)
        camera->rotatePitch(camSens * mouseDelta.y * GameTime::getDelta());
}
