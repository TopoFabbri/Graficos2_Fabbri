#pragma once

#include <list>

#include "Camera.h"
#include "CollisionManager.h"
#include "Renderer.h"
#include "Shape.h"
#include "Exports.h"
#include "Input.h"

namespace ToToEng
{
    class Scene;

    class TOTO_API BaseGame
    {
    private:
        Window* window;
        CollisionManager* collisionManager;

    protected:
        Renderer* renderer;
        Camera* camera;
        Scene* currentScene;

    public:
        BaseGame(int width, int height, const char* title);
        virtual ~BaseGame();

        void run();

        void endGame() const;

        virtual void update() = 0;
        virtual void onDraw() = 0;

        void drawLine(const vec3& start, const vec3& end, const vec4& color) const;
        void drawWireBox(vec3 min, vec3 max, const vec4& color) const;

        void importModel(const char* path) const;
        void addEntity(Entity* entity) const;
        void removeEntity(Entity* entity) const;
        std::list<Entity*> getEntities() const;
    };
}
