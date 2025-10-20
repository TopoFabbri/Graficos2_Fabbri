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

    for (Mesh& mesh : meshes)
    {
        mesh.updateBoundingBox();

        if (counter == 0)
        {
            aabb = mesh.getBox();
            counter++;
            continue;
        }

        aabb.min.x = std::min(aabb.min.x, mesh.getBox().min.x);
        aabb.min.y = std::min(aabb.min.y, mesh.getBox().min.y);
        aabb.min.z = std::min(aabb.min.z, mesh.getBox().min.z);

        aabb.max.x = std::max(aabb.max.x, mesh.getBox().max.x);
        aabb.max.y = std::max(aabb.max.y, mesh.getBox().max.y);
        aabb.max.z = std::max(aabb.max.z, mesh.getBox().max.z);
        counter++;
    }
}

void ToToEng::Model::draw()
{
    renderer->drawWireBox(aabb.min, aabb.max, {0, 1, 1, 1});
    for (Mesh& mesh : meshes)
    {
        renderer->drawWireBox(mesh.getBox().min, mesh.getBox().max, {0, 1, 1, 1});

        renderer->drawModel3D(mesh.VAO, mesh.indices.size(),
                              mesh.transform->getTransformMatrix(), mesh.textures);
    }
}
