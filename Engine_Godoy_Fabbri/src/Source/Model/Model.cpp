#include "Model.h"

ToToEng::Model::Model(Renderer* renderer, std::string const& path, bool gamma) : Entity3D(renderer)
{
    ModelLoader::loadModel(path, meshes, transform, gamma);
}

void ToToEng::Model::update()
{
    Entity3D::update();

    for (Mesh& mesh : meshes)
        mesh.updateBoundingBox();
}

void ToToEng::Model::draw()
{
    for (Mesh& mesh : meshes)
    {
        renderer->drawWireBox(mesh.getBox().min, mesh.getBox().max, {0, 1, 1, 1});
        
        renderer->drawModel3D(mesh.VAO, mesh.indices.size(),
                              mesh.transform->getTransformMatrix(), mesh.textures);
    }
}
