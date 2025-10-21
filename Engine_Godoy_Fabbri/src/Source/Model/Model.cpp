#include "Model.h"

ToToEng::Model::Model(Renderer* renderer, std::string const& path, bool gamma) : Entity3D(renderer)
{
    ModelLoader::loadModel(path, meshes, transform, gamma);
    aabb = Box();
}

void ToToEng::Model::update()
{
    Entity3D::update();

    int counter = 0;

    for (std::pair<Transform* const, Mesh*> mesh : meshes)
    {
        mesh.second->updateBoundingBox();

        if (counter == 0)
        {
            aabb = mesh.second->getBox();
            counter++;
            continue;
        }

        aabb.min.x = std::min(aabb.min.x, mesh.second->getBox().min.x);
        aabb.min.y = std::min(aabb.min.y, mesh.second->getBox().min.y);
        aabb.min.z = std::min(aabb.min.z, mesh.second->getBox().min.z);

        aabb.max.x = std::max(aabb.max.x, mesh.second->getBox().max.x);
        aabb.max.y = std::max(aabb.max.y, mesh.second->getBox().max.y);
        aabb.max.z = std::max(aabb.max.z, mesh.second->getBox().max.z);
        counter++;
    }
}

void ToToEng::Model::draw()
{
    renderer->drawWireBox(aabb.min, aabb.max, {0, 1, 1, 1});
    
    for (std::pair<Transform* const, Mesh*> mesh : meshes)
    {
        renderer->drawWireBox(mesh.second->getBox().min, mesh.second->getBox().max, {0, 1, 1, 1});

        renderer->drawModel3D(mesh.second->VAO, mesh.second->indices.size(),
                              mesh.second->transform->getTransformMatrix(), mesh.second->textures);
    }
}
