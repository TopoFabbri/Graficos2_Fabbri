#include "Plane.h"

#include <glm/ext/quaternion_geometric.hpp>

Plane::Plane(const glm::vec3& normal, const float distance)
{
    this->normal = normal;
    this->distance = distance;
}

Plane::Plane(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c)
{
    normal = glm::cross(b - a, c - a);
    distance = -glm::dot(normal, a);
}

glm::vec3 Plane::closestPointOnPlane(const glm::vec3& point) const
{
    return point - normal * distanceToPoint(point);  
}

float Plane::distanceToPoint(const glm::vec3& point) const
{
    return glm::dot(normal, point) + distance;
}

bool Plane::isPointInside(const glm::vec3& point) const
{
    return distanceToPoint(point) < 0.0f;
}

bool Plane::sameSide(const glm::vec3& pointA, const glm::vec3& pointB) const
{
    const float da = distanceToPoint(pointA);
    const float db = distanceToPoint(pointB);
    return (da > 0 && db > 0) || (da <= 0 && db <= 0);
}

void Plane::flip()
{
    normal *= -1.0f;
    distance *= -1.0f;   
}