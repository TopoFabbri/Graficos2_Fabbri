#pragma once
#include <glm/vec3.hpp>

#include "Exports.h"

class TOTO_API Plane
{
public:
    glm::vec3 normal;
    float distance;

    Plane(const glm::vec3& normal, float distance);
    Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);

    glm::vec3 closestPointOnPlane(const glm::vec3& point) const;
    float distanceToPoint(const glm::vec3& point) const;
    bool isPointInside(const glm::vec3& point) const;
    bool sameSide(const glm::vec3& pointA, const glm::vec3& pointB) const;
    void flip();
};
