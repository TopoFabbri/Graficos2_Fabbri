#include "BaseGame.h"

#include "CollisionManager.h"
#include "Model.h"
#include "TpCamera.h"

#include "GameTime.h"
#include "Scene.h"

namespace ToToEng
{
    BaseGame::BaseGame(int width, int height, const char* title)
    {
        camera = new Camera();
        window = new Window(width, height, title);
        renderer = new Renderer(window);
        collisionManager = new CollisionManager();
        currentScene = new Scene();

        Input::setCursorVisibility(false);

        GameTime::resetTime();
    }

    BaseGame::~BaseGame()
    {
        delete currentScene;
        delete renderer;
        delete window;
        delete camera;
        delete collisionManager;
    }

    void BaseGame::run()
    {
        while (!window->shouldClose())
        {
            GameTime::update();
            
            update();

            for (Entity* entity : currentScene->getEntities())
                entity->update();

            renderer->beginDraw();

            float aspect = static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight());
            camera->updateFrustum(aspect, 0.1f, 100.0f);
            camera->drawFrustum(renderer);

            for (Entity* entity : currentScene->getEntities())
                entity->draw(camera->getFrustumPlanes());

            onDraw();

            renderer->endDraw();

            glfwPollEvents();
        }
    }

    void BaseGame::endGame() const
    {
        window->close();
    }

    void BaseGame::drawLine(const vec3& start, const vec3& end, const vec4& color) const
    {
        renderer->drawLine(start, end, color);
    }

    void BaseGame::drawWireBox(vec3 min, vec3 max, const vec4& color) const
    {
        renderer->drawWireBox(min, max, color);
    }

    void BaseGame::importModel(const char* path) const
    {
        currentScene->importModel(renderer, path, true);
    }

    void BaseGame::addEntity(Entity* entity) const
    {
        currentScene->addEntity(entity);
    }

    void BaseGame::removeEntity(Entity* entity) const
    {
        currentScene->removeEntity(entity);
    }

    std::list<Entity*> BaseGame::getEntities() const
    {
        return currentScene->getEntities();
    }
}
