#include "Camera.h"

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
        system("cls");
        std::cout << rot.x << std::endl;
        
        forward.x = cos(glm::radians(rot.y)) * cos(glm::radians(rot.x));
        forward.y = sin(glm::radians(rot.x));
        forward.z = sin(glm::radians(rot.y)) * cos(glm::radians(rot.x));
    }

    Camera::Camera()
    {
        pos = glm::vec3(0.0f, 0.0f, -1.0f);
        forward = glm::vec3(0.0f, 0.0f, 1.0f);
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        rot = glm::vec3(0.0f, -90.0f, 0.0f);
    }

    Camera::~Camera()
    {
    }

    glm::mat4 Camera::getView()
    {
        return lookAt(pos, pos + forward, up);
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
        updateRotation();
    }

    void Camera::rotatePitch(float amount)
    {
        rot.x += amount;

        updateRotation();
    }
}