#include "BaseGame.h"

#include "CollisionManager.h"
#include "Model.h"
#include "Sprite.h"
#include "TpCamera.h"
#include "Plane.h"
#include <glm/geometric.hpp> // For glm::cross and glm::normalize

namespace ToToEng
{
    BaseGame::BaseGame(int width, int height, const char* title)
    {
        camera = new Camera();
        window = new Window(width, height, title);
        renderer = new Renderer(window);
        collisionManager = new CollisionManager();

        Input::setCursorVisibility(false);

        GameTime::resetTime();
    }

    BaseGame::~BaseGame()
    {
        delete renderer;
        delete window;
        delete camera;
        delete collisionManager;

        const int size = static_cast<int>(entities.size());

        for (int i = 0; i < size; i++)
        {
            Entity* tmp = entities.front();
            entities.pop_front();
            delete tmp;
        }

        entities.clear();
    }

    void BaseGame::run()
    {
        while (!window->shouldClose())
        {
            GameTime::update();
            
            update();

            for (Entity* entity : entities)
                entity->update();

            renderer->beginDraw();

            for (Entity* entity : entities)
                entity->draw();

            onDraw();

            renderer->endDraw();

            glfwPollEvents();
        }
    }

    void BaseGame::endGame()
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
}