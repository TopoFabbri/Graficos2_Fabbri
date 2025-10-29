#include "Scene.h"

#include "Model.h"

ToToEng::Scene::Scene()
{
}

ToToEng::Scene::~Scene()
{
    for (int i = 0; i < entities.size(); ++i)
    {
        const Entity* entity = entities.front();
        entities.pop_front();
        delete entity;
    }
    for (int i = 0; i < planes.size(); ++i)
    {
        const Plane* plane = planes.front();
        planes.pop_front();
        delete plane;
    }

    entities.clear();
    planes.clear();
}

std::list<ToToEng::Entity*> ToToEng::Scene::getEntities()
{
    return entities;
}

std::list<Plane*> ToToEng::Scene::getPlanes()
{
    return planes;
}

void ToToEng::Scene::importModel(Renderer* renderer, std::string const& path, bool gamma)
{
    Model* model = new Model(renderer, path, gamma);

    std::cout << model->planes.size() << std::endl;
    
    for (Plane* plane : model->planes)
        addPlane(plane);
    
    addEntity(model);
}

void ToToEng::Scene::addEntity(Entity* entity)
{
    if (entity)
        entities.push_back(entity);
}

void ToToEng::Scene::addPlane(Plane* plane)
{
    if (plane)
        planes.push_back(plane);
}

void ToToEng::Scene::removeEntity(Entity* entity)
{
    if (entity)
        entities.remove(entity);
}

void ToToEng::Scene::removePlane(Plane* plane)
{
    if (plane)
        planes.remove(plane);
}