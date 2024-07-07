#pragma once
#include <vector>

#include "Entity.h"
#include "Entity3D.h"
#include "Mesh.h"
#include "ModelLoader.h"

namespace ToToEng
{
    class TOTO_API Model : public Entity3D
    {
    public:
        std::vector<Mesh> meshes;
        // constructor, expects a filepath to a 3D model.
        Model(Renderer *renderer, std::string const &path, bool gamma = false);

        // draws the model, and thus all its meshes
        void draw() override;
    };
}
