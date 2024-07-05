#include "Game.h"

#include "Headers/Entity3D.h"
#include "Headers/Sprite.h"
#include "Headers/TpCamera.h"

Game::Game(int width, int height, const char* title) : BaseGame(width, height, title)
{
    DirectionalLight* light = new DirectionalLight();
    SpotLight* spotLight = new SpotLight();
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({0.0f,  0.0f,  0.0f});

    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({2.0f,  5.0f, -15.0f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({-1.5f, -2.2f, -2.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({-3.8f, -2.0f, -12.3f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({2.4f, -0.4f, -3.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({-1.7f,  3.0f, -7.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({1.3f, -2.0f, -2.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({1.5f,  2.0f, -2.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({1.5f,  0.2f, -1.5f});
    
    entities.push_back(new Entity3D(renderer));
    entities.back()->transform.setPos({-1.3f,  1.0f, -1.5f});

    for (Entity* entity : entities)
        rotations.push_back({rand() % 45, rand() % 45, rand() % 45});
}

Game::~Game()
{
}

void Game::update()
{
    float speed = 10.f;
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
    
    for (Entity* entity : entities)
    {
        entity->transform.rotateX(rotations.front().x * GameTime::getDelta());
        entity->transform.rotateY(rotations.front().y * GameTime::getDelta());
        entity->transform.rotateZ(rotations.front().z * GameTime::getDelta());
        
        rotations.push_back(rotations.front());
        rotations.pop_front();
    }
}