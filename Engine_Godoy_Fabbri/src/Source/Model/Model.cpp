#include "Model.h"

#include "Camera.h"

ToToEng::Model::Model(Renderer* renderer, std::string const& path, bool gamma) : Entity3D(renderer)
{
    ModelLoader::loadModel(path, meshes, planes, transform, gamma);
    aabb = Box();
}

void ToToEng::Model::update()
{
    Entity3D::update();

    int counter = 0;

    for (const std::pair<Transform* const, Mesh*> mesh : meshes)
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

    for (const std::pair<Transform* const, Mesh*> mesh : meshes)
    {
        std::list<Transform*> children = mesh.second->transform->getChildren(true);

        if (children.empty())
            continue;

        for (Transform* child : children)
        {
            mesh.second->aabb.min.x = std::min(meshes[child]->getBox().min.x, mesh.second->aabb.min.x);
            mesh.second->aabb.min.y = std::min(meshes[child]->getBox().min.y, mesh.second->aabb.min.y);
            mesh.second->aabb.min.z = std::min(meshes[child]->getBox().min.z, mesh.second->aabb.min.z);

            mesh.second->aabb.max.x = std::max(meshes[child]->getBox().max.x, mesh.second->aabb.max.x);
            mesh.second->aabb.max.y = std::max(meshes[child]->getBox().max.y, mesh.second->aabb.max.y);
            mesh.second->aabb.max.z = std::max(meshes[child]->getBox().max.z, mesh.second->aabb.max.z);
        }
    }
}

void ToToEng::Model::draw(const std::list<Plane*> frustumPlanes)
{
    drawChildren(transform, frustumPlanes);
}

void ToToEng::Model::drawPlanes() const
{
    for (const Plane* plane : planes)
        renderer->drawPlaneAt(*plane, transform->getPos(), {1, 1, 0, 1}, 5.0f);
}

bool ToToEng::Model::shouldRender(Transform* childTransform, const std::list<Plane*>& frustumPlanes)
{
    Box boundingBox = meshes[childTransform]->getBox();
    vec3 vertices[8];

    vertices[0] = boundingBox.min;
    vertices[1] = {boundingBox.max.x, boundingBox.min.y, boundingBox.min.z};
    vertices[2] = {boundingBox.min.x, boundingBox.max.y, boundingBox.min.z};
    vertices[3] = {boundingBox.min.x, boundingBox.min.y, boundingBox.max.z};
    vertices[4] = boundingBox.max;
    vertices[5] = {boundingBox.min.x, boundingBox.max.y, boundingBox.max.z};
    vertices[6] = {boundingBox.max.x, boundingBox.min.y, boundingBox.max.z};
    vertices[7] = {boundingBox.max.x, boundingBox.max.y, boundingBox.min.z};

    for (const Plane* plane : frustumPlanes)
    {
        bool allOutside = true;
        for (const vec3& vertex : vertices)
        {
            if (plane->distanceToPoint(vertex) <= 0.0f)
            {
                allOutside = false;
                break;
            }
        }

        if (allOutside)
            return false;
    }

    return true;
}

void ToToEng::Model::drawChildren(Transform* trans, const std::list<Plane*>& frustumPlanes)
{
    const std::list<Transform*> children = trans->getChildren();
    if (children.empty()) return;
    
    for (Transform* childTransform : children)
    {
        if (meshes.find(childTransform) != meshes.end())
        {
            if (!shouldRender(childTransform, frustumPlanes)) continue;

            renderer->drawWireBox(meshes[childTransform]->getBox().min, meshes[childTransform]->getBox().max, {0, 1, 1, 1});
                
            renderer->drawModel3D(meshes[childTransform]->VAO, meshes[childTransform]->indices.size(), childTransform->getTransformMatrix(),
                meshes[childTransform]->textures);
        }

        drawChildren(childTransform, frustumPlanes);
    }
}