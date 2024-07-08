#include "TpCamera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_geometric.hpp>

ToToEng::TpCamera::TpCamera(glm::vec3 reference, glm::vec3 offset)
{
    this->offset = offset;
    this->reference = reference;
}

ToToEng::TpCamera::~TpCamera()
{
}

void ToToEng::TpCamera::setReference(glm::vec3 reference)
{
    this->reference = reference;
}

void ToToEng::TpCamera::setOffset(glm::vec3 offset)
{
    this->offset = offset;
}

void ToToEng::TpCamera::updateCamera()
{
    const glm::vec3 camUp = normalize(cross(getRight(), forward));
    const glm::vec3 newOffset = normalize(forward) * offset.z + camUp * offset.y + getRight() * offset.x;
    
    pos = reference + newOffset;
}
