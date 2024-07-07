#include "Game.h"

#include "Headers/Entity3D.h"
#include "Headers/Model.h"
#include "Headers/Sprite.h"
#include "Headers/TpCamera.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    camSpeed = 10.f;
    
    DirectionalLight* light = new DirectionalLight();
    SpotLight* spotLight = new SpotLight();

    // entities.push_back(new Model(renderer, "../res/Backpack/backpack.obj", true));
    entities.push_back(new Model(renderer, "../res/CH_Dummy_HurtV2/CH_Dummy_HurtV2.fbx"));
    entities.back()->transform.setScale({0.01f, 0.01f, 0.01f});    
}

Game::~Game()
{
}

void Game::update()
{
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

    if (Input::getMouseScroll() > 0)
        camSpeed *= 1.01f;
    if (Input::getMouseScroll() < 0)
        camSpeed *= 0.99f;

    if (Input::getKey(Input::esc, Input::Pressed))
        endGame();
    
    const vec2 mouseDelta = Input::getMouseDelta();

    if (abs(mouseDelta.x) > 0.0001f)
        camera->rotateYaw(-camSens * mouseDelta.x * GameTime::getDelta());
    if (abs(mouseDelta.y) > 0.0001f)
        camera->rotatePitch(camSens * mouseDelta.y * GameTime::getDelta());

    SpotLight* light = static_cast<SpotLight*>(LightSource::lights.back());
    light->setDirection(camera->getForward());
    light->setPosition(camera->getPos());
}