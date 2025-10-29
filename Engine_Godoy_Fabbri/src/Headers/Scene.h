#pragma once
#include <list>
#include <string>

class Plane;

namespace ToToEng
{
    class Renderer;
    class Entity;

    class Scene
    {
    private:
        std::list<Entity*> entities = std::list<Entity*>();
        std::list<Plane*> planes = std::list<Plane*>();

    public:
        Scene();
        ~Scene();
        std::list<Entity*> getEntities();
        std::list<Plane*> getPlanes();
        void importModel(Renderer* renderer, std::string const& path, bool gamma = false);
        void addEntity(Entity* entity);
        void addPlane(Plane* plane);
        void removeEntity(Entity* entity);
        void removePlane(Plane* plane);
    };
}
