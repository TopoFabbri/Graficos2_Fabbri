#include "Game.h"

#include <algorithm>

#include "Headers/Entity3D.h"
#include "Headers/GameTime.h"
#include "Headers/Model.h"
#include "Headers/Sprite.h"
#include "Headers/TpCamera.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    // delete camera;
    // camera = new TpCamera();
    // static_cast<TpCamera*>(camera)->setOffset({0.f, 1.7f, -5.f});
    camSpeed = 10.f;

    // DirectionalLight* light = new DirectionalLight();
    PointLight* pointLight = new PointLight();
    SpotLight* spotLight = new SpotLight();
    pointLight->setPosition({-4.f, 0.f, 0.f});
    pointLight->setDiffuse({1.0f, .0f, .0f});

    // entities.push_back(new Model(renderer, "../res/chicken/Chicken1.fbx", false));
    // entities.back()->transform->setScale({0.1f, 0.1f, 0.1f});

    // entities.push_back(new Model(renderer, "../res/pochita/pochita.fbx", false));
    // entities.back()->transform->setPos({-4.f, 0.f, 0.f});

    // entities.push_back(new Model(renderer, "../res/Backpack/Survival_BackPack_2.fbx", true));
    // entities.back()->transform->setPos({0.f, 0.f, 0.f});
    // entities.back()->transform->setScale({.1f, .1f, .1f});

    importModel("../res/Tank/Tank.fbx");
    getEntities().back()->transform->setPos({0.f, 0.f, 0.f});
}

Game::~Game()
{
}

void Game::update()
{
    constexpr float characterSpeed = 5.f;
    const Entity* character = getEntities().front();

    // Tank movement
    if (Input::getKey(Input::i, Input::Repeated))
        character->transform->moveForward(characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::k, Input::Repeated))
        character->transform->moveForward(-characterSpeed * GameTime::getDelta());

    if (Input::getKey(Input::j, Input::Repeated))
        character->transform->moveRight(-characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::l, Input::Repeated))
        character->transform->moveRight(characterSpeed * GameTime::getDelta());

    if (Input::getKey(Input::u, Input::Repeated))
        character->transform->moveUp(characterSpeed * GameTime::getDelta());
    if (Input::getKey(Input::o, Input::Repeated))
        character->transform->moveUp(-characterSpeed * GameTime::getDelta());

    // Tank rotation
    if (Input::getKey(Input::n4, Input::Repeated))
        character->transform->rotateY(GameTime::getDelta() * 30.f);
    if (Input::getKey(Input::n6, Input::Repeated))
        character->transform->rotateY(GameTime::getDelta() * -30.f);

    // Turret rotation
    Transform* turretTransform = character->transform->getChildren().front()->getChildren().front()->getChildren().
                                            front()->getChildren().front();

    if (Input::getKey(Input::n7, Input::Repeated))
        turretTransform->rotateY(GameTime::getDelta() * 30.f);
    if (Input::getKey(Input::n9, Input::Repeated))
        turretTransform->rotateY(GameTime::getDelta() * -30.f);

    if (Input::getKey(Input::n8, Input::Repeated))
        turretTransform->rotateZ(GameTime::getDelta() * 30.f);
    if (Input::getKey(Input::n5, Input::Repeated))
        turretTransform->rotateZ(GameTime::getDelta() * -30.f);

    // Cam input
    float camSens = 5.f;

    camSpeed = Input::getMouseScroll() * 5;

    camSpeed = std::max<float>(camSpeed, 1);

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

    // Frustum FOV control
    if (Input::getKey(Input::up, Input::Repeated))
        camera->setFrustumFov(camera->getFrustumFov() + 20.f * GameTime::getDelta());
    if (Input::getKey(Input::down, Input::Repeated))
        camera->setFrustumFov(camera->getFrustumFov() - 20.f * GameTime::getDelta());

    camera->setFrustumFov(glm::clamp(camera->getFrustumFov(), 1.0f, 179.0f));

    // static_cast<TpCamera*>(camera)->setReference(character->transform->getPos());
    // static_cast<TpCamera*>(camera)->updateCamera();

    SpotLight* light = static_cast<SpotLight*>(LightSource::lights.back());
    light->setDirection(camera->getForward());
    light->setPosition(camera->getPos());
}

void Game::onDraw()
{
    vec3 origin = {0.f, 0.f, 0.f};
    
    drawLine(origin, vec3{1.f, 0.f, 0.f} * 100.f, {1.f, 0.f, 0.f, .3f});
    drawLine(origin, vec3{0.f, 1.f, 0.f} * 100.f, {0.f, 1.f, 0.f, .3f});
    drawLine(origin, vec3{0.f, 0.f, 1.f} * 100.f, {0.f, 0.f, 1.f, .3f});
}