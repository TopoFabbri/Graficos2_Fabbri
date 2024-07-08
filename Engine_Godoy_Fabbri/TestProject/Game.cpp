#include "Game.h"

#include "Headers/Entity3D.h"
#include "Headers/Model.h"
#include "Headers/Sprite.h"
#include "Headers/TpCamera.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    static_cast<TpCamera*>(camera)->setOffset({0.f, 1.7f, -5.f});
    camSpeed = 10.f;

    DirectionalLight* light = new DirectionalLight();
    SpotLight* spotLight = new SpotLight();

    entities.push_back(new Model(renderer, "../res/CH_Dummy_HurtV2/CH_Dummy_HurtV2.fbx", false));
    entities.back()->transform.setScale({.01f, .01f, .01f});

    entities.push_back(new Model(renderer, "../res/bp/Survival_BackPack_2.fbx", false));
    entities.back()->transform.setPos({2.f, 0.f, 0.f});

    entities.push_back(new Model(renderer, "../res/Backpack/backpack.obj", true));
    entities.back()->transform.setPos({-2.f, 0.f, 0.f});
}

Game::~Game()
{
}

void Game::update()
{
    float characterSpeed = 5.f;
    Entity* character = entities.front();

    if (Input::getKey(Input::i, Input::Repeated))
        character->transform.moveForward(-characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::k, Input::Repeated))
        character->transform.moveForward(characterSpeed * GameTime::getDelta());

    if (Input::getKey(Input::j, Input::Repeated))
        character->transform.moveRight(characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::l, Input::Repeated))
        character->transform.moveRight(-characterSpeed * GameTime::getDelta());

    if (Input::getKey(Input::u, Input::Repeated))
        character->transform.moveUp(-characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::o, Input::Repeated))
        character->transform.moveUp(characterSpeed * GameTime::getDelta());

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
    
    if (Input::getKey(Input::esc, Input::Pressed))
        endGame();

    const vec2 mouseDelta = Input::getMouseDelta();

    if (abs(mouseDelta.x) > 0.0001f)
        camera->rotateYaw(-camSens * mouseDelta.x * GameTime::getDelta());
    if (abs(mouseDelta.y) > 0.0001f)
        camera->rotatePitch(camSens * mouseDelta.y * GameTime::getDelta());

    static_cast<TpCamera*>(camera)->setReference(character->transform.getPos());
    static_cast<TpCamera*>(camera)->updateCamera();
    
    SpotLight* light = static_cast<SpotLight*>(LightSource::lights.back());
    light->setDirection(camera->getForward());
    light->setPosition(camera->getPos());
}
