#include "TpCamera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>

ToToEng::TpCamera::TpCamera()
{
    offset = glm::vec3(0.0f, .5f, -2.f);
    reference = glm::vec3(0.0f, 0.0f, 0.0f);
}

ToToEng::TpCamera::~TpCamera()
{
}

void ToToEng::TpCamera::setReference(glm::vec3 reference)
{
    this->reference = reference;
}

void ToToEng::TpCamera::updateCamera()
{
    const glm::vec3 camUp = normalize(cross(getRight(), forward));
    const glm::vec3 newOffset = normalize(forward) * offset.z + camUp * offset.y + getRight() * offset.x;
    
    pos = reference + newOffset;
}
