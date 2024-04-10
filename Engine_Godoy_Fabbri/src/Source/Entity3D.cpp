#include "Entity3D.h"

Entity3D::Entity3D(ToToEng::Renderer* renderer) : Entity(renderer)
{
    vertexQty = 24;
    indexQty = 36;
    id = 1;

    positions = new float[vertexQty * 3]
    {
        -.5f, -.5f, -.5f,
        .5f, -.5f, -.5f,
        -.5f, .5f, -.5f,
        .5f, .5f, -.5f,
        
        .5f, -.5f, -.5f,
        .5f, -.5f, .5f,
        .5f, .5f, -.5f,
        .5f, .5f, .5f,

        -.5f, -.5f, -.5f,
        -.5f, .5f, -.5f,
        -.5f, -.5f, .5f,
        -.5f, .5f, .5f,

        -.5f, .5f, -.5f,
        .5f, .5f, -.5f,
        -.5f, .5f, .5f,
        .5f, .5f, .5f,

        -.5f, -.5f, -.5f,
        .5f, -.5f, -.5f,
        -.5f, -.5f, .5f,
        .5f, -.5f, .5f,

        -.5f, -.5f, .5f,
        .5f, -.5f, .5f,
        -.5f, .5f, .5f,
        .5f, .5f, .5f
    };

    colors = new float[vertexQty * 4]
    {
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
        1.0f, 0.5f, 0.31f, 1.f,
    };

    textureCoords = new float[vertexQty * 2]
    {
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,
        
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,

        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f,
        
        0.f, 1.f,
        1.f, 1.f,
        0.f, 0.f,
        0.f, 1.f
    };

    indices = new unsigned int[indexQty]
    {
        0, 1, 2,
        1, 2, 3,
        
        4, 5, 6,
        5, 6, 7,

        8, 9, 10,
        9, 10, 11,

        12, 13, 14,
        13, 14, 15,

        16, 17, 18,
        17, 18, 19,

        20, 21, 22,
        21, 22, 23
    };

    updateVao();
}

Entity3D::~Entity3D()
{
}

void Entity3D::draw()
{
    renderer->drawShape(VAO, indexQty, color, transform.getTransformMatrix());
}