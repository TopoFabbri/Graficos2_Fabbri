#pragma once

#include <list>

#include "Camera.h"
#include "CollisionManager.h"
#include "Renderer.h"
#include "Shape.h"
#include "Exports.h"
#include "Input.h"
#include "GameTime.h"

namespace ToToEng
{
    class TOTO_API BaseGame
    {
    private:
        Window* window;
        CollisionManager* collisionManager;

    protected:
        Renderer* renderer;
        std::list<Entity*> entities = std::list<Entity*>();
        Camera* camera;

    public:
        BaseGame(int width, int height, const char* title);
        virtual ~BaseGame();

        void run();

        void endGame();

        virtual void update() = 0;
        virtual void onDraw() = 0;

        void drawLine(vec3 start, vec3 end, vec4 color);
        void drawWireBox(vec3 center, vec3 size, vec4 color);
    };
}
