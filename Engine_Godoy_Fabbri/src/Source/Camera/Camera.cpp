#include "Camera.h"
#include "Renderer.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

namespace ToToEng
{
    glm::vec3 Camera::getRight()
    {
        return normalize(cross(forward, up));
    }

    void Camera::updateRotation()
    {
        forward.x = cos(glm::radians(rot.y)) * cos(glm::radians(rot.x));
        forward.y = sin(glm::radians(rot.x));
        forward.z = sin(glm::radians(rot.y)) * cos(glm::radians(rot.x));
    }

    Camera::Camera()
    {
        if (main == nullptr)
            main = this;
        
        pos = glm::vec3(0.0f, 0.0f, 2.0f);
        forward = glm::vec3(0.0f, 0.0f, 1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        rot = glm::vec3(0.0f, 180.0f, 0.0f);

        frustumFov = 45.0f;
        nearPlane = 0.1f;
        farPlane = 100.0f;
        aspect = 1.0f;

        frustumPlanes = std::list<Plane*>();
    }

    Camera::~Camera()
    {
        for (const Plane* plane : frustumPlanes)
            delete plane;
        frustumPlanes.clear();

        if (main == this)
            main = nullptr;
    }

    glm::mat4 Camera::getView()
    {
        return lookAt(pos, pos + forward, up);
    }

    glm::vec3 Camera::getPos()
    {
        return pos;
    }

    glm::vec3 Camera::getForward()
    {
        return forward;
    }

    void Camera::moveUp(float amount)
    {
        pos += glm::vec3(0.0f, amount, 0.0f);
    }

    void Camera::moveRight(float amount)
    {
        pos += getRight() * amount;
    }

    void Camera::moveForward(float amount)
    {
        pos += forward * amount;
    }

    void Camera::rotateYaw(float amount)
    {
        rot.y += amount;

        if (rot.y > 360.0f)
            rot.y -= 360.0f;
        else if (rot.y < 0.0f)
            rot.y += 360.0f;

        updateRotation();
    }

    void Camera::rotatePitch(float amount)
    {
        rot.x = glm::clamp(rot.x + amount, -89.9f, 89.9f);
        
        updateRotation();
    }

    void Camera::updateFrustum(float aspect, float near, float far)
    {
        this->aspect = aspect;
        this->nearPlane = near;
        this->farPlane = far;

        const glm::mat4 projection = glm::perspective(glm::radians(frustumFov), aspect, near, far);
        const glm::mat4 view = getView();
        const glm::mat4 vp = projection * view;

        for (const Plane* plane : frustumPlanes)
            delete plane;
        frustumPlanes.clear();

        // Extract planes and flip them to use the same logic as bsp (outward normals)
        // Left
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] + vp[0][0], vp[1][3] + vp[1][0], vp[2][3] + vp[2][0]),
            -(vp[3][3] + vp[3][0])
        ));
        // Right
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] - vp[0][0], vp[1][3] - vp[1][0], vp[2][3] - vp[2][0]),
            -(vp[3][3] - vp[3][0])
        ));
        // Bottom
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] + vp[0][1], vp[1][3] + vp[1][1], vp[2][3] + vp[2][1]),
            -(vp[3][3] + vp[3][1])
        ));
        // Top
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] - vp[0][1], vp[1][3] - vp[1][1], vp[2][3] - vp[2][1]),
            -(vp[3][3] - vp[3][1])
        ));
        // Near
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] + vp[0][2], vp[1][3] + vp[1][2], vp[2][3] + vp[2][2]),
            -(vp[3][3] + vp[3][2])
        ));
        // Far
        frustumPlanes.push_back(new Plane(
            -glm::vec3(vp[0][3] - vp[0][2], vp[1][3] - vp[1][2], vp[2][3] - vp[2][2]),
            -(vp[3][3] - vp[3][2])
        ));

        // Normalize planes
        for (Plane* plane : frustumPlanes)
        {
            const float length = glm::length(plane->normal);
            plane->normal /= length;
            plane->distance /= length;
        }

        // Calculate corners
        const glm::mat4 invVP = glm::inverse(vp);
        const glm::vec4 ndcCorners[8] = {
            {-1, -1, -1, 1}, { 1, -1, -1, 1}, {-1,  1, -1, 1}, { 1,  1, -1, 1},
            {-1, -1,  1, 1}, { 1, -1,  1, 1}, {-1,  1,  1, 1}, { 1,  1,  1, 1}
        };

        for (int i = 0; i < 8; i++)
        {
            glm::vec4 corner = invVP * ndcCorners[i];
            frustumCorners[i] = glm::vec3(corner) / corner.w;
        }
    }

    std::list<Plane*> Camera::getFrustumPlanes() const
    {
        return frustumPlanes;
    }

    void Camera::setFrustumFov(float fov)
    {
        frustumFov = fov;
    }

    float Camera::getFrustumFov() const
    {
        return frustumFov;
    }

    void Camera::drawFrustum(Renderer* renderer)
    {
        const glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        // Near plane
        renderer->drawLine(frustumCorners[0], frustumCorners[1], color);
        renderer->drawLine(frustumCorners[1], frustumCorners[3], color);
        renderer->drawLine(frustumCorners[3], frustumCorners[2], color);
        renderer->drawLine(frustumCorners[2], frustumCorners[0], color);

        // Far plane
        renderer->drawLine(frustumCorners[4], frustumCorners[5], color);
        renderer->drawLine(frustumCorners[5], frustumCorners[7], color);
        renderer->drawLine(frustumCorners[7], frustumCorners[6], color);
        renderer->drawLine(frustumCorners[6], frustumCorners[4], color);

        // Connecting lines
        renderer->drawLine(frustumCorners[0], frustumCorners[4], color);
        renderer->drawLine(frustumCorners[1], frustumCorners[5], color);
        renderer->drawLine(frustumCorners[2], frustumCorners[6], color);
        renderer->drawLine(frustumCorners[3], frustumCorners[7], color);
    }
}
