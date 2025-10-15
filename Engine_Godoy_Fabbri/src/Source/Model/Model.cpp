#include "Model.h"

ToToEng::Model::Model(Renderer* renderer, std::string const& path, bool gamma) : Entity3D(renderer)
{
    ModelLoader::loadModel(path, meshes, transform, gamma);
}

void ToToEng::Model::draw()
{
    for (Mesh& mesh : meshes)
    {
        renderer->drawModel3D(mesh.VAO, mesh.indices.size(),
                              mesh.transform->getTransformMatrix(), mesh.textures);
    }
}
